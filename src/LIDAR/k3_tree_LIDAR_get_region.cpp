/*  
 * Created by Fernando Silva on 18/04/18.
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

#include <LIDAR/k3_tree_LIDAR_points.hpp>
#include <k3_tree.hpp>

using timer = std::chrono::high_resolution_clock;


bool comparePointLIDAR(const sdsl::point_LIDAR_result &p1, const sdsl::point_LIDAR_result &p2)
{
    if (p1.X == p2.X) {
        if (p1.Y == p2.Y) {
            if (p1.Z == p2.Z) {
                return false;
            } else {
                return p1.Z < p2.Z;
            }
        } else {
            return p1.Y < p2.Y;
        }
    } else {
        return p1.X < p2.X;
    }
}


template <typename k3_tree_type>
void run_get_region(std::string k3_tree_filename, std::string query_filename, bool check) {
    //************************//
    // Load structure         //
    //************************//
    std::ifstream input_file(k3_tree_filename);
    assert(input_file.is_open() && input_file.good());
    k3_tree_type k3_tree;
    k3_tree.load(input_file);
    input_file.close();


    //************************//
    // Open query file        //
    //************************//
    std::ifstream query_file(query_filename);
    assert(query_file.is_open() && query_file.good());

    //************************//
    // Run queries            //
    //************************//
    size_t n_queries = 0, n_points = 0, n;
    double i_x, i_y, i_z, e_x, e_y, e_z;
    std::vector<sdsl::point_LIDAR_result> result;

    auto start = timer::now();
    while (!query_file.eof() && query_file.good()) {
        result.clear();

        // Read coordinates
        query_file >> i_x;
        query_file >> i_y;
        query_file >> i_z;
        query_file >> e_x;
        query_file >> e_y;
        query_file >> e_z;

//        std::cout << "Query " << n_queries << ": (" << i_x << ", " << i_y << ", " << i_z << ") -- ("
//                                << e_x << ", " << e_y << ", " << e_z << ")";

        n = k3_tree.get_region_attr(i_x, i_y, i_z, e_x, e_y, e_z, result);
        n_points += n;
//        std::cout << " = " << n << std::endl;

        if (check) {
            for(size_t p = 0; p < result.size(); p++) {
                if (result[p].d_x < i_x || result[p].d_x > e_x ||
                    result[p].d_y < i_y || result[p].d_y > e_y ||
                    result[p].d_z < i_z || result[p].d_z > e_z) {
                    std::cout << "Error at query " << n_queries << " point (";
                    std::cout << result[p].d_x << ", " << result[p].d_y << ", " << result[p].d_z;
                    std::cout << ") [" << result[p].X << ", " << result[p].Y << ", " << result[p].Z;
                    std::cout << "] is out of bounds" << std::endl;
                    exit(-1);
                }

                if (!k3_tree.get( result[p].d_x, result[p].d_y, result[p].d_z)) {
                    std::cout << "Error at query " << n_queries << " point (";
                    std::cout << result[p].d_x << ", " << result[p].d_y << ", " << result[p].d_z;
                    std::cout << ") [" << result[p].X << ", " << result[p].Y << ", " << result[p].Z;
                    std::cout << "] not found" << std::endl;
                    exit(-1);
                }
            }
        }
        n_queries++;

        // Print points
//        std::sort(result.begin(), result.end(), comparePointLIDAR);
//        std::ofstream points("./puntos1.txt");
//        for (auto i = 0; i < result.size(); i++) {
//            points << "Point (" << result[i].X << ", " << result[i].Y << ", " << result[i].Z << ")" << std::endl;
//            points << "Point (" << result[i].d_x << ", " << result[i].d_y << ", " << result[i].d_z << ")" << std::endl;
//        }


    } // END WHILE run queries
    auto stop = timer::now();
    result.clear();

    std::cout << "Result: " << n_points << " points in " << n_queries << " queries" << std::endl;
    std::cout << "Test time = " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " milliseconds" << std::endl;
    std::cout << "Test average time (query) = " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() / n_queries << " milliseconds" << std::endl;
    std::cout << "Test average time (points) = " << (n_points == 0 ? 0 : std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start).count() / n_points) << " nanoseconds" << std::endl;
}

void print_help(char * argv0) {
    printf("Usage: %s <k3_tree_file> <query_file> <check>\n", argv0);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        print_help(argv[0]);
        exit(-1);
    }

    // Get input params
    std::string k3_tree_filename = argv[1];
    std::string query_filename = argv[2];
    bool check = atoi(argv[3]);

    // Read k3_type
    std::ifstream input_file(k3_tree_filename);
    assert(input_file.is_open() && input_file.good());
    ushort k3_tree_type;
    sdsl::read_member(k3_tree_type, input_file);
    input_file.close();

    switch (k3_tree_type) {
        case sdsl::K3_TREE_TYPE_LIDAR_POINTS:
            run_get_region<sdsl::k3_tree_LIDAR_points<>>(k3_tree_filename, query_filename, check);
            break;
        default:
            print_help(argv[0]);
            std::cout << "Invalid type " << k3_tree_type << ": " << std::endl;
            std::cout << "\t Type " << sdsl::K3_TREE_TYPE_LIDAR_POINTS << ": k3-tree with limit of points." << std::endl;
            exit(-1);
    }
}