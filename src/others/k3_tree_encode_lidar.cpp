/*  
 * Created by Fernando Silva on 5/04/18.
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

#include <others/k3_tree_LIDAR.hpp>

void print_help(char * argv0) {
    printf("Usage: %s <input_data> <n_digits> <n_params> <output_data> <set_check>\n", argv0);
}


int main(int argc, char **argv) {
    if (argc != 6) {
        print_help(argv[0]);
        exit(-1);
    }

    // Get input parameters
    std::string input_filename = argv[1];
    size_t n_digits = atoi(argv[2]);
    size_t n_params = atoi(argv[3]);
    std::string output_filename = argv[4];
    bool set_check = atoi(argv[5]);


    //************************//
    // Create structure       //
    //************************//
    #ifndef NDEBUG
        std::cout << std::endl << "Creating k3-tree structure from LIDAR file: " << input_filename  << std::endl;
    #endif
    sdsl::k3_tree_lidar<> k3_tree(input_filename, n_digits, n_params);

    //************************//
    // Save structure         //
    //************************//
    #ifndef NDEBUG
        std::cout << std::endl << "Storing k3-tree structure in file: " << output_filename  << std::endl;
    #endif
    sdsl::store_to_file(k3_tree, output_filename);

    #ifndef NDEBUG
        std::string file_name = std::string(output_filename) + ".html";
        sdsl::write_structure<sdsl::format_type::HTML_FORMAT>(k3_tree, file_name);
    #endif

    //************************//
    // TEST structure         //
    //************************//
    if (set_check) {
        #ifndef NDEBUG
            std::cout << std::endl << "Checking k3-tree structure......." << std::endl;
        #endif

        // Load structure
        std::ifstream input_file(output_filename);
        assert(input_file.is_open() && input_file.good());
        sdsl::k3_tree_lidar<> k3_tree_test;
        k3_tree_test.load(input_file);
        input_file.close();

        // Load values
        std::ifstream values_file(input_filename);
        assert(values_file.is_open() && values_file.good());

        if (k3_tree_test.check_values(values_file)) {
            std::cout << "Test Values: OK!!" << std::endl;
        } else {
            std::cout << "Test Values: FAILED!!" << std::endl;
        }
        values_file.close();
    }
}