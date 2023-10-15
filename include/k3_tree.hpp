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
#include <queue>
#include <tuple>

#include <k3_tree_base.hpp>

//! Namespace for the succint data structure library
namespace sdsl {


template<uint8_t t_k1=2, uint8_t t_k2=2,
        typename t_bv=bit_vector,
        typename t_rank=typename t_bv::rank_1_type>
class k3_tree : public k3_tree_base<>
{

    static_assert(t_k1>1, "t_k has to be larger than 1.");
    static_assert(t_k2>1, "t_k has to be larger than 1.");

    public:
        typedef k3_tree_base::size_type size_type;
        typedef k3_tree_base::size_type pos_type;
        typedef k3_tree_base::tuple_result tuple_result;
        typedef k3_tree_base::point_type point_type;

    private:
        //! Bit array to store all the bits of the tree, except those in the
        //! last level.
        t_bv        k_t;
        //! Bit array to store a bit for each 0 in k_t (1 -> it as at least one point | 0 -> empty node)
        t_bv        k_l;

        t_rank      k_t_rank;

        uint8_t     k_k1;
        uint8_t     k_k2;
        uint16_t    k_height;

        // tmp params
        size_type k_k1_3;

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
    //********************** HELPERS ************************//
    //*******************************************************//

    /*! Get the chunk index ([0, k^3[) of a submatrix point.
     *
     * Gets a point in the global matrix and returns its corresponding chunk
     * in the submatrix specified.
     *
     * \param x x coordinate of the point in the global matrix.
     * \param y y coordinate of the point in the global matrix.
     * \param z z coordinate of the point in the global maxtrix.
     * \param x_0 x offset of the submatix in the global matrix.
     * \param y_0 y offset of the submatix in the global matrix.
     * \param z_0 z offset of the submatix in the global matrix.
     * \param l size of the chunk at the submatrix.
     * \param k the k parameter from the k^3 tree.
     * \returns the index of the chunk containing the point at the submatrix.
     */
    inline uint16_t get_chunk_idx(pos_type x, pos_type y, pos_type z,
                                  pos_type x_0, pos_type y_0, pos_type z_0,
                                  size_type l, uint8_t k)
    {
        return  ((x - x_0) / l) * k * k + ((y - y_0) / l) * k + (z - z_0) / l;
    }

