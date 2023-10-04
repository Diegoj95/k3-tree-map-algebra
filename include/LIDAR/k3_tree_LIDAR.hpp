/*  
 * Created by Fernando Silva on 07/06/18.
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

#include <k3_tree.hpp>
#include <k3_tree_level.hpp>
#include <k3_tree_points.hpp>
#include <LASlib/inc/lasreader.hpp>

//! Namespace for the succint data structure library
namespace sdsl {


template<
        typename t_k3_tree=k3_tree_points<>>
class k3_tree_LIDAR
{

    public:
        typedef int_vector<>::size_type size_type;
        typedef int_vector<>::size_type pos_type;
        typedef std::tuple<size_type, size_type, size_type> tuple_result;
        typedef std::tuple<pos_type, pos_type, pos_type> point_type;

    private:
        t_k3_tree k_k3_tree;
        double k_min_x;
        double k_min_y;
        double k_min_z;
        double k_max_x;
        double k_max_y;
        double k_max_z;
        double k_x_scale_factor;
        double k_y_scale_factor;
        double k_z_scale_factor;
        size_type k_offset_x;
        size_type k_offset_y;
        size_type k_offset_z;

    protected:



    public:

    //*******************************************************//
    //******************* CONSTRUCTOR ***********************//
    //*******************************************************//
    k3_tree_LIDAR() = default;

    k3_tree_LIDAR(const k3_tree_LIDAR& tr)
    {
        *this = tr;
    }

    k3_tree_LIDAR(k3_tree_LIDAR&& tr)
    {
        *this = std::move(tr);
    }

    k3_tree_LIDAR(LASreader* lasreader) {

        // Copy info from LAS/LAZ file
        k_min_x = lasreader->header.min_x;
        k_min_y = lasreader->header.min_y;
        k_min_z = lasreader->header.min_z;
        k_max_x = lasreader->header.max_x;
        k_max_y = lasreader->header.max_y;
        k_max_z = lasreader->header.max_z;
        k_x_scale_factor = lasreader->header.x_scale_factor;
        k_y_scale_factor = lasreader->header.y_scale_factor;
        k_z_scale_factor = lasreader->header.z_scale_factor;

        // Calculate offest of each dimension
        k_offset_x = std::floor(lasreader->header.min_x / lasreader->header.x_scale_factor);
        k_offset_y = std::floor(lasreader->header.min_y / lasreader->header.y_scale_factor);
        k_offset_z = std::floor(lasreader->header.min_z / lasreader->header.z_scale_factor);

        // Read points and store them into a vector
        std::vector<sdsl::k3_tree_points<>::point_type> points;
        points.resize(lasreader->npoints);
        uint count = 0;
        LASpoint point;
        while (lasreader->read_point()) {
            point = lasreader->point;
            points[count] = sdsl::k3_tree_points<>::point_type(point.get_X() - k_offset_x, point.get_Y() - k_offset_y, point.get_Z() - k_offset_z);
            count++;
        }

        // Max size of the cube
        ulong size = std::ceil(std::max(std::max((lasreader->header.max_x/ lasreader->header.x_scale_factor) - k_offset_x,
                                                 (lasreader->header.max_y/ lasreader->header.y_scale_factor) - k_offset_y),
                                        (lasreader->header.max_z/ lasreader->header.z_scale_factor) - k_offset_z));

        // Run k3_tree
//        std::cout << "LIDAR file with " << points.size() << " points and size " << size << std::endl;
        k_k3_tree = t_k3_tree(points, size);
    }


    //*******************************************************//
    //*************** BASIC OPERATIONS **********************//
    //*******************************************************//

    //! Move assignment operator
    k3_tree_LIDAR& operator=(k3_tree_LIDAR&& tr)
    {
        if (this != &tr) {
            k_k3_tree = std::move(tr.k_k3_tree);
            k_min_x = std::move(tr.k_min_x);
            k_min_y = std::move(tr.k_min_y);
            k_min_z = std::move(tr.k_min_z);
            k_max_x = std::move(tr.k_max_x);
            k_max_y = std::move(tr.k_max_y);
            k_max_z = std::move(tr.k_max_z);
            k_x_scale_factor = std::move(tr.k_x_scale_factor);
            k_y_scale_factor = std::move(tr.k_y_scale_factor);
            k_z_scale_factor = std::move(tr.k_z_scale_factor);
            k_offset_x = std::move(tr.k_offset_x);
            k_offset_y = std::move(tr.k_offset_y);
            k_offset_z = std::move(tr.k_offset_z);
        }
        return *this;
    }

    //! Assignment operator
    k3_tree_LIDAR& operator=(k3_tree_LIDAR& tr)
    {
        if (this != &tr) {
            k_k3_tree = tr.k_k3_tree;
            k_min_x = tr.k_min_x;
            k_min_y = tr.k_min_y;
            k_min_z = tr.k_min_z;
            k_max_x = tr.k_max_x;
            k_max_y = tr.k_max_y;
            k_max_z = tr.k_max_z;
            k_x_scale_factor = tr.k_x_scale_factor;
            k_y_scale_factor = tr.k_y_scale_factor;
            k_z_scale_factor = tr.k_z_scale_factor;
            k_offset_x = tr.k_offset_x;
            k_offset_y = tr.k_offset_y;
            k_offset_z = tr.k_offset_z;
        }
        return *this;
    }

    //! Swap operator
    void swap(k3_tree_LIDAR& tr)
    {
        if (this != &tr) {
            std::swap(k_k3_tree, tr.k_k3_tree);
            std::swap(k_min_x, tr.k_min_x);
            std::swap(k_min_y, tr.k_min_y);
            std::swap(k_min_z, tr.k_min_z);
            std::swap(k_max_x, tr.k_max_x);
            std::swap(k_max_y, tr.k_max_y);
            std::swap(k_max_z, tr.k_max_z);
            std::swap(k_x_scale_factor, tr.k_x_scale_factor);
            std::swap(k_y_scale_factor, tr.k_y_scale_factor);
            std::swap(k_z_scale_factor, tr.k_z_scale_factor);
            std::swap(k_offset_x, tr.k_offset_x);
            std::swap(k_offset_y, tr.k_offset_y);
            std::swap(k_offset_z, tr.k_offset_z);
        }
    }

    //! Equal operator
    bool operator==(const k3_tree_LIDAR& tr) const
    {
        // TODO check the rank support equality?
        if (k_k3_tree != tr.k_k3_tree)
            return false;
        if (k_min_x != tr.k_min_x || k_min_y != tr.k_min_y || k_min_z != tr.k_min_z)
            return false;
        if (k_max_x != tr.k_max_x || k_max_y != tr.k_max_y || k_max_z != tr.k_max_z)
            return false;
        if (k_x_scale_factor != tr.k_x_scale_factor ||
            k_y_scale_factor != tr.k_y_scale_factor ||
            k_z_scale_factor != tr.k_z_scale_factor)
            return false;
        if (k_offset_x != tr.k_offset_x ||
            k_offset_y != tr.k_offset_y ||
            k_offset_z != tr.k_offset_z)
            return false;

        return true;
    }


    //*******************************************************//
    //********************** QUERIES ************************//
    //*******************************************************//

    bool get(pos_type pos_x, pos_type pos_y, pos_type pos_z) {

//        std::cout << "Getting point: (" << pos_x - k_offset_x << ", " <<  pos_y - k_offset_y << ", " <<  pos_z - k_offset_z << ")" << std::endl;
        return k_k3_tree.get(pos_x - k_offset_x, pos_y - k_offset_y, pos_z - k_offset_z);
    }


    size_type get_region(size_type i_pos_x, size_type i_pos_y, size_type i_pos_z,
                         size_type e_pos_x, size_type e_pos_y, size_type e_pos_z,
                         std::vector<tuple_result> &result) {

        return k_k3_tree.get_region(i_pos_x - k_offset_x, i_pos_y - k_offset_y, i_pos_z - k_offset_z,
                                    e_pos_x - k_offset_x, e_pos_y - k_offset_y, e_pos_z - k_offset_z,
                                    result);
    }


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
        size_type written_bytes = 0;

        written_bytes += k_k3_tree.serialize(out, child, "k3_tree");
        written_bytes += write_member(k_min_x, out, child, "min_x");
        written_bytes += write_member(k_min_y, out, child, "min_y");
        written_bytes += write_member(k_min_z, out, child, "min_z");
        written_bytes += write_member(k_max_x, out, child, "max_x");
        written_bytes += write_member(k_max_y, out, child, "max_y");
        written_bytes += write_member(k_max_z, out, child, "max_z");
        written_bytes += write_member(k_x_scale_factor, out, child, "x_scale_factor");
        written_bytes += write_member(k_y_scale_factor, out, child, "y_scale_factor");
        written_bytes += write_member(k_z_scale_factor, out, child, "z_scale_factor");
        written_bytes += write_member(k_offset_x, out, child, "offset_x");
        written_bytes += write_member(k_offset_y, out, child, "offset_y");
        written_bytes += write_member(k_offset_z, out, child, "offset_z");

        structure_tree::add_size(child, written_bytes);
        return written_bytes;
    }


    //! Load from istream
    /*! Serialize the k3_tree from the given istream.
     *  \param istream Stream to load the k3_tree from.
     */
    void load(std::istream& in)
    {
        k_k3_tree.load(in);

        read_member(k_min_x, in);
        read_member(k_min_y, in);
        read_member(k_min_z, in);
        read_member(k_max_x, in);
        read_member(k_max_y, in);
        read_member(k_max_z, in);
        read_member(k_x_scale_factor, in);
        read_member(k_y_scale_factor, in);
        read_member(k_z_scale_factor, in);
        read_member(k_offset_x, in);
        read_member(k_offset_y, in);
        read_member(k_offset_z, in);
    }

    void print() {
        std::cout << "k3-tree with size " << k_k3_tree.size << " and height " << 0 << std::endl;
        std::cout << "Min: " << k_min_x << ", " << k_min_y << ", " << k_min_z << std::endl;
        std::cout << "Max: " << k_max_x << ", " << k_max_y << ", " << k_max_z << std::endl;
        std::cout << "Scale: " << k_x_scale_factor << ", " << k_y_scale_factor << ", " << k_z_scale_factor << std::endl;
        std::cout << "Offset: " << k_offset_x << ", " << k_offset_y << ", " << k_offset_z << std::endl;
        return;
    }

    //*******************************************************//
    //*********************** TEST **************************//
    //*******************************************************//
    bool check_values(LASreader* lasreader) {
        // Read file
        LASpoint point;
        while (lasreader->read_point()) {
            point = lasreader->point;
            if (!get(point.get_X(), point.get_Y(), point.get_Z())) {
#ifndef NDEBUG
                std::cout << "Failed point (" << point.get_X() << ", " << point.get_Y() << ", " << point.get_Z() << ") " << std::endl;
#endif
                return false;
            }
        }
        return true;
    }

}; // ENC CLASS k3-tree

} // END NAMESPACE sdsl

#endif // INCLUDED_SDSL_K3_TREE
