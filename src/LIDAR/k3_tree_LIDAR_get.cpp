/*  
 * Created by Fernando Silva on 18/06/18.
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

using timer = std::chrono::high_resolution_clock;

void print_help(char * argv0) {
    printf("Usage: %s <k3_tree_file> <query_file>\n", argv0);
}

template <typename k3_tree_type>
void run_get(std::string k3_tree_filename, std::string query_filename){
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
    size_t n_queries = 0, n_points = 0;
    double x, y, z;
    sdsl::point_LIDAR_result point;

    auto start = timer::now();
    while (!query_file.eof() && query_file.good()) {
        // Read coordinates
        query_file >> x;
        query_file >> y;
        query_file >> z;

        n_points += k3_tree.get_attr(x, y, z, point) ? 1 : 0;
        n_queries++;
    } // END WHILE run queries
    auto stop = timer::now();

    std::cout << "Result: " << n_points << " points in " << n_queries << " queries" << std::endl;
    std::cout << "Test time = " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " milliseconds" << std::endl;
}



int main(int argc, char **argv) {
    if (argc != 3) {
        print_help(argv[0]);
        exit(-1);
    }

    // Get input params
    std::string k3_tree_filename = argv[1];
    std::string query_filename = argv[2];


    // Read k3_type
    std::ifstream input_file(k3_tree_filename);
    assert(input_file.is_open() && input_file.good());
    ushort k3_tree_type;
    sdsl::read_member(k3_tree_type, input_file);
    input_file.close();

    switch (k3_tree_type) {
        case sdsl::K3_TREE_TYPE_LIDAR_POINTS:
            run_get<sdsl::k3_tree_LIDAR_points<>>(k3_tree_filename, query_filename);
            break;
        default:
            print_help(argv[0]);
            std::cout << "Invalid type " << k3_tree_type << ": " << std::endl;
            std::cout << "\t Type " << sdsl::K3_TREE_TYPE_LIDAR_POINTS << ": k3-tree with limit of points." << std::endl;
            exit(-1);
    }
}
