/*  
 * Created by Fernando Silva on 8/06/18.
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

#ifndef INCLUDED_SDSL_K3_TREE_LIDAR_POINTS
#define INCLUDED_SDSL_K3_TREE_LIDAR_POINTS

#include <k3_tree_points.hpp>
#include <LASlib/inc/lasreader.hpp>

//! Namespace for the succint data structure library
namespace sdsl {

struct point_base {
    int X;
    int Y;
    int Z;
};

struct point_LIDAR_men : point_base{
    size_t pos;
};


struct point_LIDAR : point_base{
    ushort intensity;
    u_char return_number : 3;
    u_char number_of_returns : 3;
    u_char scan_direction_flag : 1;
    u_char edge_of_flight_line : 1;
    u_char classification;
    int8_t scan_angle_rank;
    u_char user_data;
    ushort point_source_ID;
};

struct point_LIDAR_result : point_LIDAR {
        double d_x; // Real x coordinate
        double d_y; // Real y coordinate
        double d_z; // Real z coordinate
};

void print_point_LIDAR(point_LIDAR_result point) {
    std::cout << "Point (" << point.X << ", " << point.Y << ", " << point.Z << ")" << std::endl;
    std::cout << "Intensity number: " << (uint)point.intensity << std::endl;
    std::cout << "Return number: " << (uint)point.return_number << std::endl;
    std::cout << "Number of returns: " << (uint)point.number_of_returns << std::endl;
    std::cout << "Scan direction flag: " << (uint)point.scan_direction_flag << std::endl;
    std::cout << "Edge of flight line: " << (uint)point.edge_of_flight_line << std::endl;
    std::cout << "Classification: " << (uint)point.classification << std::endl;
    std::cout << "Scan angle rank: " << (uint)point.scan_angle_rank << std::endl;
    std::cout << "User data: " << (uint)point.user_data << std::endl;
    std::cout << "Point source ID: " << (uint)point.point_source_ID << std::endl;

}

template<uint8_t t_k1=2, uint8_t t_k2=2, size_t t_min_points=10,
        typename t_bv=bit_vector,
        typename t_rank=typename t_bv::rank_1_type,
        typename t_select=typename t_bv::select_1_type,
        typename t_point_vec=dac_vector_dp<>>
class k3_tree_LIDAR_points : k3_tree_points<t_k1, t_k2, t_min_points, t_bv, t_rank, t_select, t_point_vec, double >
{
    public:
        typedef k3_tree_base<>::size_type size_type;
        typedef k3_tree_base<>::pos_type pos_type;
        typedef k3_tree_base<>::point_type point_type;

    private:
        // LIDAR info
        size_type k_n_points;
        double k_min_x;
        double k_min_y;
        double k_min_z;
        double k_max_x;
        double k_max_y;
        double k_max_z;
        double k_x_scale_factor;
        double k_y_scale_factor;
        double k_z_scale_factor;
        double k_d_x_offset;
        double k_d_y_offset;
        double k_d_z_offset;
        long long k_offset_x;
        long long k_offset_y;
        long long k_offset_z;

        // LIDAR attributes
        t_point_vec k_c_intensity;
        t_point_vec k_c_return_number;
        t_point_vec k_c_n_return_pulse;
        t_bv        k_c_scan_direction_flag;
        t_bv        k_c_edge;
        t_point_vec k_c_classification;
        t_point_vec k_c_scan_angle;
        int8_t k_scan_angle_rank_delta;
        t_point_vec k_c_user_data;
        t_point_vec k_c_point_source;


    public:
        const double &min_x = k_min_x;
        const double &min_y = k_min_y;
        const double &min_z = k_min_z;
        const double &max_x = k_max_x;
        const double &max_y = k_max_y;
        const double &max_z = k_max_z;

    protected:

    void init_att(size_type n_points) {
        k_n_points = n_points;
        k_scan_angle_rank_delta = 90;
    }

    void copy_info_LIDAR(LASreader* lasreader) {
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
        k_d_x_offset = lasreader->header.x_offset;
        k_d_y_offset = lasreader->header.y_offset;
        k_d_z_offset = lasreader->header.z_offset;

        // Calculate real offset of each dimension
        k_offset_x = std::floor((k_min_x - k_d_x_offset) / k_x_scale_factor);
        k_offset_y = std::floor((k_min_y - k_d_y_offset) / k_y_scale_factor);
        k_offset_z = std::floor((k_min_z - k_d_z_offset) / k_z_scale_factor);
    }

    void retrieve_point_information(point_LIDAR_result &point, pos_type pos_x, pos_type pos_y, pos_type pos_z, uint att_pos) {
        point.X = pos_x + k_offset_x;
        point.Y = pos_y + k_offset_y;
        point.Z = pos_z + k_offset_z;
        point.d_x = (point.X * k_x_scale_factor) + k_d_x_offset;
        point.d_y = (point.Y * k_y_scale_factor) + k_d_y_offset;
        point.d_z = (point.Z * k_z_scale_factor) + k_d_z_offset;
        point.intensity = k_c_intensity[att_pos];
        point.return_number = k_c_return_number[att_pos];
        point.number_of_returns = k_c_n_return_pulse[att_pos];
        point.scan_direction_flag = k_c_scan_direction_flag[att_pos];
        point.edge_of_flight_line = k_c_edge[att_pos];
        point.classification = k_c_classification[att_pos];
        point.scan_angle_rank = k_c_scan_angle[att_pos] + k_scan_angle_rank_delta;
        point.user_data = k_c_user_data[att_pos];
        point.point_source_ID = k_c_point_source[att_pos];
    }

    void retrieve_point_information_no_int(point_LIDAR_result &point, pos_type pos_x, pos_type pos_y, pos_type pos_z, uint att_pos) {
        point.X = pos_x + k_offset_x;
        point.Y = pos_y + k_offset_y;
        point.Z = pos_z + k_offset_z;
        point.d_x = (point.X * k_x_scale_factor) + k_d_x_offset;
        point.d_y = (point.Y * k_y_scale_factor) + k_d_y_offset;
        point.d_z = (point.Z * k_z_scale_factor) + k_d_z_offset;
//        point.intensity = k_c_intensity[att_pos];
        point.return_number = k_c_return_number[att_pos];
        point.number_of_returns = k_c_n_return_pulse[att_pos];
        point.scan_direction_flag = k_c_scan_direction_flag[att_pos];
        point.edge_of_flight_line = k_c_edge[att_pos];
        point.classification = k_c_classification[att_pos];
        point.scan_angle_rank = k_c_scan_angle[att_pos] + k_scan_angle_rank_delta;
        point.user_data = k_c_user_data[att_pos];
        point.point_source_ID = k_c_point_source[att_pos];
    }


    //*******************************************************//
    //********************** HELPERS ************************//
    //*******************************************************//
    // Sort points
    static bool sort_points_LIDAR(const point_base &p1, const point_base &p2) {
        // X coordinate
        if (p1.X != p2.X) {
            return p1.X < p2.X;
        }

        // Y coordinate
        if (p1.Y != p2.Y) {
            return p1.Y < p2.Y;
        }

        // Z coordinate
        if (p1.Z != p2.Z) {
            return p1.Z < p2.Z;
        }

        return false;
    }

    //*******************************************************//
    //********************* BUILD TREE **********************//
    //*******************************************************//
    void build(std::vector<point_LIDAR>& points) {

        // (Initial position, end position, submatrix size, base x coordinate, base y coordinate, base z coordinate)
        typedef std::tuple<pos_type, pos_type, size_type, pos_type, pos_type, pos_type > t_part_tuple;

        // Init bit_vectors
        bit_vector k_t_ = bit_vector(this->k_k1_3 * this->k_height * points.size(), 0);
        bit_vector k_h_p_ = bit_vector(this->k_k1_3 * this->k_height * points.size(), 0);
        bit_vector k_l_;
        bit_vector k_s_leaf_points_ = bit_vector(points.size());


        // Init point vector
        std::vector<point_type> leaf_points;

        // Init attribute vectors
        int_vector<16> k_intensity(k_n_points);
        int_vector<3> k_return_number(k_n_points);
        int_vector<3> k_n_return_pulse(k_n_points);
        int_vector<1> k_scan_direction_flag(k_n_points);
        int_vector<1> k_edge(k_n_points);
        int_vector<8> k_classification(k_n_points);
        int_vector<8> k_scan_angle(k_n_points);
        int_vector<8> k_user_data(k_n_points);
        int_vector<16> k_point_source(k_n_points);

        // Init queue
        std::queue<t_part_tuple> q;
        pos_type t = 0, last_level = 0, p_p = 0, h_p = 0, att_pos = 0;
        pos_type init_p, end_p, x_0, y_0, z_0, it, t_x, t_y, t_z;
        size_type sub_size = std::pow(this->k_k1, this->k_height - 1);
        std::vector<pos_type > pos_by_chunk(this->k_k1_3 + 1, 0);

        q.push(t_part_tuple(0, points.size(), sub_size, 0, 0, 0));

        while (!q.empty()) {
            std::vector<pos_type> amount_by_chunk(this->k_k1_3, 0);
            std::tie(init_p, end_p, sub_size, x_0, y_0, z_0) = q.front();

            q.pop();

            // Get size for each chunk
            for (it = init_p; it < end_p; it++) {
                amount_by_chunk[this->get_chunk_idx(
                        points[it].X,
                        points[it].Y,
                        points[it].Z,
                        x_0, y_0, z_0, sub_size, this->k_k1)] += 1;
            }
            if (sub_size == 1) {
                if (last_level == 0) {
                    last_level = t;
                    k_l_ = bit_vector(k_t_.size() - last_level, 0);
                    k_t_.resize(last_level);
                    k_h_p_.resize(h_p);
                    last_level = 1; // if t was 0
                    t = 0; // Restart counter as we're storing at k_l_ now.
                }

                for (it = 0; it < this->k_k1_3; it++,t++)
                    if (amount_by_chunk[it] != 0)
                        k_l_[t] = 1;

                for (it = init_p; it < end_p; it++) {
                    k_intensity[att_pos] = points[it].intensity;
                    k_return_number[att_pos] = points[it].return_number;
                    k_n_return_pulse[att_pos] = points[it].number_of_returns;
                    k_scan_direction_flag[att_pos] = points[it].scan_direction_flag;
                    k_edge[att_pos] = points[it].edge_of_flight_line;
                    k_classification[att_pos] = points[it].classification;
                    k_scan_angle[att_pos] = points[it].scan_angle_rank - k_scan_angle_rank_delta;
                    k_user_data[att_pos] = points[it].user_data;
                    k_point_source[att_pos] = points[it].point_source_ID;
                    att_pos++;
                }
                // At l == 1 we do not put new elements at the queue.
                continue;
            }

            // Set starting position in the vector for each chunkpoints
            pos_by_chunk[0] = init_p;
            for (it = 1; it < this->k_k1_3; it++)
                pos_by_chunk[it] =
                        pos_by_chunk[it - 1] + amount_by_chunk[it - 1];
            // To handle the last case when it = k_2 - 1
            pos_by_chunk[this->k_k1_3] = end_p;
            // Push to the queue every non zero elements chunk
            for (it = 0; it < this->k_k1_3; it++,t++) {
                // If not empty chunk, set bit to 1
                if (amount_by_chunk[it] >= this->k_min_points) {
                    t_x = it / (this->k_k1 * this->k_k1);
                    t_y = (it / this->k_k1) % this->k_k1;
                    t_z = it % this->k_k1;
                    k_t_[t] = 1;
                    q.push(t_part_tuple(pos_by_chunk[it],
                                        pos_by_chunk[it + 1],
                                        sub_size / this->k_k1,
                                        x_0 + t_x * sub_size,
                                        y_0 + t_y * sub_size,
                                        z_0 + t_z * sub_size));
                } else {
                    if (amount_by_chunk[it] != 0) {
                        k_h_p_[h_p] = 1;
                    }
                    h_p++;
                }
            }
            size_type chunk;

            // Sort edges' vector
            for (unsigned ch = 0; ch < this->k_k1_3; ch++) {
                size_type be = ch == 0 ? init_p : pos_by_chunk[ch - 1];
                for (it = pos_by_chunk[ch]; it < be + amount_by_chunk[ch];) {
                    chunk = this->get_chunk_idx(
                            points[it].X,
                            points[it].Y,
                            points[it].Z,
                            x_0, y_0, z_0, sub_size, this->k_k1);

                    if (pos_by_chunk[chunk] != it)
                        std::iter_swap(points.begin() + it,
                                       points.begin() + pos_by_chunk[chunk]);
                    else
                        it++;
                    pos_by_chunk[chunk]++;
                }
            }

            // Add leaf points
            for (unsigned ch = 0; ch < this->k_k1_3; ch++) {
                if (amount_by_chunk[ch] != 0 && amount_by_chunk[ch] < this->k_min_points) {
                    // Sort leaf
                    std::sort(points.begin() + (pos_by_chunk[ch] - amount_by_chunk[ch]),
                              points.begin() + pos_by_chunk[ch], sort_points_LIDAR);
                    for (it =  pos_by_chunk[ch] - amount_by_chunk[ch]; it < pos_by_chunk[ch]; it++) {
                        leaf_points.push_back(point_type(points[it].X % sub_size,
                                                         points[it].Y % sub_size,
                                                         points[it].Z % sub_size));

                        k_s_leaf_points_[leaf_points.size()-1] = (it == (pos_by_chunk[ch] - 1) ? 1 : 0);

                        // Store attributes
                        k_intensity[att_pos] = points[it].intensity;
                        k_return_number[att_pos] = points[it].return_number;
                        k_n_return_pulse[att_pos] = points[it].number_of_returns;
                        k_scan_direction_flag[att_pos] = points[it].scan_direction_flag;
                        k_edge[att_pos] = points[it].edge_of_flight_line;
                        k_classification[att_pos] = points[it].classification;
                        k_scan_angle[att_pos] = points[it].scan_angle_rank - k_scan_angle_rank_delta;
                        k_user_data[att_pos] = points[it].user_data;
                        k_point_source[att_pos] = points[it].point_source_ID;
                        att_pos++;
                    } // END FOR add point
//                    std::sort(leaf_points.end() - amount_by_chunk[ch], leaf_points.end(), k3_tree_points<>::sort_points);
                } // END FOR submatrix
            }
        }

        if (last_level == 0) {
            k_t_.resize(t);
            k_l_.resize(0);
        } else {
            k_l_.resize(t);
        }

        k_h_p_.resize(h_p);

        //k2_tree_ns::build_template_vector<t_bv>(k_t_, k_l_, k_t, k_l);
        this->k_t = t_bv(k_t_);
        this->k_h_p = t_bv(k_h_p_);
        this->k_l = t_bv(k_l_);

        this->k_t_rank = t_rank(&this->k_t);
        this->k_h_p_rank = t_rank(&this->k_h_p);

        // Create DAC vectors
//        k_r_leaf_points = t_point_vec(r_leaf_points_);
        this->k_s_leaf_points.resize(leaf_points.size());
        this->k_s_leaf_points = t_bv(k_s_leaf_points_);
        this->k_s_leaf_points_select = t_select(&this->k_s_leaf_points);

        // TODO optimize this!!!
        std::vector<pos_type> pos(leaf_points.size());
        for (size_t p  = 0; p < leaf_points.size(); p ++){
            pos[p] = std::get<0>(leaf_points[p]);
        }
        this->k_x_points = t_point_vec(pos);

        for (size_t p  = 0; p < leaf_points.size(); p ++){
            pos[p] = std::get<1>(leaf_points[p]);
        }
        this->k_y_points = t_point_vec(pos);

        for (size_t p  = 0; p < leaf_points.size(); p ++){
            pos[p] = std::get<2>(leaf_points[p]);
        }
        this->k_z_points = t_point_vec(pos);

        // Compress attributes
        k_c_intensity = t_point_vec(k_intensity);
        k_c_return_number = t_point_vec(k_return_number);
        k_c_n_return_pulse = t_point_vec(k_n_return_pulse);
        k_c_scan_direction_flag = t_bv(k_scan_direction_flag);
        k_c_edge = t_bv(k_edge);
        k_c_classification = t_point_vec(k_classification);
        k_c_scan_angle = t_point_vec(k_scan_angle);
        k_c_user_data = t_point_vec(k_user_data);
        k_c_point_source = t_point_vec(k_point_source);
    }


    //*******************************************************//
    //************** MIN MEMORY VERSION *********************//
    //*******************************************************//

    void build_men(LASreader* lasreader, std::vector<point_LIDAR_men>& points) {

        // (Initial position, end position, submatrix size, base x coordinate, base y coordinate, base z coordinate)
        typedef std::tuple<pos_type, pos_type, size_type, pos_type, pos_type, pos_type > t_part_tuple;

        // Init bit_vectors
        bit_vector k_t_ = bit_vector(this->k_k1_3 * this->k_height * points.size(), 0);
        bit_vector k_h_p_ = bit_vector(this->k_k1_3 * this->k_height * points.size(), 0);
        bit_vector k_l_;
        bit_vector k_s_leaf_points_ = bit_vector(points.size());


        // Init point vector
        std::vector<point_type> leaf_points;

        // Init attribute vectors
        int_vector<16> k_intensity(k_n_points);
        int_vector<3> k_return_number(k_n_points);
        int_vector<3> k_n_return_pulse(k_n_points);
        int_vector<1> k_scan_direction_flag(k_n_points);
        int_vector<1> k_edge(k_n_points);
        int_vector<8> k_classification(k_n_points);
        int_vector<8> k_scan_angle(k_n_points);
        int_vector<8> k_user_data(k_n_points);
        int_vector<16> k_point_source(k_n_points);

        // Init queue
        std::queue<t_part_tuple> q;
        pos_type t = 0, last_level = 0, p_p = 0, h_p = 0, att_pos = 0;
        pos_type init_p, end_p, x_0, y_0, z_0, it, t_x, t_y, t_z;
        size_type sub_size = std::pow(this->k_k1, this->k_height - 1);
        std::vector<pos_type > pos_by_chunk(this->k_k1_3 + 1, 0);

        q.push(t_part_tuple(0, points.size(), sub_size, 0, 0, 0));

        while (!q.empty()) {
            std::vector<pos_type> amount_by_chunk(this->k_k1_3, 0);
            std::tie(init_p, end_p, sub_size, x_0, y_0, z_0) = q.front();

            q.pop();

            // Get size for each chunk
            for (it = init_p; it < end_p; it++) {
                amount_by_chunk[this->get_chunk_idx(
                        points[it].X,
                        points[it].Y,
                        points[it].Z,
                        x_0, y_0, z_0, sub_size, this->k_k1)] += 1;
            }
            if (sub_size == 1) {
                if (last_level == 0) {
                    last_level = t;
                    k_l_ = bit_vector(k_t_.size() - last_level, 0);
                    k_t_.resize(last_level);
                    k_h_p_.resize(h_p);
                    last_level = 1; // if t was 0
                    t = 0; // Restart counter as we're storing at k_l_ now.
                }

                for (it = 0; it < this->k_k1_3; it++,t++)
                    if (amount_by_chunk[it] != 0)
                        k_l_[t] = 1;

                for (it = init_p; it < end_p; it++) {
                    lasreader->seek(points[it].pos);
                    k_intensity[att_pos] = lasreader->point.intensity;
                    k_return_number[att_pos] = lasreader->point.return_number;
                    k_n_return_pulse[att_pos] = lasreader->point.number_of_returns;
                    k_scan_direction_flag[att_pos] = lasreader->point.scan_direction_flag;
                    k_edge[att_pos] = lasreader->point.edge_of_flight_line;
                    k_classification[att_pos] = lasreader->point.classification;
                    k_scan_angle[att_pos] = lasreader->point.scan_angle_rank - k_scan_angle_rank_delta;
                    k_user_data[att_pos] = lasreader->point.user_data;
                    k_point_source[att_pos] = lasreader->point.point_source_ID;
                    att_pos++;
                }
                // At l == 1 we do not put new elements at the queue.
                continue;
            }

            // Set starting position in the vector for each chunkpoints
            pos_by_chunk[0] = init_p;
            for (it = 1; it < this->k_k1_3; it++)
                pos_by_chunk[it] =
                        pos_by_chunk[it - 1] + amount_by_chunk[it - 1];
            // To handle the last case when it = k_2 - 1
            pos_by_chunk[this->k_k1_3] = end_p;
            // Push to the queue every non zero elements chunk
            for (it = 0; it < this->k_k1_3; it++,t++) {
                // If not empty chunk, set bit to 1
                if (amount_by_chunk[it] >= this->k_min_points) {
                    t_x = it / (this->k_k1 * this->k_k1);
                    t_y = (it / this->k_k1) % this->k_k1;
                    t_z = it % this->k_k1;
                    k_t_[t] = 1;
                    q.push(t_part_tuple(pos_by_chunk[it],
                                        pos_by_chunk[it + 1],
                                        sub_size / this->k_k1,
                                        x_0 + t_x * sub_size,
                                        y_0 + t_y * sub_size,
                                        z_0 + t_z * sub_size));
                } else {
                    if (amount_by_chunk[it] != 0) {
                        k_h_p_[h_p] = 1;
                    }
                    h_p++;
                }
            }
            size_type chunk;

            // Sort edges' vector
            for (unsigned ch = 0; ch < this->k_k1_3; ch++) {
                size_type be = ch == 0 ? init_p : pos_by_chunk[ch - 1];
                for (it = pos_by_chunk[ch]; it < be + amount_by_chunk[ch];) {
                    chunk = this->get_chunk_idx(
                            points[it].X,
                            points[it].Y,
                            points[it].Z,
                            x_0, y_0, z_0, sub_size, this->k_k1);

                    if (pos_by_chunk[chunk] != it)
                        std::iter_swap(points.begin() + it,
                                       points.begin() + pos_by_chunk[chunk]);
                    else
                        it++;
                    pos_by_chunk[chunk]++;
                }
            }

            // Add leaf points
            for (unsigned ch = 0; ch < this->k_k1_3; ch++) {
                if (amount_by_chunk[ch] != 0 && amount_by_chunk[ch] < this->k_min_points) {
                    // Sort leaf
                    std::sort(points.begin() + (pos_by_chunk[ch] - amount_by_chunk[ch]),
                              points.begin() + pos_by_chunk[ch], sort_points_LIDAR);
                    for (it =  pos_by_chunk[ch] - amount_by_chunk[ch]; it < pos_by_chunk[ch]; it++) {
                        leaf_points.push_back(point_type(points[it].X % sub_size,
                                                         points[it].Y % sub_size,
                                                         points[it].Z % sub_size));

                        k_s_leaf_points_[leaf_points.size()-1] = (it == (pos_by_chunk[ch] - 1) ? 1 : 0);

                        // Store attributes
                        lasreader->seek(points[it].pos);
                        k_intensity[att_pos] = lasreader->point.intensity;
                        k_return_number[att_pos] = lasreader->point.return_number;
                        k_n_return_pulse[att_pos] = lasreader->point.number_of_returns;
                        k_scan_direction_flag[att_pos] = lasreader->point.scan_direction_flag;
                        k_edge[att_pos] = lasreader->point.edge_of_flight_line;
                        k_classification[att_pos] = lasreader->point.classification;
                        k_scan_angle[att_pos] = lasreader->point.scan_angle_rank - k_scan_angle_rank_delta;
                        k_user_data[att_pos] = lasreader->point.user_data;
                        k_point_source[att_pos] = lasreader->point.point_source_ID;
                        att_pos++;
                    } // END FOR add point
//                    std::sort(leaf_points.end() - amount_by_chunk[ch], leaf_points.end(), k3_tree_points<>::sort_points);
                } // END FOR submatrix
            }
        }

        if (last_level == 0) {
            k_t_.resize(t);
            k_l_.resize(0);
        } else {
            k_l_.resize(t);
        }

        k_h_p_.resize(h_p);

        //k2_tree_ns::build_template_vector<t_bv>(k_t_, k_l_, k_t, k_l);
        this->k_t = t_bv(k_t_);
        this->k_h_p = t_bv(k_h_p_);
        this->k_l = t_bv(k_l_);

        this->k_t_rank = t_rank(&this->k_t);
        this->k_h_p_rank = t_rank(&this->k_h_p);

        // Create DAC vectors
//        k_r_leaf_points = t_point_vec(r_leaf_points_);
        this->k_s_leaf_points.resize(leaf_points.size());
        this->k_s_leaf_points = t_bv(k_s_leaf_points_);
        this->k_s_leaf_points_select = t_select(&this->k_s_leaf_points);

        // TODO optimize this!!!
        std::vector<pos_type> pos(leaf_points.size());
        for (size_t p  = 0; p < leaf_points.size(); p ++){
            pos[p] = std::get<0>(leaf_points[p]);
        }
        this->k_x_points = t_point_vec(pos);

        for (size_t p  = 0; p < leaf_points.size(); p ++){
            pos[p] = std::get<1>(leaf_points[p]);
        }
        this->k_y_points = t_point_vec(pos);

        for (size_t p  = 0; p < leaf_points.size(); p ++){
            pos[p] = std::get<2>(leaf_points[p]);
        }
        this->k_z_points = t_point_vec(pos);

        // Compress attributes
        k_c_intensity = t_point_vec(k_intensity);
        k_c_return_number = t_point_vec(k_return_number);
        k_c_n_return_pulse = t_point_vec(k_n_return_pulse);
        k_c_scan_direction_flag = t_bv(k_scan_direction_flag);
        k_c_edge = t_bv(k_edge);
        k_c_classification = t_point_vec(k_classification);
        k_c_scan_angle = t_point_vec(k_scan_angle);
        k_c_user_data = t_point_vec(k_user_data);
        k_c_point_source = t_point_vec(k_point_source);
    }


    //*******************************************************//
    //******************** QUERY HELPER *********************//
    //*******************************************************//

    bool get_helper(pos_type pos_x, pos_type pos_y, pos_type pos_z) {

        if (this->k_t.size() == 0) {
            // Empty matrix
            return false;
        }

        if (pos_x > this->k_size || pos_y > this->k_size || pos_z > this->k_size) {
            return false;
        }

        // Size of the submatrix at the current level
        size_type submatrix_size_l = this->k_size;
        size_type node_pos;
        size_type children_pos = 0;
        uint8_t k = this->k_k1;
        pos_type x = pos_x, y = pos_y , z = pos_z;


        for (uint16_t l = 0; l < this->k_height-1; l++) {
            submatrix_size_l /= k;
            node_pos = (x / submatrix_size_l) * k * k + y / submatrix_size_l * k + z / submatrix_size_l;
            node_pos += children_pos;

            if (this->k_t[node_pos] == 0) {
                size_type zeroes = node_pos - this->k_t_rank(node_pos);
                if (this->k_h_p[zeroes] == 0) {
                    return false; // Empty submatrix
                } else {
                    // Local positions
                    x %= submatrix_size_l;
                    y %= submatrix_size_l;
                    z %= submatrix_size_l;
                    size_type ones = this->k_h_p_rank(zeroes);
                    size_type p_init = ones == 0 ? 0 : this->k_s_leaf_points_select(ones)+1;
                    size_type p_end = this->k_s_leaf_points_select(ones+1)+1;
//                    for (size_type p = k_r_leaf_points[ones]; p < k_r_leaf_points[ones+1]; p++) {
//                    size_type x_point, y_point, z_point;
                    size_type x_point, y_point, z_point;
                    for (size_type p = p_init; p < p_end; p++) {
                        x_point = this->k_x_points[p];
                        if (x == x_point) {
                            y_point = this->k_y_points[p];
                            if (y == y_point) {
                                z_point = this->k_z_points[p];
                                if (z == z_point) {
                                    return true;
                                } else { if (z < z_point) {break;}}
                            } else  { if (y < y_point) {break;}}
                        } else { if (x < x_point) {break;}}
                    }
                    return false;
                }
            } else {
                // Go to next level
                children_pos = this->k_t_rank (node_pos+1) * this->k_k1_3;
            }

            // Calculate local position on the current submatrix
            x %= submatrix_size_l;
            y %= submatrix_size_l;
            z %= submatrix_size_l;
        }

        // Last level
        submatrix_size_l /= k;
        node_pos = (x / submatrix_size_l) * k * k + y / submatrix_size_l * k + z / submatrix_size_l;
        node_pos += children_pos;
        return (this->k_l[node_pos - this->k_t.size()] == 1);
    }

    // Return information about a point
    bool get_attr_helper(pos_type pos_x, pos_type pos_y, pos_type pos_z, point_LIDAR_result &point) {

        if (this->k_t.size() == 0) {
            // Empty matrix
            return false;
        }

        if (pos_x > this->k_size || pos_y > this->k_size || pos_z > this->k_size) {
            return false;
        }

        // Size of the submatrix at the current level
        size_type submatrix_size_l = this->k_size;
        size_type node_pos;
        size_type children_pos = 0;
        uint8_t k = this->k_k1;
        pos_type x = pos_x, y = pos_y , z = pos_z;


        for (uint16_t l = 0; l < this->k_height-1; l++) {
            submatrix_size_l /= k;
            node_pos = (x / submatrix_size_l) * k * k + y / submatrix_size_l * k + z / submatrix_size_l;
            node_pos += children_pos;

            if (this->k_t[node_pos] == 0) {
                size_type zeroes = node_pos - this->k_t_rank(node_pos);
                if (this->k_h_p[zeroes] == 0) {
                    return false; // Empty submatrix
                } else {
                    // Local positions
                    x %= submatrix_size_l;
                    y %= submatrix_size_l;
                    z %= submatrix_size_l;
                    size_type ones = this->k_h_p_rank(zeroes);
                    size_type p_init = ones == 0 ? 0 : this->k_s_leaf_points_select(ones)+1;
                    size_type p_end = this->k_s_leaf_points_select(ones+1)+1;
//                    for (size_type p = k_r_leaf_points[ones]; p < k_r_leaf_points[ones+1]; p++) {
                    size_type x_point, y_point, z_point;
                    for (size_type p = p_init; p < p_end; p++) {
                        x_point = this->k_x_points[p];
                        if (x == x_point) {
                            y_point = this->k_y_points[p];
                            if (y == y_point) {
                                z_point = this->k_z_points[p];
                                if (z == z_point) {
                                    retrieve_point_information(point, pos_x, pos_y, pos_z, p);
                                    return true;
                                } else { if (z < z_point) {break;}}
                            } else  { if (y < y_point) {break;}}
                        } else { if (x < x_point) {break;}}
                    }
                    return false;
                } // END IF k_t[node_pos] == 0
            } else {
                // Go to next level
                children_pos = this->k_t_rank (node_pos+1) * this->k_k1_3;
            }

            // Calculate local position on the current submatrix
            x %= submatrix_size_l;
            y %= submatrix_size_l;
            z %= submatrix_size_l;
        }

        // Last level
        submatrix_size_l /= k;
        node_pos = (x / submatrix_size_l) * k * k + y / submatrix_size_l * k + z / submatrix_size_l;
        node_pos += children_pos;

        if (this->k_l[node_pos - this->k_t.size()] == 1) {

            size_type p = this->k_x_points.size() + (node_pos - this->k_t.size()); // TODO fix this
            retrieve_point_information(point, pos_x, pos_y, pos_z, p);
            return true;
        }
        return false;
    }

    size_type get_region_helper(pos_type i_pos_x, pos_type i_pos_y, pos_type i_pos_z,
                         pos_type e_pos_x, pos_type e_pos_y, pos_type e_pos_z,
                         std::vector<point_type> &result) {

        if (i_pos_x > this->k_size || i_pos_y > this->k_size || i_pos_z > this->k_size) {
            return 0;
        }

        typedef std::tuple<pos_type, pos_type, pos_type, pos_type, pos_type, pos_type,
                size_type, pos_type, pos_type, pos_type, size_type, uint16_t> t_part_tuple;
        std::stack<t_part_tuple> q;

        q.push(t_part_tuple(i_pos_x, i_pos_y, i_pos_z, e_pos_x, e_pos_y, e_pos_z,
                            this->k_size, 0, 0, 0, 0, 0));


        uint8_t k = this->k_k1;
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

                        if (l < (this->k_height-1)) {
                            // Internal nodes
                            if (this->k_t[pos] == 1) {
                                // Continue with the search process
                                q.push(t_part_tuple(x == x_i_b ? xi % sub_size : 0,
                                                    y == y_i_b ? yi % sub_size : 0,
                                                    z == z_i_b ? zi % sub_size : 0,
                                                    x == x_e_b ? xe % sub_size : sub_size - 1,
                                                    y == y_e_b ? ye % sub_size : sub_size - 1,
                                                    z == z_e_b ? ze % sub_size : sub_size - 1,
                                                    sub_size, bx + x * sub_size, by + y * sub_size,  bz + z * sub_size,
                                                    this->k_t_rank(pos + 1) * this->k_k1_3, l+1));

                            } else {
                                size_type zeroes = pos - this->k_t_rank(pos);
                                if (this->k_h_p[zeroes] == 0) {
                                    continue; // Empty submatrix
                                } else {
                                    // Base positions
                                    pos_type l_bx = bx + x * sub_size;
                                    pos_type l_by = by + y * sub_size;
                                    pos_type l_bz = bz + z * sub_size;

                                    size_type ones = this->k_h_p_rank(zeroes);
                                    size_type p_init = ones == 0 ? 0 : this->k_s_leaf_points_select(ones)+1;
                                    size_type p_end = this->k_s_leaf_points_select(ones+1)+1;
//                    for (size_type p = k_r_leaf_points[ones]; p < k_r_leaf_points[ones+1]; p++) {
                                    for (size_type p = p_init; p < p_end; p++) {

                                        pos_type p_x = l_bx + this->k_x_points[p];
                                        pos_type p_y = l_by + this->k_y_points[p];
                                        pos_type p_z = l_bz + this->k_z_points[p];

                                        if (p_x >= i_pos_x) {
                                            if (p_x <= e_pos_x) {
                                                if (p_y >= i_pos_y && p_y <= e_pos_y &&
                                                    p_z >= i_pos_z && p_z <= e_pos_z) {
                                                    // The point is within of the region
                                                    result.push_back(point_type(p_x + k_offset_x, p_y + k_offset_y, p_z + k_offset_z));
                                                }
                                            } else {
                                                // There are no more points within the region
                                                break;
                                            }
                                        } // END IF p_x
                                    } // END FOR p_init to p_end
                                } // END IF k_t[node_pos] == 0
                            }// ENF IF t[pos] == 1
                        } else {
                            // Leaves nodes
                            if (this->k_l[pos - this->k_t.size()] == 1) {
                                result.push_back(point_type(bx + x, by + y, bz + z));
                            }
                        } // END IF check level
                    } // END FOR z
                } // END FOR y
            } // END FOR x
        } // END WHILE queue
        return result.size();
    }

    size_type get_region_attr_helper(pos_type i_pos_x, pos_type i_pos_y, pos_type i_pos_z,
                                pos_type e_pos_x, pos_type e_pos_y, pos_type e_pos_z,
                                std::vector<point_LIDAR_result> &result) {

        if (i_pos_x > this->k_size || i_pos_y > this->k_size || i_pos_z > this->k_size) {
            return 0;
        }

        typedef std::tuple<pos_type, pos_type, pos_type, pos_type, pos_type, pos_type,
                size_type, pos_type, pos_type, pos_type, size_type, uint16_t> t_part_tuple;
        std::stack<t_part_tuple> q;

        q.push(t_part_tuple(i_pos_x, i_pos_y, i_pos_z, e_pos_x, e_pos_y, e_pos_z,
                            this->k_size, 0, 0, 0, 0, 0));


        uint8_t k = this->k_k1;
        pos_type x_i_b, x_e_b, y_i_b, y_e_b, z_i_b, z_e_b;  // First and end child
        pos_type xi, xe, yi, ye, zi, ze;                    // Local positions
        pos_type bx, by, bz;                                // Bases positions
        size_type sub_size;                                 // Size of each submatrix
        size_type pos, pos_children;
        uint16_t l;

        while (!q.empty()) {
            std::tie(xi, yi, zi, xe, ye, ze, sub_size, bx, by, bz, pos_children, l) = q.top();
            q.pop();

//            std::cout << "sub_size: " << sub_size << std::endl;

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

                        if (l < (this->k_height-1)) {
                            // Internal nodes
                            if (this->k_t[pos] == 1) {
                                // Continue with the search process
                                q.push(t_part_tuple(x == x_i_b ? xi % sub_size : 0,
                                                    y == y_i_b ? yi % sub_size : 0,
                                                    z == z_i_b ? zi % sub_size : 0,
                                                    x == x_e_b ? xe % sub_size : sub_size - 1,
                                                    y == y_e_b ? ye % sub_size : sub_size - 1,
                                                    z == z_e_b ? ze % sub_size : sub_size - 1,
                                                    sub_size, bx + x * sub_size, by + y * sub_size,  bz + z * sub_size,
                                                    this->k_t_rank(pos + 1) * this->k_k1_3, l+1));

                            } else {
                                size_type zeroes = pos - this->k_t_rank(pos);
                                if (this->k_h_p[zeroes] == 0) {
                                    continue; // Empty submatrix
                                } else {
                                    // Base positions
                                    pos_type l_bx = bx + x * sub_size;
                                    pos_type l_by = by + y * sub_size;
                                    pos_type l_bz = bz + z * sub_size;

                                    size_type ones = this->k_h_p_rank(zeroes);
                                    size_type p_init = ones == 0 ? 0 : this->k_s_leaf_points_select(ones)+1;
                                    size_type p_end = this->k_s_leaf_points_select(ones+1)+1;
//                    for (size_type p = k_r_leaf_points[ones]; p < k_r_leaf_points[ones+1]; p++) {

                                    for (size_type p = p_init; p < p_end; p++) {

                                        pos_type p_x = l_bx + this->k_x_points[p];
                                        pos_type p_y = l_by + this->k_y_points[p];
                                        pos_type p_z = l_bz + this->k_z_points[p];

                                        if (p_x >= i_pos_x) {
                                            if (p_x <= e_pos_x) {
                                                if (p_y >= i_pos_y && p_y <= e_pos_y &&
                                                    p_z >= i_pos_z && p_z <= e_pos_z) {
                                                    // The point is within of the region
                                                    point_LIDAR_result point;
                                                    retrieve_point_information(point, p_x, p_y, p_z, p);
                                                    result.push_back(point);
                                                }
                                            } else {
                                                // There are no more points within the region
                                                break;
                                            }
                                        } // END IF p_x
                                    } // END FOR p_init to p_end
                                } // END IF k_t[node_pos] == 0
                            }// ENF IF t[pos] == 1
                        } else {
                            // Leaves nodes
                            if (this->k_l[pos - this->k_t.size()] == 1) {
                                point_LIDAR_result point;
                                // Base positions
                                pos_type l_bx = bx + x * sub_size;
                                pos_type l_by = by + y * sub_size;
                                pos_type l_bz = bz + z * sub_size;
                                size_type p = this->k_x_points.size() + (pos - this->k_t.size()); // TODO fix this
                                retrieve_point_information(point, l_bx, l_by, l_bz, p);
                                result.push_back(point);
                            }
                        } // END IF check level
                    } // END FOR z
                } // END FOR y
            } // END FOR x
        } // END WHILE queue
        return result.size();
    }

    size_type get_region_int_attr_helper(pos_type i_pos_x, pos_type i_pos_y, pos_type i_pos_z,
                                     pos_type e_pos_x, pos_type e_pos_y, pos_type e_pos_z,
                                     ushort i_intenstiy, ushort e_intensity,
                                     std::vector<point_LIDAR_result> &result) {

        if (i_pos_x > this->k_size || i_pos_y > this->k_size || i_pos_z > this->k_size) {
            return 0;
        }

        typedef std::tuple<pos_type, pos_type, pos_type, pos_type, pos_type, pos_type,
                size_type, pos_type, pos_type, pos_type, size_type, uint16_t> t_part_tuple;
        std::stack<t_part_tuple> q;

        q.push(t_part_tuple(i_pos_x, i_pos_y, i_pos_z, e_pos_x, e_pos_y, e_pos_z,
                            this->k_size, 0, 0, 0, 0, 0));


        uint8_t k = this->k_k1;
        pos_type x_i_b, x_e_b, y_i_b, y_e_b, z_i_b, z_e_b;  // First and end child
        pos_type xi, xe, yi, ye, zi, ze;                    // Local positions
        pos_type bx, by, bz;                                // Bases positions
        size_type sub_size;                                 // Size of each submatrix
        size_type pos, pos_children;
        uint16_t l;

        while (!q.empty()) {
            std::tie(xi, yi, zi, xe, ye, ze, sub_size, bx, by, bz, pos_children, l) = q.top();
            q.pop();

//            std::cout << "sub_size: " << sub_size << std::endl;

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

                        if (l < (this->k_height-1)) {
                            // Internal nodes
                            if (this->k_t[pos] == 1) {
                                // Continue with the search process
                                q.push(t_part_tuple(x == x_i_b ? xi % sub_size : 0,
                                                    y == y_i_b ? yi % sub_size : 0,
                                                    z == z_i_b ? zi % sub_size : 0,
                                                    x == x_e_b ? xe % sub_size : sub_size - 1,
                                                    y == y_e_b ? ye % sub_size : sub_size - 1,
                                                    z == z_e_b ? ze % sub_size : sub_size - 1,
                                                    sub_size, bx + x * sub_size, by + y * sub_size,  bz + z * sub_size,
                                                    this->k_t_rank(pos + 1) * this->k_k1_3, l+1));

                            } else {
                                size_type zeroes = pos - this->k_t_rank(pos);
                                if (this->k_h_p[zeroes] == 0) {
                                    continue; // Empty submatrix
                                } else {
                                    // Base positions
                                    pos_type l_bx = bx + x * sub_size;
                                    pos_type l_by = by + y * sub_size;
                                    pos_type l_bz = bz + z * sub_size;

                                    size_type ones = this->k_h_p_rank(zeroes);
                                    size_type p_init = ones == 0 ? 0 : this->k_s_leaf_points_select(ones)+1;
                                    size_type p_end = this->k_s_leaf_points_select(ones+1)+1;
//                    for (size_type p = k_r_leaf_points[ones]; p < k_r_leaf_points[ones+1]; p++) {

                                    for (size_type p = p_init; p < p_end; p++) {

                                        pos_type p_x = l_bx + this->k_x_points[p];
                                        pos_type p_y = l_by + this->k_y_points[p];
                                        pos_type p_z = l_bz + this->k_z_points[p];

                                        if (p_x >= i_pos_x) {
                                            if (p_x <= e_pos_x) {
                                                if (p_y >= i_pos_y && p_y <= e_pos_y &&
                                                    p_z >= i_pos_z && p_z <= e_pos_z) {
                                                    // The point is within of the region
                                                    int t_intensity = k_c_intensity[p];
                                                    if (t_intensity >= i_intenstiy && t_intensity <= e_intensity) {
                                                        point_LIDAR_result point;
                                                        retrieve_point_information_no_int(point, p_x, p_y, p_z, p); // TODO do not get intensity again
                                                        point.intensity = t_intensity;
                                                        result.push_back(point);
                                                    }
                                                }
                                            } else {
                                                // There are no more points within the region
                                                break;
                                            }
                                        } // END IF p_x
                                    } // END FOR p_init to p_end
                                } // END IF k_t[node_pos] == 0
                            }// ENF IF t[pos] == 1
                        } else {
                            // Leaves nodes
                            if (this->k_l[pos - this->k_t.size()] == 1) {
                                point_LIDAR_result point;
                                // Base positions
                                pos_type l_bx = bx + x * sub_size;
                                pos_type l_by = by + y * sub_size;
                                pos_type l_bz = bz + z * sub_size;
                                size_type p = this->k_x_points.size() + (pos - this->k_t.size()); // TODO fix this
                                int t_intensity = k_c_intensity[p];
                                if (t_intensity >= i_intenstiy && t_intensity <= e_intensity) {
                                    point_LIDAR_result point;
                                    retrieve_point_information_no_int(point, l_bx, l_by, l_bz, p); // TODO do not get intensity again
                                    point.intensity = t_intensity;
                                    result.push_back(point);
                                }
                                result.push_back(point);
                            }
                        } // END IF check level
                    } // END FOR z
                } // END FOR y
            } // END FOR x
        } // END WHILE queue
        return result.size();
    }

    //********************************************************************************************************//
    //******************************************* PUBLIC FUNCTIONS *******************************************//
    //*******************************************************************************************************//

    public:

    //*******************************************************//
    //******************* CONSTRUCTOR ***********************//
    //*******************************************************//
    k3_tree_LIDAR_points() = default;

    k3_tree_LIDAR_points(const k3_tree_LIDAR_points& tr)
    {
        *this = tr;
    }

    k3_tree_LIDAR_points(k3_tree_LIDAR_points&& tr)
    {
        *this = std::move(tr);
    }

    k3_tree_LIDAR_points(std::string filename) : k3_tree_LIDAR_points(filename, false)
    {
    }

    k3_tree_LIDAR_points(std::string filename, bool min_men)
    {
        // Open LAS/LAZ file
        LASreadOpener lasreadopener;
        lasreadopener.set_file_name(filename.data());
        LASreader* lasreader = lasreadopener.open();

        // Get LIDAR info
        init_att(lasreader->npoints);
        copy_info_LIDAR(lasreader);

        // Max size of the cube
        ulong size = std::ceil(std::max(std::max(std::ceil((k_max_x - k_d_x_offset) / k_x_scale_factor) - k_offset_x,
                                                 std::ceil((k_max_y - k_d_y_offset) / k_y_scale_factor) - k_offset_y),
                                        std::ceil((k_max_z - k_d_z_offset) / k_z_scale_factor) - k_offset_z));
        size++;



        // Initialize k3-tree values (ks, height, size, etc)
        this->init(size);

        // Read points and store them into a vector
        uint count = 0;
        LASpoint point;
        k_scan_angle_rank_delta = 90;

        if (min_men) {
            std::vector<point_LIDAR_men> points(lasreader->npoints);
            point_LIDAR_men point_l;
            while (lasreader->read_point()) {
                point = lasreader->point;

                // Copy point
                point_l.X = point.X - k_offset_x;
                point_l.Y = point.Y - k_offset_y;
                point_l.Z = point.Z - k_offset_z;
                point_l.pos = count;

                // Calculate k_scan_angle_rank_delta
                k_scan_angle_rank_delta = std::min(k_scan_angle_rank_delta, (int8_t)point.scan_angle_rank);
                points[count] = point_l;
                count++;
            }




            // Build structures
            std::cout << "Encoding LIDAR (Format " << (uint)lasreader->header.point_data_format << ") file with " << k_n_points << " points and size " << this->k_size << " (" << size << ")" << std::endl;
            build_men(lasreader, points);

            // close file
            lasreader->close();
            delete lasreader;

        } else {
            std::vector<point_LIDAR> points(lasreader->npoints);
            point_LIDAR point_l;
            while (lasreader->read_point()) {
                point = lasreader->point;

                // Copy point
                point_l.X = point.X - k_offset_x;
                point_l.Y = point.Y - k_offset_y;
                point_l.Z = point.Z - k_offset_z;
                point_l.intensity = point.intensity;
                point_l.return_number = point.return_number;
                point_l.number_of_returns = point.number_of_returns;
                point_l.scan_direction_flag = point.scan_direction_flag;
                point_l.edge_of_flight_line = point.edge_of_flight_line;
                point_l.classification = point.classification;
                point_l.scan_angle_rank = point.scan_angle_rank;
                point_l.user_data = point.user_data;
                point_l.point_source_ID = point.point_source_ID;

                // Calculate k_scan_angle_rank_delta
                k_scan_angle_rank_delta = std::min(k_scan_angle_rank_delta, point_l.scan_angle_rank);


                points[count] = point_l;
                count++;
            }

            // close file
            lasreader->close();
            delete lasreader;

            // Initialize k3-tree values (ks, height, size, etc)
            this->init(size);

            // Build structures
            std::cout << "Encoding LIDAR (Format " << (uint)lasreader->header.point_data_format << ") file with " << k_n_points << " points and size " << this->k_size << " (" << size << ")" << std::endl;
            build(points);
        }
    }

    //*******************************************************//
    //*************** BASIC OPERATIONS **********************//
    //*******************************************************//

    //! Move assignment operator
    k3_tree_LIDAR_points& operator=(k3_tree_LIDAR_points&& tr)
    {
        if (this != &tr) {

        }
        return *this;
    }

    //! Assignment operator
    k3_tree_LIDAR_points& operator=(k3_tree_LIDAR_points& tr)
    {
        if (this != &tr) {

        }
        return *this;
    }

    //! Swap operator
    void swap(k3_tree_LIDAR_points& tr)
    {
        if (this != &tr) {

        }
    }

    //! Equal operator
    bool operator==(const k3_tree_LIDAR_points& tr) const
    {
        return true;
    }

    //*******************************************************//
    //********************* GETTERS ************************//
    //*******************************************************//

    size_type get_size() {return this->k_size;}
    double get_min_size_x(){ return k_min_x;}
    double get_min_size_y(){ return k_min_y;}
    double get_min_size_z(){ return k_min_z;}
    double get_max_size_x(){ return k_max_x;}
    double get_max_size_y(){ return k_max_y;}
    double get_max_size_z(){ return k_max_z;}

