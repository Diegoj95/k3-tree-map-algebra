/*  
 * Created by Fernando Silva on 5/06/18.
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

#include <LASlib/inc/lasreader.hpp>
#include <LIDAR/k3_tree_LIDAR_points.hpp>

using timer = std::chrono::high_resolution_clock;

void print_help(char * argv0) {
    printf("Usage: %s <input_data> <output_data> <set_check> <k3_tree_type>\\n", argv0);
}

template<typename k3_tree_type>
void run_encode(std::string input_filename, std::string output_filename, bool set_check) {
    //************************//
    // Create structure       //
    //************************//
    k3_tree_type k3_tree(input_filename);

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
        std::cout << std::endl << "Checking k3-tree structure......." << std::endl;

        // Load structure
        std::ifstream input_file(output_filename);
        assert(input_file.is_open() && input_file.good());
        sdsl::k3_tree_LIDAR_points<> k3_tree_test;
        k3_tree_test.load(input_file);
        input_file.close();

        // Open LIDAR file
        LASreadOpener lasreadopener_test;
        lasreadopener_test.set_file_name(input_filename.data());
        LASreader* lasreader_test = lasreadopener_test.open();

        // Check values
        if (k3_tree_test.check_values(lasreader_test)) {
            std::cout << "Test Values: OK!!" << std::endl;
        } else {
            std::cout << "Test Values: FAILED!!" << std::endl;
        }
        // Close and delete
        lasreader_test->close();
        delete lasreader_test;
    }
}


int main(int argc, char **argv) {
    if (argc != 5) {
        print_help(argv[0]);
        exit(-1);
    }

    std::string input_filename = argv[1];
    std::string output_filename = argv[2];
    bool set_check = atoi(argv[3]);
    ushort k3_tree_type = atoi(argv[4]);


    switch (k3_tree_type) {

        case sdsl::K3_TREE_TYPE_LIDAR_POINTS:
            run_encode<sdsl::k3_tree_LIDAR_points<>>(input_filename, output_filename, set_check);
            break;
        default:
            print_help(argv[0]);
            std::cout << "Invalid type " << k3_tree_type << ": " << std::endl;
            std::cout << "\t Type " << sdsl::K3_TREE_TYPE_LIDAR_POINTS << ": k3-tree with limit of points." << std::endl;
            exit(-1);
    }

//    k3_tree.print();
}