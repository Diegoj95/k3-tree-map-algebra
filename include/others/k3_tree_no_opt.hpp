/*  
 * Created by Fernando Silva on 3/04/18.
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

#ifndef INCLUDED_SDSL_K3_TREE
#define INCLUDED_SDSL_K3_TREE

#include <cstdint>
#include <sdsl/vectors.hpp>
#include <conceptual_node.hpp>
#include <queue>

//! Namespace for the succint data structure library
namespace sdsl {


template<uint8_t t_k1=2, uint8_t t_k2=2,
        typename t_bv=bit_vector,
        typename t_rank=typename t_bv::rank_1_type>
class k3_tree_no_opt
{

    static_assert(t_k1>1, "t_k has to be larger than 1.");
    static_assert(t_k2>1, "t_k has to be larger than 1.");

    public:
        //typedef k3_tree_ns::idx_type idx_type;
        //typedef k3_tree_ns::size_type size_type;
        typedef int_vector<>::size_type size_type;
        typedef std::tuple<size_type, size_type, size_type> tuple_result;

    private:
        //! Bit array to store all the bits of the tree, except those in the
        //! last level.
        t_bv        k_t;
        //! Bit array to store the last level of the tree.
        t_bv        k_l;

        t_rank      k_t_rank;

        uint8_t     k_k1;
        uint8_t     k_k2;
        uint16_t    k_height;
        size_type   k_size;

        // tmp params
        size_type k_k1_3;

    public:
        const size_type &size = k_size;

    protected:

    void init(size_type size) {
        // Set params
        k_k1 = t_k1;
        k_k1_3 = pow(k_k1, 3);
        k_k2 = t_k2;
        k_height = std::ceil(std::log(size)/std::log(k_k1));
        k_height = k_height > 1 ? k_height : 1; // If size == 0
        k_size = pow(k_k1, k_height);
    }

    //*******************************************************//
    //***************** CONCEPTUAL TREE *********************//
    //*******************************************************//
    void insert_point(conceptual_node *root, size_type pos_x, size_type pos_y, size_type pos_z) {

        // Size of the submatrix at the current level
        size_type submatrix_size_l = k_size;
        size_type node_pos;
        uint8_t k = k_k1;
        conceptual_node *current_node = root;

        // Set a 1 on each level of the tree
        for(uint16_t l = 0; l < k_height; l++) {
            submatrix_size_l /= k;
            node_pos = (pos_x / submatrix_size_l) * k * k + pos_y / submatrix_size_l * k + pos_z / submatrix_size_l;
            current_node = current_node->insert_node(node_pos, k);

            pos_x %= submatrix_size_l;
            pos_y %= submatrix_size_l;
            pos_z %= submatrix_size_l;
        }
    }

    //*******************************************************//
    //********************* STRUCTURE ***********************//
    //*******************************************************//
    void count_nodes(conceptual_node *node, uint16_t level, size_type &internal_nodes, size_type &leaves_nodes) {
        if (!node->has_children()) {
            return;
        }

        if (level == k_height - 1) {
            // Add internal nodes
            leaves_nodes += k_k1_3;
        } else {
            internal_nodes += k_k1_3;
            conceptual_node *child;
            for (uint c = 0; c < k_k1_3; c++) {
                child = node->get_child(c);
                if (child != nullptr) {
                    count_nodes(child, level+1, internal_nodes, leaves_nodes);
                }
            }
        }
        return;
    }


    void build_k3_tree_structure(conceptual_node *root){

        // Count number of internal and leaves nodes
        size_type internal_nodes = 0;
        size_type leaves_nodes = 0;
        count_nodes(root, 0, internal_nodes, leaves_nodes);

//        std::cout << "k3-tree has " << internal_nodes << " internal nodes and " << leaves_nodes << " leaves nodes" << std::endl;

        // Initialize bitmaps
        k_t = t_bv(internal_nodes);
        k_l = t_bv(leaves_nodes);

        // Set 1s and 0s
        std::queue<conceptual_node*> queue;
        queue.push(root);
        size_type n_current = 1;
        size_type n_next = 0;
        size_type pos = 0;

        size_type pos_t = 0;
        size_type pos_l = 0;
        uint16_t level = 0;

        conceptual_node *n;
        while (!queue.empty()) {
            n = queue.front();
            queue.pop();

            if (n->has_children()) {
                for (size_type c = 0; c < k_k1_3; c++) {
                    conceptual_node *child = n->get_child(c);
                    if (level == k_height-1) {
                        k_l[pos_l] = (child != nullptr ? 1 : 0);
                        pos_l++;
                        if (child != nullptr) {
                            delete(child);
                        }
                    } else {
                        k_t[pos_t] = (child != nullptr ? 1 : 0);
                        pos_t++;
                        if (child != nullptr) {
                            queue.push(child);
                            n_next++;
                        }
                    } // END IF level == k_height-2
                } // END FOR children
            } // END IF has_children

            pos++;
            if (pos == n_current) {
                // Go to next level of the k3-tree
                pos = 0;
                n_current = n_next;
                n_next = 0;
                level++;
            }

            delete(n);
        }

        util::init_support(k_t_rank, &k_t);
        return;
    }


    public:

    //*******************************************************//
    //******************* CONSTRUCTOR ***********************//
    //*******************************************************//
    k3_tree_no_opt() = default;

    k3_tree_no_opt(const k3_tree_no_opt& tr)
    {
        *this = tr;
    }

    k3_tree_no_opt(k3_tree_no_opt&& tr)
    {
        *this = std::move(tr);
    }

    k3_tree_no_opt(std::string filename, size_type size)
    {
        // Initialize parameters
        init(size);

        // Open data file
        std::ifstream data_file(filename);
        assert(data_file.is_open() && data_file.good());

        // Read file and create conceptual tree
        size_type pos_x, pos_y, pos_z;

        conceptual_node *root = new conceptual_node();

        while (!data_file.eof() && data_file.good()) {

            // Get position (x, y, z)
            read_member(pos_x, data_file);
            read_member(pos_y, data_file);
            read_member(pos_z, data_file);

            insert_point(root, pos_x, pos_y, pos_z);
        }

        // Build structures
        build_k3_tree_structure(root);
    }

    //*******************************************************//
    //*************** BASIC OPERATIONS **********************//
    //*******************************************************//

    //! Move assignment operator
    k3_tree_no_opt& operator=(k3_tree_no_opt&& tr)
    {
        if (this != &tr) {
            k_t = std::move(tr.k_t);
            k_l = std::move(tr.k_l);
            k_k1 = std::move(tr.k_k1);
            k_k2 = std::move(tr.k_k2);
            k_height = std::move(tr.k_height);
            k_t_rank = std::move(tr.k_t_rank);
            k_t_rank.set_vector(&k_t);
        }
        return *this;
    }

    //! Assignment operator
    k3_tree_no_opt& operator=(k3_tree_no_opt& tr)
    {
        if (this != &tr) {
            k_t = tr.k_t;
            k_l = tr.k_l;
            k_t_rank = tr.k_t_rank;
            k_t_rank.set_vector(&k_t);
            k_k1 = tr.k_k1;
            k_k2 = tr.k_k2;
            k_height = tr.k_height;
        }
        return *this;
    }

    //! Swap operator
    void swap(k3_tree_no_opt& tr)
    {
        if (this != &tr) {
            std::swap(k_t, tr.k_t);
            std::swap(k_l, tr.k_l);
            util::swap_support(k_t_rank, tr.k_t_rank, &k_t, &(tr.k_t));
            std::swap(k_k1, tr.k_k1);
            std::swap(k_k2, tr.k_k2);
            std::swap(k_height, tr.k_height);
        }
    }

    //! Equal operator
    bool operator==(const k3_tree_no_opt& tr) const
    {
        // TODO check the rank support equality?
        if (k_k1 != tr.k_k1 || k_k2 != tr.k_k2 || k_height != tr.k_height)
            return false;
        if (k_t.size() != tr.k_t.size() || k_l.size() != tr.k_l.size())
            return false;
        for (unsigned i = 0; i < k_t.size(); i++)
            if (k_t[i] != tr.k_t[i])
                return false;
        for (unsigned i = 0; i < k_l.size(); i++)
            if (k_l[i] != tr.k_l[i])
                return false;
        return true;
    }

    //*******************************************************//
    //********************** QUERIES ************************//
    //*******************************************************//

    bool get(size_type pos_x, size_type pos_y, size_type pos_z) {

        if (k_t.size() == 0) {
            // Empty matrix
            return false;
        }

        if (pos_x > k_size || pos_y > k_size || pos_z > k_size) {
            return false;
        }

        // Size of the submatrix at the current level
        size_type submatrix_size_l = k_size;
        size_type node_pos;
        size_type children_pos = 0;
        uint8_t k = k_k1;


        for (uint16_t l = 0; l < k_height; l++) {
            submatrix_size_l /= k;
            node_pos = (pos_x / submatrix_size_l) * k * k + pos_y / submatrix_size_l * k + pos_z / submatrix_size_l;
            node_pos += children_pos;

            if (l < (k_height-1)){
                // Internal nodes
                if (k_t[node_pos] == 0) {
                    return false; // Empty submatrix
                } else {
                    // Go to next level
                    children_pos = k_t_rank (node_pos+1) * k_k1_3;
                }

            } else {
                // Leaf node
                return (k_l[node_pos - k_t.size()] == 1);
            }

            // Calculate local position on the current submatrix
            pos_x %= submatrix_size_l;
            pos_y %= submatrix_size_l;
            pos_z %= submatrix_size_l;
        }

        return false; // Never reach this code
    }

    size_type get_region(size_type i_pos_x, size_type i_pos_y, size_type i_pos_z,
                         size_type e_pos_x, size_type e_pos_y, size_type e_pos_z,
                         std::vector<tuple_result> &result) {

        if (i_pos_x > k_size || i_pos_y > k_size || i_pos_z > k_size) {
            return 0;
        }
        return get_region(i_pos_x, i_pos_y, i_pos_z,
                          std::min(e_pos_x, k_size), std::min(e_pos_y, k_size), std::min(e_pos_z, k_size), result,
                          0, 0, 0, k_size, 0, 0);
    };

    size_type get_region(size_type i_pos_x, size_type i_pos_y, size_type i_pos_z,
                         size_type e_pos_x, size_type e_pos_y, size_type e_pos_z,
                         std::vector<tuple_result> &result,
                         size_type base_x, size_type base_y, size_type base_z,
                         size_type sub_size, uint16_t level, size_type pos_children) {

       size_type pos;
       uint8_t k = k_k1;
       size_type children_size = sub_size / k;
       size_type b_x, b_y, b_z;
       size_type n_points = 0;


       // For each child that has cells that overlap with the searched region
       for (size_type x = i_pos_x/children_size; x <= (e_pos_x/children_size); x++) {
           b_x = x * children_size;
           for (size_type y = i_pos_y/children_size; y <= (e_pos_y/children_size); y++) {
               b_y = y * children_size;
               for (size_type z = i_pos_z/children_size; z <= (e_pos_z/children_size); z++) {
                   pos = pos_children + x * k * k + y * k + z; // Position of the current child
                   b_z = z * children_size;


                   if (level < (k_height-1)) {
                       // Internal nodes
                       if (k_t[pos] == 1) {
                           // Continue with the search process
                           n_points += get_region(std::max(b_x, i_pos_x) - b_x,
                                      std::max(b_y, i_pos_y) - b_y,
                                      std::max(b_z, i_pos_z) - b_z,
                                      std::min(b_x + children_size-1, e_pos_x) - b_x,
                                      std::min(b_y + children_size-1, e_pos_y) - b_y,
                                      std::min(b_z + children_size-1, e_pos_z) - b_z,
                                      result,
                                      base_x + x * children_size, base_y + y * children_size, base_z + z * children_size,
                                      children_size, level + 1, k_t_rank(pos + 1) * k_k1_3);
                       }
                   } else {
                       // Leaves nodes
                       if (k_l[pos - k_t.size()] == 1) {
                           result.push_back(tuple_result(base_x + x, base_y + y, base_z + z));
                           n_points++;
                       }
                   }
               } // END FOR z
           } // END FOR y
       } // END FOR x
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
        size_type written_bytes = 0;

        written_bytes += k_t.serialize(out, child, "t");
        written_bytes += k_l.serialize(out, child, "l");
        written_bytes += k_t_rank.serialize(out, child, "t_rank");
        written_bytes += write_member(k_k1, out, child, "k1");
        written_bytes += write_member(k_k2, out, child, "k2");
        written_bytes += write_member(k_height, out, child, "height");
        written_bytes += write_member(k_size, out, child, "size");
        structure_tree::add_size(child, written_bytes);
        return written_bytes;
    }


    //! Load from istream
    /*! Serialize the k3_tree from the given istream.
     *  \param istream Stream to load the k3_tree from.
     */
    void load(std::istream& in)
    {
        k_t.load(in);
        k_l.load(in);
        k_t_rank.load(in);
        k_t_rank.set_vector(&k_t);
        read_member(k_k1, in);
        read_member(k_k2, in);
        read_member(k_height, in);
        read_member(k_size, in);
        k_k1_3 = pow(k_k1, 3);
    }

    void print() {
        std::cout << "k3-tree with size " << k_size << " and height " << k_height << std::endl;
        std::cout << "k1 = " << (uint)k_k1 << " | k2 = " << (uint)k_k2 << std::endl;
        std::cout << "Bitmap t: ";
        for (size_type p = 0; p < k_t.size(); p++) {
            std::cout << k_t[p];
        }
        std::cout << std::endl;
        std::cout << "Bitmap l: ";
        for (size_type p = 0; p < k_l.size(); p++) {
            std::cout << k_l[p];
        }
        std::cout << std::endl;
        return;
    }

    //*******************************************************//
    //*********************** TEST **************************//
    //*******************************************************//
    bool check_values(std::string data_file_name){
        std::ifstream values_file(data_file_name);
        assert(values_file.is_open() && values_file.good());

        bool res = check_values(values_file);
        values_file.close();
        return res;
    }

    bool check_values(std::istream& data_file) {

        // Read file
        size_type pos_x, pos_y, pos_z;
        while (!data_file.eof() && data_file.good()) {

            // Get position (x, y, z)
            read_member(pos_x, data_file);
            read_member(pos_y, data_file);
            read_member(pos_z, data_file);

            if (!get(pos_x, pos_y, pos_z)) {
                #ifndef NDEBUG
                    std::cout << "Failed point (" << pos_x << ", " << pos_y << ", " << pos_z << ") " << std::endl;
                #endif
                return false;
            }

        }

        return true;
    }

}; // ENC CLASS k3-tree

} // END NAMESPACE sdsl

#endif // INCLUDED_SDSL_K3_TREE