    //*******************************************************//
    //********************* BUILD TREE **********************//
    //*******************************************************//
    //! Build a tree from an point collection
    /*! This method takes a vector of points
     *  and the cube size. And takes linear time over the amount of
     *  points to build the k_3 representation.
     *  \param edges A vector with all the points of the cube, it can
     *               not be empty.
     *  \param size Size of the cube, all the nodes in point must be
     *              within 0 and size ([0, size[).
     */
    void build(std::vector<point_type>& points, const size_type size) {

        // (Initial position, end position, submatrix size, base x coordinate, base y coordinate, base z coordinate)
        typedef std::tuple<pos_type, pos_type, size_type, pos_type, pos_type, pos_type > t_part_tuple;

        // Initialize k3-tree values (ks, height, size, etc)
        init(size);

        // Init bit_vectors
        bit_vector k_t_ = bit_vector(k_k1_3 * k_height * points.size(), 0);
        bit_vector k_l_;

        std::queue<t_part_tuple> q;
        pos_type t = 0, last_level = 0;
        pos_type init_p, end_p, x_0, y_0, z_0, it, t_x, t_y, t_z;
        size_type l = std::pow(k_k1, k_height - 1);
        std::vector<pos_type > pos_by_chunk(k_k1_3 + 1, 0);

        q.push(t_part_tuple(0, points.size(), l, 0, 0, 0));

        while (!q.empty()) {
            std::vector<pos_type> amount_by_chunk(k_k1_3, 0);
            std::tie(init_p, end_p, l, x_0, y_0, z_0) = q.front();

            q.pop();

            // Get size for each chunk
            for (it = init_p; it < end_p; it++) {
                amount_by_chunk[get_chunk_idx(
                        std::get<0>(points[it]), std::get<1>(points[it]), std::get<2>(points[it]),
                x_0, y_0, z_0, l, k_k1)] += 1;
            }
            if (l == 1) {
                if (last_level == 0) {
                    last_level = t;
                    k_l_ = bit_vector(k_t_.size() - last_level, 0);
                    k_t_.resize(last_level);
                    last_level = 1; // if t was 0
                    t = 0; // Restart counter as we're storing at k_l_ now.
                }
                for (it = 0; it < k_k1_3; it++,t++)
                    if (amount_by_chunk[it] != 0)
                        k_l_[t] = 1;
                // At l == 1 we do not put new elements at the queue.
                continue;
            }

            // Set starting position in the vector for each chunk
            pos_by_chunk[0] = init_p;
            for (it = 1; it < k_k1_3; it++)
                pos_by_chunk[it] =
                        pos_by_chunk[it - 1] + amount_by_chunk[it - 1];
            // To handle the last case when it = k_2 - 1
            pos_by_chunk[k_k1_3] = end_p;
            // Push to the queue every non zero elements chunk
            for (it = 0; it < k_k1_3; it++,t++) {
                // If not empty chunk, set bit to 1
                if (amount_by_chunk[it] != 0) {
                    t_x = it / (k_k1 * k_k1);
                    t_y = (it / k_k1) % k_k1;
                    t_z = it % k_k1;
                    k_t_[t] = 1;
                    q.push(t_part_tuple(pos_by_chunk[it],
                                        pos_by_chunk[it + 1],
                                        l / k_k1,
                                        x_0 + t_x * l,
                                        y_0 + t_y * l,
                                        z_0 + t_z * l));
                }
            }
            size_type chunk;

            // Sort edges' vector
            for (unsigned ch = 0; ch < k_k1_3; ch++) {
                size_type be = ch == 0 ? init_p : pos_by_chunk[ch - 1];
                for (it = pos_by_chunk[ch]; it < be + amount_by_chunk[ch];) {
                    chunk = get_chunk_idx(
                            std::get<0>(points[it]), std::get<1>(points[it]), std::get<2>(points[it]),
                            x_0, y_0, z_0, l, k_k1);

                    if (pos_by_chunk[chunk] != it)
                        std::iter_swap(points.begin() + it,
                                       points.begin() + pos_by_chunk[chunk]);
                    else
                        it++;
                    pos_by_chunk[chunk]++;
                }
            }
        }
        k_l_.resize(t);
        //k2_tree_ns::build_template_vector<t_bv>(k_t_, k_l_, k_t, k_l);
        k_t = t_bv(k_t_);
        k_l = t_bv(k_l_);

        k_t_rank = t_rank(&k_t);
    }



    public:

    //*******************************************************//
    //******************* CONSTRUCTOR ***********************//
    //*******************************************************//
    k3_tree() = default;

    k3_tree(const k3_tree& tr)
    {
        *this = tr;
    }

    k3_tree(k3_tree&& tr)
    {
        *this = std::move(tr);
    }

    k3_tree(std::string filename, size_type size)
    {
        // Initialize parameters
        init(size);

        // Open data file
        std::ifstream data_file(filename);
        assert(data_file.is_open() && data_file.good());

        // Read file and create conceptual tree
        pos_type pos_x, pos_y, pos_z;

        std::vector<point_type> points;
        while (!data_file.eof() && data_file.good()) {

            // Get position (x, y, z)
            read_member(pos_x, data_file);
            read_member(pos_y, data_file);
            read_member(pos_z, data_file);
//            std::cout << "Adding point " << pos_x << ", " << pos_y << ", " << pos_z << ")" << std::endl;

            points.push_back(point_type(pos_x, pos_y, pos_z));
        }

        // Remove duplicates
        std::sort( points.begin(), points.end() );
        points.erase( std::unique( points.begin(), points.end() ), points.end() );

        // Build structures
        build(points, size);
    }