//    size_type get_offset_x() { return this->k_offset_x;}
//    size_type get_offset_y() { return this->k_offset_y;}
//    size_type get_offset_z() { return this->k_offset_z;}

    //*******************************************************//
    //********************** QUERIES ************************//
    //*******************************************************//

    //*******************//
    //******* GET *******//
    //*******************//

    bool get_no_factor(pos_type x, pos_type y, pos_type z) {
        return get_helper(x - k_offset_x, y - k_offset_y, z - k_offset_z);
    }

    bool get(double x, double y, double z) {
        return get_no_factor(std::round((x - k_d_x_offset) / k_x_scale_factor),
                             std::round((y - k_d_y_offset) / k_y_scale_factor),
                             std::round((z - k_d_z_offset) / k_z_scale_factor));
    }

    //*******************//
    //***** GET ATTR ****//
    //*******************//
    bool get_attr_no_factor(pos_type pos_x, pos_type pos_y, pos_type pos_z, point_LIDAR_result &point) {
        return get_attr_helper(pos_x - k_offset_x, pos_y - k_offset_y, pos_z - k_offset_z, point);
    }

    bool get_attr(double x, double y, double z, point_LIDAR_result &point) {
        return get_attr_no_factor(std::round((x - k_d_x_offset) / k_x_scale_factor),
                                  std::round((y - k_d_y_offset) / k_y_scale_factor),
                                  std::round((z - k_d_z_offset) / k_z_scale_factor), point);
    }

    //*******************//
    //**** GET REGION ***//
    //*******************//
    size_type get_region_no_factor(pos_type i_pos_x, pos_type i_pos_y, pos_type i_pos_z,
                                   pos_type e_pos_x, pos_type e_pos_y, pos_type e_pos_z,
                                   std::vector<point_type> &result) {
        return get_region_helper(i_pos_x - k_offset_x, i_pos_y - k_offset_y, i_pos_z - k_offset_z,
                                 e_pos_x - k_offset_x, e_pos_y - k_offset_y, e_pos_z - k_offset_z,
                                 result);
    }

    size_type get_region(double i_pos_x, double i_pos_y, double i_pos_z,
                         double e_pos_x, double e_pos_y, double e_pos_z,
                         std::vector<point_type> &result) {
        return get_region_no_factor(std::round((i_pos_x - k_d_x_offset) / k_x_scale_factor),
                                    std::round((i_pos_y - k_d_y_offset) / k_y_scale_factor),
                                    std::round((i_pos_z - k_d_z_offset) / k_z_scale_factor),
                                    std::round((e_pos_x - k_d_x_offset) / k_x_scale_factor),
                                    std::round((e_pos_y - k_d_y_offset) / k_y_scale_factor),
                                    std::round((e_pos_z - k_d_z_offset) / k_z_scale_factor),
                                    result); //TODO change result to real coordinates
    }

    //*******************//
    //* GET REGION ATTR *//
    //*******************//
    size_type get_region_attr_no_factor(long long i_pos_x, long long i_pos_y, long long i_pos_z,
                                        long long e_pos_x, long long e_pos_y, long long e_pos_z,
                                   std::vector<point_LIDAR_result> &result) {
        if (e_pos_x < k_offset_x || e_pos_y < k_offset_y || e_pos_z < k_offset_z) {
            return 0;
        }
        return get_region_attr_helper(i_pos_x < k_offset_x ? 0 : i_pos_x - k_offset_x,
                                      i_pos_y < k_offset_y ? 0 : i_pos_y - k_offset_y,
                                      i_pos_z < k_offset_z ? 0 : i_pos_z - k_offset_z,
                                      e_pos_x - k_offset_x - 1,
                                      e_pos_y - k_offset_y - 1,
                                      e_pos_z - k_offset_z - 1,
                                 result);
    }

    size_type get_region_attr(double i_pos_x, double i_pos_y, double i_pos_z,
                         double e_pos_x, double e_pos_y, double e_pos_z,
                         std::vector<point_LIDAR_result> &result) {
        e_pos_x = e_pos_x > k_max_x ? k_max_x : e_pos_x;
        e_pos_y = e_pos_y > k_max_y ? k_max_y : e_pos_y;
        e_pos_z = e_pos_z > k_max_z ? k_max_z : e_pos_z;

        return get_region_attr_no_factor((std::round((i_pos_x - k_d_x_offset) / k_x_scale_factor)),
                                         std::round((i_pos_y - k_d_y_offset) / k_y_scale_factor),
                                         std::round((i_pos_z - k_d_z_offset) / k_z_scale_factor),
                                         std::round((e_pos_x - k_d_x_offset) / k_x_scale_factor),
                                         std::round((e_pos_y - k_d_y_offset) / k_y_scale_factor),
                                         std::round((e_pos_z - k_d_z_offset) / k_z_scale_factor),
                                    result);
    }

    //*******************//
    //* GET REGION + Intensity ATTR *//
    //*******************//
    size_type get_region_int_attr_no_factor(pos_type i_pos_x, pos_type i_pos_y, pos_type i_pos_z,
                                        pos_type e_pos_x, pos_type e_pos_y, pos_type e_pos_z,
                                        ushort i_intensity, ushort e_intensity,
                                        std::vector<point_LIDAR_result> &result) {
        if (e_pos_x < k_offset_x || e_pos_y < k_offset_y || e_pos_z < k_offset_z) {
            return 0;
        }
        return get_region_int_attr_helper(i_pos_x < k_offset_x ? 0 : i_pos_x - k_offset_x,
                                          i_pos_y < k_offset_y ? 0 : i_pos_y - k_offset_y,
                                          i_pos_z < k_offset_z ? 0 : i_pos_z - k_offset_z,
                                          e_pos_x - k_offset_x - 1,
                                          e_pos_y - k_offset_y - 1,
                                          e_pos_z - k_offset_z - 1,
                                      i_intensity, e_intensity,
                                      result);
    }

    size_type get_region_int_attr(double i_pos_x, double i_pos_y, double i_pos_z,
                                  double e_pos_x, double e_pos_y, double e_pos_z,
                                  ushort i_intensity, ushort e_intensity,
                              std::vector<point_LIDAR_result> &result) {
        e_pos_x = e_pos_x > k_max_x ? k_max_x : e_pos_x;
        e_pos_y = e_pos_y > k_max_y ? k_max_y : e_pos_y;
        e_pos_z = e_pos_z > k_max_z ? k_max_z : e_pos_z;

        return get_region_int_attr_no_factor((std::round((i_pos_x - k_d_x_offset) / k_x_scale_factor)),
                                         std::round((i_pos_y - k_d_y_offset) / k_y_scale_factor),
                                         std::round((i_pos_z - k_d_z_offset) / k_z_scale_factor),
                                         std::round((e_pos_x - k_d_x_offset) / k_x_scale_factor),
                                         std::round((e_pos_y - k_d_y_offset) / k_y_scale_factor),
                                         std::round((e_pos_z - k_d_z_offset) / k_z_scale_factor),
                                         i_intensity, e_intensity,
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

        written_bytes += write_member(K3_TREE_TYPE_LIDAR_POINTS, out, child, "k3_tree_type");
        k3_tree_points<t_k1, t_k2, t_min_points, t_bv, t_rank, t_select, t_point_vec, double>::serialize(out, v, "k3_tree");
        written_bytes += write_member(k_n_points, out, child, "n_points");
        written_bytes += write_member(k_min_x, out, child, "min_x");
        written_bytes += write_member(k_min_y, out, child, "min_y");
        written_bytes += write_member(k_min_z, out, child, "min_z");
        written_bytes += write_member(k_max_x, out, child, "max_x");
        written_bytes += write_member(k_max_y, out, child, "max_y");
        written_bytes += write_member(k_max_z, out, child, "max_z");
        written_bytes += write_member(k_d_x_offset, out, child, "d_x_offset");
        written_bytes += write_member(k_d_y_offset, out, child, "d_y_offset");
        written_bytes += write_member(k_d_z_offset, out, child, "d_z_offset");
        written_bytes += write_member(k_x_scale_factor, out, child, "x_scale_factor");
        written_bytes += write_member(k_y_scale_factor, out, child, "y_scale_factor");
        written_bytes += write_member(k_z_scale_factor, out, child, "z_scale_factor");
        written_bytes += write_member(k_offset_x, out, child, "offset_x");
        written_bytes += write_member(k_offset_y, out, child, "offset_y");
        written_bytes += write_member(k_offset_z, out, child, "offset_z");
        written_bytes += write_member(k_scan_angle_rank_delta, out, child, "scan_angle_rank_delta");

//        written_bytes += k_intensity.serialize(out, child, "intensity");
//        written_bytes += k_return_number.serialize(out, child, "return_number");
//        written_bytes += k_n_return_pulse.serialize(out, child, "n_return_pulse");
//        written_bytes += k_scan_direction_flag.serialize(out, child, "scan_direction_flag");
//        written_bytes += k_edge.serialize(out, child, "edge");
//        written_bytes += k_classification.serialize(out, child, "classification");
//        written_bytes += k_scan_angle.serialize(out, child, "scan_angle");
//        written_bytes += k_user_data.serialize(out, child, "user_data");
//        written_bytes += k_point_source.serialize(out, child, "point_source");

        written_bytes += k_c_intensity.serialize(out, child, "intensity");
        written_bytes += k_c_return_number.serialize(out, child, "return_number");
        written_bytes += k_c_n_return_pulse.serialize(out, child, "n_return_pulse");
        written_bytes += k_c_scan_direction_flag.serialize(out, child, "scan_direction_flag");
        written_bytes += k_c_edge.serialize(out, child, "edge");
        written_bytes += k_c_classification.serialize(out, child, "classification");
        written_bytes += k_c_scan_angle.serialize(out, child, "scan_angle");
        written_bytes += k_c_user_data.serialize(out, child, "user_data");
        written_bytes += k_c_point_source.serialize(out, child, "point_source");

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
        k3_tree_points<t_k1, t_k2, t_min_points, t_bv, t_rank, t_select, t_point_vec, double>::load(in);
        read_member(k_n_points, in);
        read_member(k_min_x, in);
        read_member(k_min_y, in);
        read_member(k_min_z, in);
        read_member(k_max_x, in);
        read_member(k_max_y, in);
        read_member(k_max_z, in);
        read_member(k_d_x_offset, in);
        read_member(k_d_y_offset, in);
        read_member(k_d_z_offset, in);
        read_member(k_x_scale_factor, in);
        read_member(k_y_scale_factor, in);
        read_member(k_z_scale_factor, in);
        read_member(k_offset_x, in);
        read_member(k_offset_y, in);
        read_member(k_offset_z, in);
        read_member(k_scan_angle_rank_delta, in);

//        k_intensity.load(in);
//        k_return_number.load(in);
//        k_n_return_pulse.load(in);
//        k_scan_direction_flag.load(in);
//        k_edge.load(in);
//        k_classification.load(in);
//        k_scan_angle.load(in);
//        k_user_data.load(in);
//        k_point_source.load(in);

        k_c_intensity.load(in);
        k_c_return_number.load(in);
        k_c_n_return_pulse.load(in);
        k_c_scan_direction_flag.load(in);
        k_c_edge.load(in);
        k_c_classification.load(in);
        k_c_scan_angle.load(in);
        k_c_user_data.load(in);
        k_c_point_source.load(in);
    }

    void print() {
        k3_tree_points<t_k1, t_k2, t_min_points, t_bv, t_rank, t_select, t_point_vec, double>::print();
        return;
    }

    //*******************************************************//
    //*********************** TEST **************************//
    //*******************************************************//
    bool check_values(std::string data_file_name){
        // Open LIDAR file
        LASreadOpener lasreadopener_test;
        lasreadopener_test.set_file_name(data_file_name.data());
        LASreader* lasreader_test = lasreadopener_test.open();

        // Run test
        bool res = check_values(lasreader_test);

        // Close and delete
        lasreader_test->close();
        delete lasreader_test;

        return res;
    }

    bool check_values(LASreader* lasreader) {

        // Read file
        LASpoint point;
        point_LIDAR_result point_l;
        while (lasreader->read_point()) {
            point = lasreader->point;

            if (!get_attr_no_factor(point.X, point.Y, point.Z, point_l)) {
                #ifndef NDEBUG
                    std::cout << "Failed point (" << point.X << ", " << point.Y << ", " << point.Z << ") " << std::endl;
                #endif
                return false;
            } else {
                // Check attributes
                if (point_l.intensity != point.intensity ||
                    point_l.return_number != point.return_number ||
                    point_l.number_of_returns != point.number_of_returns ||
                    point_l.scan_direction_flag != point.scan_direction_flag ||
                    point_l.edge_of_flight_line != point.edge_of_flight_line ||
                    point_l.classification != point.classification ||
                    point_l.scan_angle_rank != point.scan_angle_rank ||
                    point_l.user_data != point.user_data ||
                    point_l.point_source_ID != point.point_source_ID) {
#ifndef NDEBUG
                    std::cout << "Failed point (" << point.X << ", " << point.Y << ", " << point.Z << "): Values are not equal" << std::endl;

                    std::cout << "k3-tree point" << std::endl;
                    std::cout << "-----------------------------" << std::endl;
                    print_point_LIDAR(point_l);

                    std::cout << "LIDAR point" << std::endl;
                    std::cout << "-----------------------------" << std::endl;
                    std::cout << "Point (" << point.X << ", " << point.Y << ", " << point.Z << ")" << std::endl;
                    std::cout << "Intensity number: " << (uint)point.intensity << std::endl;
                    std::cout << "Return number: " << (uint)point.return_number << std::endl;
                    std::cout << "Number of returns: " << (uint)point.number_of_returns << std::endl;
                    std::cout << "Scan direction flag: " << (uint)point.scan_direction_flag << std::endl;
                    std::cout << "Edge of flight line: " << (uint)point.edge_of_flight_line << std::endl;
                    std::cout << "Classification: " << (uint)point.classification << std::endl;
                    std::cout << "Scan angle rank: " << (uint)point.scan_angle_rank << std::endl;
                    std::cout << "User data: " << (uint)point.user_data << std::endl;
                    std::cout << "Point source ID: " << (uint)point.point_source_ID << std::endl;
#endif
                    return false;
                }
            }

        }

        return true;
    }
}; // ENC CLASS k3-tree

} // END NAMESPACE sdsl

#endif // INCLUDED_SDSL_K3_TREE_LIDAR_POINTS
