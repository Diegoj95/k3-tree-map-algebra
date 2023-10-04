/*  
 * Created by Fernando Silva on 9/04/18.
 *
 * Copyright (C) 2018-current-year, Fernando Silva, all rights reserved.
 *
 * 
 * Author's contact: Fernando Silva  <fernando.silva@udc.es>
 * Databases Lab, University of A Coruña. Campus de Elviña s/n. Spain
 *
 * DESCRIPTION
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef INCLUDED_SDSL_K3_TREE_LIDAR
#define INCLUDED_SDSL_K3_TREE_LIDAR

#include <k3_tree_no_opt.hpp>
#include <float.h>
#include <climits>

//! Namespace for the succint data structure library
namespace sdsl {

    template<uint8_t t_k1=2, uint8_t t_k2=2,
            typename t_bv=bit_vector,
            typename t_rank=typename t_bv::rank_1_type>
class k3_tree_lidar : public k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>
{

public:
    typedef k3_tree_no_opt<>::size_type size_type;
    typedef k3_tree_no_opt<>::tuple_result tuple_result;
    typedef std::tuple<double, double, double> d_tuple_result;

private:

    uint8_t k_n_digits;
    uint8_t k_n_params;

    // Delta value for each position
    long long k_delta_x;
    long long k_delta_y;
    long long k_delta_z;

protected:

public:

    //*******************************************************//
    //******************* CONSTRUCTOR ***********************//
    //*******************************************************//
    k3_tree_lidar() = default;

    k3_tree_lidar(const k3_tree_lidar& tr)
    {
        *this = tr;
    }

    k3_tree_lidar(k3_tree_lidar&& tr)
    {
        *this = std::move(tr);
    }

    k3_tree_lidar(std::string filename, uint8_t n_digits=0, uint8_t n_params=0)
    {
        k_n_digits = n_digits;
        k_n_params = n_params;

        // Open data file
        std::ifstream data_file(filename);
        assert(data_file.is_open() && data_file.good());


        size_type max_size ;
        size_type pow_n_digits = pow(10, k_n_digits);;
        // Check values of positions x, y, and z
        {
            k_delta_x = LLONG_MAX;
            k_delta_y = LLONG_MAX;
            k_delta_z = LLONG_MAX;


            double x, y, z;
            size_type other;
            long long max_x=0, max_y=0, max_z=0;
            while (!data_file.eof() && data_file.good()) {

                // Read position
                data_file >> x;
                k_delta_x = std::min(k_delta_x, (long long)round(x * pow_n_digits));
                max_x = std::max(max_x, (long long)round(x * pow_n_digits));
                data_file >> y;
                k_delta_y = std::min(k_delta_y, (long long)round(y * pow_n_digits));
                max_y = std::max(max_y, (long long)round(y * pow_n_digits));
                data_file >> z;
                k_delta_z = std::min(k_delta_z, (long long)round(z * pow_n_digits));
                max_z = std::max(max_z, (long long)round(z * pow_n_digits));

                // Other values
                for (uint8_t v = 0; v < k_n_params; v++){
                    data_file >> other;
                }
            } // END WHILE values

            max_size = (size_type)(max_x - k_delta_x);
            max_size = std::max(max_size, (size_type)(max_y - k_delta_y));
            max_size = std::max(max_size, (size_type)(max_z - k_delta_z));
        } // END BLOCK check values

        // Initialize k3-tree
        {
            this->init(max_size);
        }


        // Read file and create conceptual tree
        {
            data_file.clear();
            data_file.seekg(0, std::ios::beg);

            double x, y, z;
            size_type pos_x, pos_y, pos_z, other;
            conceptual_node *root = new conceptual_node();

            while (!data_file.eof() && data_file.good()) {

                // Read row and get position (x, y, z)
                data_file >> x;
                pos_x = round(x * pow_n_digits) - k_delta_x;
                data_file >> y;
                pos_y = round(y * pow_n_digits) - k_delta_y;
                data_file >> z;
                pos_z = round(z * pow_n_digits) - k_delta_z;

                // Other values
                for (uint8_t v = 0; v < k_n_params; v++){
                    data_file >> other;
                }

                // Add point to conceptual tree
                this->insert_point(root, pos_x, pos_y, pos_z);
            }

            data_file.close();

            // Build structures
            this->build_k3_tree_structure(root);
        } // END BLOCK conceptual tree

    }

    //*******************************************************//
    //*************** BASIC OPERATIONS **********************//
    //*******************************************************//

    //! Move assignment operator
    k3_tree_lidar& operator=(k3_tree_lidar&& tr)
    {
        if (this != &tr) {
            k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::operator=(tr);
            k_n_digits = std::move(tr.k_n_digits);
            k_n_params = std::move(tr.k_n_params);
            k_delta_x = std::move(tr.k_delta_x);
            k_delta_y = std::move(tr.k_delta_y);
            k_delta_z = std::move(tr.k_delta_z);
        }
        return *this;
    }

    //! Assignment operator
    k3_tree_lidar& operator=(k3_tree_lidar& tr)
    {
        if (this != &tr) {
            k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::operator=(tr);
            k_n_digits = tr.k_n_digits;
            k_n_params = tr.k_n_params;
            k_delta_x = tr.k_delta_x;
            k_delta_y = tr.k_delta_y;
            k_delta_z = tr.k_delta_z;
        }
        return *this;
    }

    //! Swap operator
    void swap(k3_tree_lidar& tr)
    {
        if (this != &tr) {
            k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::swap(tr);
            std::swap(k_n_digits, tr.k_n_digits);
            std::swap(k_n_params, tr.k_n_params);
            std::swap(k_delta_x, tr.k_delta_x);
            std::swap(k_delta_y, tr.k_delta_y);
            std::swap(k_delta_z, tr.k_delta_z);
        }
    }

    //! Equal operator
    bool operator==(const k3_tree_lidar& tr) const
    {
        if (!k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::operator==(tr)) {
            return false;
        }
        if (k_n_digits != tr.k_n_digits || k_n_params != tr.k_n_params ||
                k_delta_x != tr.k_delta_x || k_delta_y != tr.k_delta_y || k_delta_z != tr.k_delta_z) {
            return false;
        }
        return true;
    }

    //*******************************************************//
    //********************* GETTERS *************************//
    //*******************************************************//

    double get_min_size_x() {
        return k_delta_x / pow(10, k_n_digits);
    }

    double get_min_size_y() {
        return k_delta_y / pow(10, k_n_digits);
    }

    double get_min_size_z() {
        return k_delta_z / pow(10, k_n_digits);
    }

    double get_max_size_x() {
        return (k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::size + k_delta_x) / pow(10, k_n_digits);
    }

    double get_max_size_y() {
        return (k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::size + k_delta_y) / pow(10, k_n_digits);
    }

    double get_max_size_z() {
        return (k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::size + k_delta_z) / pow(10, k_n_digits);
    }


    //*******************************************************//
    //********************** QUERIES ************************//
    //*******************************************************//

    bool get(double pos_x, double pos_y, double pos_z) {

        size_type pow_n_digits = pow(10, k_n_digits);


        if ((pos_x * pow_n_digits) < k_delta_x ||
            (pos_y * pow_n_digits) < k_delta_y ||
            (pos_z * pow_n_digits) < k_delta_z) {
            return false;
        }


        size_type x = round(pos_x * pow_n_digits) - k_delta_x;
        size_type y = round(pos_y * pow_n_digits) - k_delta_y;
        size_type z = round(pos_z * pow_n_digits) - k_delta_z;

        return k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::get(x, y, z);
    }

    size_type get_region(double i_pos_x, double i_pos_y, double i_pos_z,
                         double e_pos_x, double e_pos_y, double e_pos_z,
                         std::vector<d_tuple_result> &result) {

        size_type pow_n_digits = pow(10, k_n_digits);
        if ((e_pos_x * pow_n_digits) < k_delta_x ||
                (e_pos_y * pow_n_digits) < k_delta_y ||
                (e_pos_z * pow_n_digits) < k_delta_z) {
            return 0;
        }

        size_type i_x = round(i_pos_x * pow_n_digits) - k_delta_x;
        size_type i_y = round(i_pos_y * pow_n_digits) - k_delta_y;
        size_type i_z = round(i_pos_z * pow_n_digits) - k_delta_z;
        size_type e_x = round(e_pos_x * pow_n_digits) - k_delta_x;
        size_type e_y = round(e_pos_y * pow_n_digits) - k_delta_y;
        size_type e_z = round(e_pos_z * pow_n_digits) - k_delta_z;

        std::vector<tuple_result> t_result;
        size_type n_points = k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::get_region(i_x, i_y, i_z, e_x, e_y, e_z, t_result);

        // Change each point to double
        for (size_type t = 0; t < t_result.size(); t++) {
            result.push_back(d_tuple_result(
                    (std::get<0>(t_result[t]) + k_delta_x) / (double)pow_n_digits ,
                    (std::get<1>(t_result[t]) + k_delta_y) / (double)pow_n_digits ,
                    (std::get<2>(t_result[t]) + k_delta_z) / (double)pow_n_digits));
        }
        result.resize(t_result.size());
        result.shrink_to_fit();
        return n_points;
    };


    //*******************************************************//
    //********************** FILE ***************************//
    //*******************************************************//

    //! Serialize to a stream
    /*! Serialize the k3_tree data structure
     *  \param out Outstream to write the k3_tree.
     *  \param v
     *  \param string_name
     *  \returns The number of written bytes.
     */
    size_type serialize(std::ostream& out, structure_tree_node* v=nullptr,
                        std::string name="") const
    {
        structure_tree_node* child = structure_tree::add_child(
                v, name, util::class_name(*this));
        size_type written_bytes = k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::serialize(out, child, "k3-tree");

        written_bytes += write_member(k_n_digits, out, child, "n_digits");
        written_bytes += write_member(k_n_params, out, child, "n_params");
        written_bytes += write_member(k_delta_x, out, child, "k_delta_x");
        written_bytes += write_member(k_delta_y, out, child, "k_delta_y");
        written_bytes += write_member(k_delta_z, out, child, "k_delta_z");
        structure_tree::add_size(child, written_bytes);
        return written_bytes;
    }


    //! Load from istream
    /*! Serialize the k3_tree from the given istream.
     *  \param istream Stream to load the k3_tree from.
     */
    void load(std::istream& in)
    {
        k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::load(in);

        read_member(k_n_digits, in);
        read_member(k_n_params, in);
        read_member(k_delta_x, in);
        read_member(k_delta_y, in);
        read_member(k_delta_z, in);
    }

    void print() {
        k3_tree_no_opt<t_k1, t_k2, t_bv, t_rank>::print();
        std::cout << "INFO LIDAR: " << std::endl;
        std::cout << "N Digits: " << k_n_digits << std::endl;
        std::cout << "Delta x: " << k_delta_x << ", Delta y: " << k_delta_y << "and Delta z: " << k_delta_z << std::endl;
        return;
    }


    //*******************************************************//
    //*********************** TEST **************************//
    //*******************************************************//
    bool check_values(std::istream& data_file) {

        // Read file
        double x, y, z, other;
        while (!data_file.eof() && data_file.good()) {

            // Read row and get position (x, y, z)
            data_file >> x;
            data_file >> y;
            data_file >> z;

            // Other values
            for (uint8_t v = 0; v < k_n_params; v++){
                data_file >> other;
            }

            if (!this->get(x, y, z)) {
                #ifndef NDEBUG
                    std::cout << "Failed point (" << x << ", " << y << ", " << z << ") " << std::endl;
                #endif
                return false;
            }
        }
        return true;
    }

}; // END CLASS k3_tree_lidar

} // END NAMESPACE sdsl



#endif // INCLUDED_SDSL_K3_TREE_LIDAR