    k3_tree(std::vector<point_type> &points, size_type size)
    {
        build(points, size);
    }

    //*******************************************************//
    //*************** BASIC OPERATIONS **********************//
    //*******************************************************//

    //! Move assignment operator
    k3_tree& operator=(k3_tree&& tr)
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
    k3_tree& operator=(k3_tree& tr)
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
    void swap(k3_tree& tr)
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
    bool operator==(const k3_tree& tr) const
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

    bool get(pos_type pos_x, pos_type pos_y, pos_type pos_z) {

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

        std::cout<< "submatriz_size_l = " << submatrix_size_l << std::endl;

        std::cout<< "k = " << k_k1 << std::endl;
        for(int i=0; i<k_t_rank.size(); i++){
            std::cout << k_t_rank (i) << " " ;
        }
        std::cout << std::endl;
        for (uint16_t l = 0; l < k_height-1; l++) {
            submatrix_size_l /= k;
            std::cout << "submatriz("<< l << ") = " << submatrix_size_l << std::endl;
            node_pos = (pos_x / submatrix_size_l) * k * k + pos_y / submatrix_size_l * k + pos_z / submatrix_size_l;
            node_pos += children_pos;
            std::cout << "node_pos(" << l << ") = " << node_pos << std::endl;
            if (k_t[node_pos] == 0) {
                return false; // Empty submatrix
            } else {
                // Go to next level
                children_pos = k_t_rank (node_pos+1) * k_k1_3;
            }
            std::cout << "children_pos(" << l << ") = " << children_pos << std::endl;
            // Calculate local position on the current submatrix
            pos_x %= submatrix_size_l;
            pos_y %= submatrix_size_l;
            pos_z %= submatrix_size_l;
            std::cout << "x=" << pos_x << " y=" << pos_y << " z=" << pos_z << "   ("<< l << ")" << std::endl;
        }


        // Last level
        submatrix_size_l /= k;
        std::cout << "submatrix_size_l (last level) = " << submatrix_size_l << std::endl;
        node_pos = (pos_x / submatrix_size_l) * k * k + pos_y / submatrix_size_l * k + pos_z / submatrix_size_l;
        node_pos += children_pos;
        std::cout << "node_pos = " << node_pos << " \nchildren_pos = " << children_pos << " (last level)" << std::endl;
        std::cout << "k_l[" << (node_pos-k_t.size()) << ", con k_t.size=" << k_t.size() << std::endl;
        return (k_l[node_pos - k_t.size()] == 1);
    }


    size_type get_region_2(size_type i_pos_x, size_type i_pos_y, size_type i_pos_z,
                         size_type e_pos_x, size_type e_pos_y, size_type e_pos_z,
                         std::vector<tuple_result> &result) {

        if (i_pos_x > k_size || i_pos_y > k_size || i_pos_z > k_size) {
            return 0;
        }

        return get_region_r(i_pos_x, i_pos_y, i_pos_z,
                          std::min(e_pos_x, k_size), std::min(e_pos_y, k_size), std::min(e_pos_z, k_size), result,
                          0, 0, 0, k_size, 0, 0);
    }


