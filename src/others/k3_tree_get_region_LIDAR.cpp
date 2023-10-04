/*  
 * Created by Fernando Silva on 16/04/18.
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

#include <others/k3_tree_no_opt.hpp>
#include <others/k3_tree_LIDAR.hpp>

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

    //************************//
    // Load structure         //
    //************************//
    std::ifstream input_file(k3_tree_filename);
    assert(input_file.is_open() && input_file.good());
    sdsl::k3_tree_lidar<> k3_tree;
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
    double i_x, i_y, i_z, e_x, e_y, e_z;
    std::vector<sdsl::k3_tree_lidar<>::d_tuple_result> result;

    while (!query_file.eof() && query_file.good()) {
        result.clear();

        // Read coordinates
        query_file >> i_x;
        query_file >> i_y;
        query_file >> i_z;
        query_file >> e_x;
        query_file >> e_y;
        query_file >> e_z;

        n_points += k3_tree.get_region(i_x, i_y, i_z, e_x, e_y, e_z, result);
        if (check) {
            for(size_t p = 0; p < result.size(); p++) {
                if (!k3_tree.get(
                        std::get<0>(result[p]),
                        std::get<1>(result[p]),
                        std::get<2>(result[p]))) {
                    std::cout << "Error at query " << n_queries << " point (";
                    std::cout << std::get<0>(result[p]) << ", " << std::get<1>(result[p]) << ", " << std::get<2>(result[p]);
                    std::cout << ") not found" << std::endl;
                }
            }
        }
        n_queries++;
    } // END WHILE run queries

    std::cout << "Result: " << n_points << " points in " << n_queries << " queries" << std::endl;
}
