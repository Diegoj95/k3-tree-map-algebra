/*  
 * Created by Fernando Silva on 05/06/18.
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

#ifndef INCLUDED_SDSL_K3_TREE_LEVE
#define INCLUDED_SDSL_K3_TREE_LEVEL

#include <cstdint>
#include <sdsl/vectors.hpp>
#include <queue>
#include <tuple>
#include "k3_tree_base.hpp"

//! Namespace for the succint data structure library
namespace sdsl {


template<uint8_t t_k1=2, uint8_t t_k2=2, size_t max_level=4,
        typename t_bv=bit_vector,
        typename t_rank=typename t_bv::rank_1_type,
        typename t_point_vec=dac_vector<>>
class k3_tree_level : public k3_tree_base<>
{

    static_assert(t_k1>1, "t_k has to be larger than 1.");
    static_assert(t_k2>1, "t_k has to be larger than 1.");
    static_assert(max_level>0, "max_level has to be larger than 0.");

    public:
        //typedef k3_tree_ns::idx_type idx_type;
        //typedef k3_tree_ns::size_type size_type;
        typedef int_vector<>::size_type size_type;
        typedef int_vector<>::size_type pos_type;
        typedef std::tuple<pos_type, pos_type, pos_type> point_type;

    private:
        //! Bit array to store all the bits of the tree, except those in the
        //! last level.
        t_bv        k_t;

        //! Bit array to store a bit for each 0 in k_t (1 -> it as at least one point | 0 -> empty node)
        t_bv        k_l;

        t_rank      k_t_rank;

        // DAC vector with coordinates
        t_point_vec k_r_leaf_points;
        t_point_vec k_x_points;
        t_point_vec k_y_points;
        t_point_vec k_z_points;

        uint8_t     k_k1;
        uint8_t     k_k2;
        uint16_t    k_height;
        uint16_t    k_max_height;
        size_type   k_prev_ones;

        // tmp params
        size_type k_k1_3;

    protected:

    // Sort points
   static bool sort_points(const point_type &p1, const point_type &p2) {
        // X coordinate
        if (std::get<0>(p1) < std::get<0>(p2)) {
            return true;
        }
        if (std::get<0>(p1) > std::get<0>(p2)) {
            return false;
        }

        // Y coordinate
        if (std::get<1>(p1) < std::get<1>(p2)) {
            return true;
        }
        if (std::get<1>(p1) > std::get<1>(p2)) {
            return false;
        }

        // Z coordinate
        if (std::get<2>(p1) < std::get<2>(p2)) {
            return true;
        }

        return false;
    }


    void init(size_type size) {
        // Set params
        k_k1 = t_k1;
        k_k1_3 = pow(k_k1, 3);
        k_k2 = t_k2;
        k_height = std::ceil(std::log(size)/std::log(k_k1));
        k_height = k_height > 1 ? k_height : 1; // If size == 0
        k_size = pow(k_k1, k_height);
        k_max_height = max_level;
        k_prev_ones = 0;
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

        // Init point vector
        std::vector<point_type> leaf_points;
        std::vector<pos_type> r_leaf_points_; // Store the start positions of the points of each leaf submatrix
        r_leaf_points_.push_back(0);

        std::queue<t_part_tuple> q;
        pos_type t = 0, last_level = 0, p_p = 0;
        pos_type init_p, end_p, x_0, y_0, z_0, it, t_x, t_y, t_z;
        size_type sub_size = std::pow(k_k1, k_height - 1);
        std::vector<pos_type > pos_by_chunk(k_k1_3 + 1, 0);

        q.push(t_part_tuple(0, points.size(), sub_size, 0, 0, 0));
        uint16_t c_level; // Current level;

        while (!q.empty()) {
            std::vector<pos_type> amount_by_chunk(k_k1_3, 0);
            std::tie(init_p, end_p, sub_size, x_0, y_0, z_0) = q.front();
            q.pop();
            c_level = k_height - std::ceil(std::log(sub_size)/std::log(k_k1));

            // Get size for each chunk
            for (it = init_p; it < end_p; it++) {
                amount_by_chunk[get_chunk_idx(
                        std::get<0>(points[it]), std::get<1>(points[it]), std::get<2>(points[it]),
                        x_0, y_0, z_0, sub_size, k_k1)] += 1;
            }
            if (sub_size == 1) {
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
                    k_t_[t] = 1;
                    if (c_level < k_max_height) {
                        k_prev_ones++;
                        t_x = it / (k_k1 * k_k1);
                        t_y = (it / k_k1) % k_k1;
                        t_z = it % k_k1;
                        q.push(t_part_tuple(pos_by_chunk[it],
                                            pos_by_chunk[it + 1],
                                            sub_size / k_k1,
                                            x_0 + t_x * sub_size,
                                            y_0 + t_y * sub_size,
                                            z_0 + t_z * sub_size));
                    }
                } // END IF amount > 0
            }
            size_type chunk;

            // Sort edges' vector
            for (unsigned ch = 0; ch < k_k1_3; ch++) {
                size_type be = ch == 0 ? init_p : pos_by_chunk[ch - 1];
                for (it = pos_by_chunk[ch]; it < be + amount_by_chunk[ch];) {
                    chunk = get_chunk_idx(
                            std::get<0>(points[it]), std::get<1>(points[it]), std::get<2>(points[it]),
                            x_0, y_0, z_0, sub_size, k_k1);

                    if (pos_by_chunk[chunk] != it)
                        std::iter_swap(points.begin() + it,
                                       points.begin() + pos_by_chunk[chunk]);
                    else
                        it++;
                    pos_by_chunk[chunk]++;
                }
            }

            // Add leaf points
            if (c_level == k_max_height) {
                for (unsigned ch = 0; ch < k_k1_3; ch++) {
                    if (amount_by_chunk[ch] != 0 ) {
                        std::vector<point_type>::iterator it_begin = leaf_points.end();
                        for (it =  pos_by_chunk[ch] - amount_by_chunk[ch]; it < pos_by_chunk[ch]; it++) {
                            leaf_points.push_back(point_type(std::get<0>(points[it]) % sub_size,
                                                             std::get<1>(points[it]) % sub_size,
                                                             std::get<2>(points[it]) % sub_size));
    //                        leaf_points.push_back(points[it]);
                        }
                        r_leaf_points_.push_back(r_leaf_points_[r_leaf_points_.size()-1] + amount_by_chunk[ch]);
                        std::sort(leaf_points.end() - amount_by_chunk[ch], leaf_points.end(), sort_points);
                    }
                } // END FOR add points
            } // END IF max_height
        }

        if (last_level == 0) {
            k_t_.resize(t);
            k_l_.resize(0);
        } else {
            k_l_.resize(t);
        }

        //k2_tree_ns::build_template_vector<t_bv>(k_t_, k_l_, k_t, k_l);
        k_t = t_bv(k_t_);
        k_l = t_bv(k_l_);

        k_t_rank = t_rank(&k_t);

        // Create DAC vectors
        k_r_leaf_points = t_point_vec(r_leaf_points_);

        // TODO optimize this!!!
        std::vector<pos_type> pos(leaf_points.size());
        for (size_t p  = 0; p < leaf_points.size(); p ++){
            pos[p] = std::get<0>(leaf_points[p]);
        }
        k_x_points = t_point_vec(pos);

        for (size_t p  = 0; p < leaf_points.size(); p ++){
            pos[p] = std::get<1>(leaf_points[p]);
        }
        k_y_points = t_point_vec(pos);

        for (size_t p  = 0; p < leaf_points.size(); p ++){
            pos[p] = std::get<2>(leaf_points[p]);
        }
        k_z_points = t_point_vec(pos);
    }



    public:

    //*******************************************************//
    //******************* CONSTRUCTOR ***********************//
    //*******************************************************//
    k3_tree_level() = default;

    k3_tree_level(const k3_tree_level& tr)
    {
        *this = tr;
    }

    k3_tree_level(k3_tree_level&& tr)
    {
        *this = std::move(tr);
    }

    k3_tree_level(std::string filename, size_type size)
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

    k3_tree_level(std::vector<point_type> &points, size_type size)
    {
        // Build structures
        build(points, size);
    }

    //*******************************************************//
    //*************** BASIC OPERATIONS **********************//
    //*******************************************************//

    //! Move assignment operator
    k3_tree_level& operator=(k3_tree_level&& tr)
    {
        if (this != &tr) {
            k_t = std::move(tr.k_t);
            k_l = std::move(tr.k_l);
            k_k1 = std::move(tr.k_k1);
            k_k2 = std::move(tr.k_k2);
            k_height = std::move(tr.k_height);
            k_t_rank = std::move(tr.k_t_rank);
            k_t_rank.set_vector(&k_t);
            k_max_height = std::move(tr.k_max_height);
            k_prev_ones = std::move(tr.k_prev_ones);

            k_r_leaf_points = std::move(tr.k_r_leaf_points);
            k_x_points = std::move(tr.k_x_points);
            k_y_points = std::move(tr.k_y_points);
            k_z_points = std::move(tr.k_z_points);
        }
        return *this;
    }

    //! Assignment operator
    k3_tree_level& operator=(k3_tree_level& tr)
    {
        if (this != &tr) {
            k_t = tr.k_t;
            k_l = tr.k_l;
            k_t_rank = tr.k_t_rank;
            k_t_rank.set_vector(&k_t);
            k_k1 = tr.k_k1;
            k_k2 = tr.k_k2;
            k_height = tr.k_height;
            k_max_height = tr.k_max_height;
            k_prev_ones = tr.k_prev_ones;

            k_r_leaf_points = tr.k_r_leaf_points;
            k_x_points = tr.k_x_points;
            k_y_points = tr.k_y_points;
            k_z_points = tr.k_z_points;
        }
        return *this;
    }

    //! Swap operator
    void swap(k3_tree_level& tr)
    {
        if (this != &tr) {
            std::swap(k_t, tr.k_t);
            std::swap(k_l, tr.k_l);
            util::swap_support(k_t_rank, tr.k_t_rank, &k_t, &(tr.k_t));
            std::swap(k_k1, tr.k_k1);
            std::swap(k_k2, tr.k_k2);
            std::swap(k_height, tr.k_height);
            std::swap(k_max_height, tr.k_max_height);
            std::swap(k_prev_ones, tr.k_prev_ones);

            k_r_leaf_points.swap(tr.k_r_leaf_points);
            k_x_points.swap(tr.k_x_points);
            k_y_points.swap(tr.k_y_points);
            k_z_points.swap(tr.k_z_points);
        }
    }

    //! Equal operator
    bool operator==(const k3_tree_level& tr) const
    {
        // TODO check the rank support equality?
        if (k_k1 != tr.k_k1 || k_k2 != tr.k_k2 || k_height != tr.k_height)
            return false;
        if (k_t.size() != tr.k_t.size() || k_l.size() != tr.k_l.size())
            return false;
        if (k_max_height != tr.k_max_height || k_prev_ones != tr.k_prev_ones)
            return false;
        if (k_r_leaf_points.size() != tr.k_r_leaf_points.size() ||
            k_x_points.size() != tr.k_x_points.size() ||
            k_y_points.size() != tr.k_y_points.size() ||
            k_z_points.size() != tr.k_z_points.size())
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
        pos_type x = pos_x, y = pos_y , z = pos_z;


        uint16_t level = std::min((uint)k_height-1, (uint)k_max_height);
        uint16_t l;
        for ( l = 0; l < level; l++) {
            submatrix_size_l /= k;
            node_pos = (x / submatrix_size_l) * k * k + y / submatrix_size_l * k + z / submatrix_size_l;
            node_pos += children_pos;

            if (k_t[node_pos] == 0) {
                return false; // Empty submatrix
            } else {
                // Go to next level
                children_pos = k_t_rank (node_pos+1) * k_k1_3;
            }

            // Calculate local position on the current submatrix
            x %= submatrix_size_l;
            y %= submatrix_size_l;
            z %= submatrix_size_l;
        }


        if (l == (k_height-1)) {
            // Last level
            submatrix_size_l /= k;
            node_pos = (x / submatrix_size_l) * k * k + y / submatrix_size_l * k + z / submatrix_size_l;
            node_pos += children_pos;
            return (k_l[node_pos - k_t.size()] == 1);
        } else {
            // Searching in leaves points array
            // Local positions
            size_type ones = k_t_rank(node_pos) - k_prev_ones;
            for (size_type p = k_r_leaf_points[ones]; p < k_r_leaf_points[ones+1]; p++) {
                if (x == k_x_points[p]) {
                    if (y == k_y_points[p]) {
                        if (z == k_z_points[p]) {
                            return true;
                        } else { if (z < k_z_points[p]) {break;}}
                    } else  { if (y < k_y_points[p]) {break;}}
                } else { if (x < k_x_points[p]) {break;}}
            }
            return false;

        }
    }

    size_type get_region(pos_type i_pos_x, pos_type i_pos_y, pos_type i_pos_z,
                           pos_type e_pos_x, pos_type e_pos_y, pos_type e_pos_z,
                         std::vector<point_type> &result) {

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
                                if (l < (k_max_height-1)) {
                                    // Continue with the search process
                                    q.push(t_part_tuple(x == x_i_b ? xi % sub_size : 0,
                                                        y == y_i_b ? yi % sub_size : 0,
                                                        z == z_i_b ? zi % sub_size : 0,
                                                        x == x_e_b ? xe % sub_size : sub_size - 1,
                                                        y == y_e_b ? ye % sub_size : sub_size - 1,
                                                        z == z_e_b ? ze % sub_size : sub_size - 1,
                                                        sub_size, bx + x * sub_size, by + y * sub_size,
                                                        bz + z * sub_size,
                                                        k_t_rank(pos + 1) * k_k1_3, l + 1));
                                } else {
                                    pos_type l_bx = bx + x * sub_size;
                                    pos_type l_by = by + y * sub_size;
                                    pos_type l_bz = bz + z * sub_size;

                                    size_type ones = k_t_rank(pos) - k_prev_ones;

                                    // Check each point of the child
                                    for (size_type p = k_r_leaf_points[ones]; p < k_r_leaf_points[ones+1]; p++) {
                                        pos_type p_x = l_bx + k_x_points[p];
                                        pos_type p_y = l_by + k_y_points[p];
                                        pos_type p_z = l_bz + k_z_points[p];

                                        if (p_x >= i_pos_x) {
                                            if (p_x <= e_pos_x) {
                                                if (p_y >= i_pos_y && p_y <= e_pos_y &&
                                                    p_z >= i_pos_z && p_z <= e_pos_z) {
                                                    // The point is within of the region
                                                    result.push_back(point_type(p_x, p_y, p_z));
                                                }
                                            } else {
                                                // There are no more points within the region
                                                break;
                                            }
                                        }
                                    } // END FOR add points
                                }
                            }
                        } else {
                            // Leaves nodes
                            if (k_l[pos - k_t.size()] == 1) {
                                result.push_back(point_type(bx + x, by + y, bz + z));
                            }
                        } // END IF check level
                    } // END FOR z
                } // END FOR y
            } // END FOR x
        } // END WHILE queue
        return result.size();
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

        written_bytes += write_member(K3_TREE_TYPE_LEVEL, out, child, "k3_tree_type");
        written_bytes += k_t.serialize(out, child, "t");
        written_bytes += k_l.serialize(out, child, "l");
        written_bytes += k_t_rank.serialize(out, child, "t_rank");
        written_bytes += write_member(k_k1, out, child, "k1");
        written_bytes += write_member(k_k2, out, child, "k2");
        written_bytes += write_member(k_height, out, child, "k_height");
        written_bytes += write_member(k_size, out, child, "size");
        written_bytes += write_member(k_max_height, out, child, "max_height");
        written_bytes += write_member(k_prev_ones, out, child, "prev_ones");

        written_bytes += k_r_leaf_points.serialize(out, child, "r_leaf_points");
        written_bytes += k_x_points.serialize(out, child, "x_points");
        written_bytes += k_y_points.serialize(out, child, "y_points");
        written_bytes += k_z_points.serialize(out, child, "z_points");

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
        read_member(k_max_height, in);
        read_member(k_prev_ones, in);

        k_r_leaf_points.load(in);
        k_x_points.load(in);
        k_y_points.load(in);
        k_z_points.load(in);
    }

    void print() {
        std::cout << "k3-tree with size " << k_size << " and height " << k_height << std::endl;
        std::cout << "Max level = " << k_max_height << std::endl;
        std::cout << "k1 = " << (uint)k_k1 << " | k2 = " << (uint)k_k2 << std::endl;
        std::cout << "Bitmap t (size " << k_t.size() << ") : ";
//        for (size_type p = 0; p < k_t.size(); p++) {
//            std::cout << k_t[p];
//        }
        std::cout << std::endl;
        std::cout << "Bitmap l (size " << k_l.size() << ") : ";
//        for (size_type p = 0; p < k_l.size(); p++) {
//            std::cout << k_l[p];
//        }
        std::cout << std::endl;
        std::cout << "Number of plain points stored: " << k_x_points.size() << std::endl;
        return;
    }


}; // ENC CLASS k3-tree

} // END NAMESPACE sdsl

#endif // INCLUDED_SDSL_K3_TREE