    size_type get_region(pos_type i_pos_x, pos_type i_pos_y, pos_type i_pos_z,
                           pos_type e_pos_x, pos_type e_pos_y, pos_type e_pos_z,
                         std::vector<tuple_result> &result) {

        if (i_pos_x > k_size || i_pos_y > k_size || i_pos_z > k_size) {
            return 0;
        }

        typedef std::tuple<pos_type, pos_type, pos_type, pos_type, pos_type, pos_type,
                size_type, pos_type, pos_type, pos_type, size_type, uint16_t> t_part_tuple;
        std::stack<t_part_tuple> q;

        q.push(t_part_tuple(i_pos_x, i_pos_y, i_pos_z, e_pos_x, e_pos_y, e_pos_z,
                            k_size, 0, 0, 0, 0, 0));


        uint8_t k = k_k1;
        pos_type x_i_b, x_e_b, y_i_b, y_e_b, z_i_b, z_e_b;  // First and end child
        pos_type xi, xe, yi, ye, zi, ze;                    // Local positions
        pos_type bx, by, bz;                                // Bases positions
        size_type sub_size;                                 // Size of each submatrix
        size_type pos, pos_children;
        uint16_t l;

        while (!q.empty()) {
            std::tie(xi, yi, zi, xe, ye, ze, sub_size, bx, by, bz, pos_children, l) = q.top();
            q.pop();

            // Calculate submatrix size
            sub_size = sub_size / k;

            // For each child that has cells that overlap with the searched region
            x_i_b = xi/sub_size;
            x_e_b = xe/sub_size;
            y_i_b = yi/sub_size;
            y_e_b = ye/sub_size;
            z_i_b = zi/sub_size;
            z_e_b = ze/sub_size;


            for (size_type x = x_i_b; x <= x_e_b; x++) {
                for (size_type y = y_i_b; y <= y_e_b; y++) {
                    for (size_type z = z_i_b; z <= z_e_b; z++) {
                        pos = pos_children + x * k * k + y * k + z; // Position of the current child

                        if (l < (k_height-1)) {
                            // Internal nodes
                            if (k_t[pos] == 1) {
                                // Continue with the search process
                                q.push(t_part_tuple(x == x_i_b ? xi % sub_size : 0,
                                                    y == y_i_b ? yi % sub_size : 0,
                                                    z == z_i_b ? zi % sub_size : 0,
                                                    x == x_e_b ? xe % sub_size : sub_size - 1,
                                                    y == y_e_b ? ye % sub_size : sub_size - 1,
                                                    z == z_e_b ? ze % sub_size : sub_size - 1,
                                                    sub_size, bx + x * sub_size, by + y * sub_size,  bz + z * sub_size,
                                                    k_t_rank(pos + 1) * k_k1_3, l+1));

                            } // ENF IF t[pos] == 1
                        } else {
                            // Leaves nodes
                            if (k_l[pos - k_t.size()] == 1) {
                                result.push_back(tuple_result(bx + x, by + y, bz + z));
                            }
                        } // END IF check level
                    } // END FOR z
                } // END FOR y
            } // END FOR x
        } // END WHILE queue
        return result.size();
    }

    size_type get_region_r(size_type i_pos_x, size_type i_pos_y, size_type i_pos_z,
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
                           n_points += get_region_r(std::max(b_x, i_pos_x) - b_x,
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

        written_bytes += write_member(K3_TREE_TYPE_BASIC, out, child, "k3_tree_type");
        written_bytes += k_t.serialize(out, child, "t");
        written_bytes += k_l.serialize(out, child, "l");
        written_bytes += k_t_rank.serialize(out, child, "t_rank");
        written_bytes += write_member(k_k1, out, child, "k1");
        written_bytes += write_member(k_k2, out, child, "k2");
        written_bytes += write_member(k_height, out, child, "k_height");
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
        ushort type;
        read_member(type, in);
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
        std::cout << "Bitmap t (size " << k_t.size() << ") : ";
        for (size_type p = 0; p < k_t.size(); p++) {
            if(p%8==0){
                std::cout << " ";
            }
            std::cout << k_t[p];
        }
        std::cout << std::endl;
        std::cout << "Bitmap l (size " << k_l.size() << ") : ";
        for (size_type p = 0; p < k_l.size(); p++) {
            if(p%8==0){
                std::cout << " ";
            }
            std::cout << k_l[p];
        }
        std::cout << std::endl;
        return;
    }

    void threshold2(t_bv k_t_, size_t np, int height_per_node, 
                    int height_, size_type submatrix,
                    pos_type x_min, pos_type x_max,
                    pos_type y_min, pos_type y_max,
                    pos_type z_min, pos_type z_max,
                    pos_type x, pos_type y, pos_type z){
        std::cout << "height total: " << height_ << std::endl;
        if(height_per_node < height_){
            std::cout << "height actual: " << height_per_node << std::endl;
            std::cout << "x: (" << x_min << "," << x_max << ") ";
            std::cout << " y: (" << y_min << "," << y_max << ") ";
            std::cout << " z: (" << z_min << "," << z_max << ") " << std::endl;
            std::cout << "Entrada A: " << k_t_[np] << " en el nodo: " << np << " ";
            std::cout << "Entrada B: " << k_t_[np+1] << " en el nodo: " << np+1 << " ";

            if(k_t_[np] == 0 && k_t_[np+1] == 0){
                std::cout << " no hago nada" << std::endl;

            }else if(k_t_[np] == 0 && k_t_[np+1] == 1){
                std::cout << " me voy a la derecha" << std::endl;
                submatrix /= k_k1;
                size_type cp = k_t_rank (np+2) * k_k1_3;
                std::cout << "submatrix " << submatrix << std::endl;
                std::cout << "np " << np << std::endl;
                std::cout << "cp " << cp << "    k_t_rank " << k_t_rank (np+2) * k_k1_3 << std::endl;
                std::cout << std::endl;
                threshold2(k_t_, cp, height_per_node+1, height_, submatrix, x_min, x_max/2, y_min, y_max/2, ((z_min+z_max)/2)+1, z_max, x, y, z);

            }else if(k_t_[np] == 1 && k_t_[np+1] == 0){
                std::cout << " me voy a la izquierda" << std::endl;
                submatrix /= k_k1;
                size_type cp = k_t_rank (np+1) * k_k1_3;
                std::cout << "submatrix " << submatrix << std::endl;
                std::cout << "np " << np << std::endl;
                std::cout << "cp " << cp << "    k_t_rank " << k_t_rank (np+1) * k_k1_3 << std::endl;
                std::cout << std::endl;
                threshold2(k_t_, cp, height_per_node+1, height_, submatrix, x_min, x_max/2, y_min, y_max/2, z_min, ((z_min+z_max)/2), x, y, z);

            }else{
                std::cout << " me voy a ambos lados" << std::endl;
                // submatrix /= k_k1;
                // size_type cp0 = k_t_rank (np+1) * k_k1_3;
                // size_type cp1 = k_t_rank (np+2) * k_k1_3;
                // std::cout << "submatrix " << submatrix << std::endl;
                // std::cout << "np " << np << std::endl;
                // std::cout << "cp0 " << cp0 << "    k_t_rank " << k_t_rank (np+1) * k_k1_3 << std::endl;
                // std::cout << "cp1 " << cp1 << "    k_t_rank " << k_t_rank (np+2) * k_k1_3 << std::endl;
                // std::cout << std::endl;
                // threshold2(k_t_, cp0, height_per_node+1, height_, submatrix, x_min, x_max/2, y_min, y_max/2, z_min, ((z_min+z_max)/2), x, y, z);
                // threshold2(k_t_, cp1, height_per_node+1, height_, submatrix, x_min, x_max/2, y_min, y_max/2, ((z_min+z_max)/2)+1, z_max, x, y, z);

            }
        } else {
            return;
        }

        // for (uint16_t l = 0; l < k_height-1; l++) {
        //     submatrix_size_l /= k;

        //     node_pos = (pos_x / submatrix_size_l) * k * k + pos_y / submatrix_size_l * k + pos_z / submatrix_size_l;
        //     node_pos += children_pos;

        //     if (k_t[node_pos] == 0) {
        //         return false; // Empty submatrix
        //     } else {
        //         // Go to next level
        //         children_pos = k_t_rank (node_pos+1) * k_k1_3;
        //     }

        //     // Calculate local position on the current submatrix
        //     pos_x %= submatrix_size_l;
        //     pos_y %= submatrix_size_l;
        //     pos_z %= submatrix_size_l;

    }

    bool threshold(int thresh) {
    
        size_t submatrix_size_l = k_size;
        size_t node_pos;
        size_t children_pos = 0;
        uint8_t k = k_k1;
        size_t k_k1_3 = pow(k, 3);

        ///////// PRINT ///////////
        std::cout<< "submatriz_size_l = " << submatrix_size_l << std::endl;
        std::cout<< "k = " << unsigned(k) << std::endl;
        std::cout<< "k_t_rank = ";
        for(int i=0; i<k_t_rank.size(); i++){
            std::cout << k_t_rank (i) << " " ;
        }
        std::cout << std::endl;
        
        ///////// PRINT ///////////
        std::cout << "k_height = " << unsigned(k_height) << std::endl;

        ///////// PRINT ///////////
        std::cout<< "k_t = ";
        for(int i=0; i<k_t.size(); i++){
            if(i%8==0 && i!=0){
                std::cout << " ";
            }
            std::cout << k_t[i];
        }
        std::cout << std::endl;

        ///////// PRINT ///////////
        std::cout<< "k_l = ";
        for(int i=0; i<k_l.size(); i++){
            if(i%8==0 && i!=0){
                std::cout << " ";
            }
            std::cout << k_l[i];
        }
        std::cout << std::endl;  
 
        int factor_t = 0;
        int height = unsigned(k_height);
        bit_vector k_t_thresh = bit_vector(factor_t, 0);

        for(int i=0; i<height-1; i++){
            factor_t += pow(4, i)*8;   
        }

        ///////// PRINT ///////////
        std::cout << "factor_t = " << factor_t << std::endl;


        for(int i=0; i<factor_t; i++){
            if(i%2 == 0){
                k_t_thresh[i] = 1;
            }
        }
        
        ///////// PRINT ///////////
        std::cout<< "k_t_thresh = ";
        for(int i=0; i<factor_t; i++){
            if(i%8==0 && i!=0){
                std::cout << " ";
            }
            std::cout << k_t_thresh[i];
        }
        std::cout << std::endl;

        pos_type x_max = get_max_size_x()-1;
        pos_type y_max = get_max_size_y()-1;
        pos_type z_max = get_max_size_z()-1;

        // size_type cp0 = k_t_rank (1) * k_k1_3;
        // size_type cp1 = k_t_rank (3) * k_k1_3;
        // size_type cp2 = k_t_rank (5) * k_k1_3;
        // size_type cp3 = k_t_rank (7) * k_k1_3;

        threshold2(k_t, (size_t) 0, 1, height, submatrix_size_l, 0, x_max/2, 0, y_max/2, 0, z_max, 0, 0, thresh);
        threshold2(k_t, (size_t) 2, 1, height, submatrix_size_l, 0, x_max/2, (y_max/2)+1, y_max, 0, z_max, 0, (y_max/2)+1, thresh);
        threshold2(k_t, (size_t) 4, 1, height, submatrix_size_l, (x_max/2)+1, x_max, 0, y_max/2, 0, z_max, (x_max/2)+1, 0, thresh);
        threshold2(k_t, (size_t) 6, 1, height, submatrix_size_l, (x_max/2)+1, x_max, (y_max/2)+1, y_max, 0, z_max, (x_max/2)+1, (y_max/2)+1, thresh);
        
        return true;

        //k3_tree& operator=(k3_tree& tr)
        
    }

}; // ENC CLASS k3-tree

} // END NAMESPACE sdsl

#endif // INCLUDED_SDSL_K3_TREE
