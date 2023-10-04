/*  
 * Created by Fernando Silva on 10/05/18.
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

// k3-tree
#include <k3_tree_base.hpp>
#include <k3_tree.hpp>
#include <k3_tree_points.hpp>
#include <k3_tree_level.hpp>


using timer = std::chrono::high_resolution_clock;

void print_help(char * argv0) {
    printf("Usage: %s <input_data> <size> <output_data> <set_check> <k3_tree_type>\n", argv0);
}


template<typename k3_tree_type>
void run_encode(std::string input_filename, size_t size, std::string output_filename, bool set_check){
    //************************//
    // Create structure       //
    //************************//
    auto start = timer::now();
    k3_tree_type k3_tree(input_filename, size);
    auto stop = timer::now();
    std::cout << "Encode time = " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " milliseconds" << std::endl;

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
        k3_tree_type k3_tree_test;
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

int main(int argc, char **argv) {
    if (argc != 6) {
        print_help(argv[0]);
        exit(-1);
    }

    /*********************/
    /* Reads params      */
    /*********************/
    std::string input_filename = argv[1];
    size_t size = atoi(argv[2]);
    std::string output_filename = argv[3];
    bool set_check = atoi(argv[4]);
    ushort k3_tree_type = atoi(argv[5]);

    /*********************/
    /* Encodes data      */
    /*********************/
    switch (k3_tree_type) {
        case sdsl::K3_TREE_TYPE_BASIC:
            run_encode<sdsl::k3_tree<>>(input_filename, size, output_filename, set_check);
            break;
        case sdsl::K3_TREE_TYPE_POINTS:
            run_encode<sdsl::k3_tree_points<>>(input_filename, size, output_filename, set_check);
            break;
        case sdsl::K3_TREE_TYPE_LEVEL:
            run_encode<sdsl::k3_tree_level<>>(input_filename, size, output_filename, set_check);
            break;
        default:
            print_help(argv[0]);
            std::cout << "Invalid type " << k3_tree_type << ": " << std::endl;
            std::cout << "\t Type " << sdsl::K3_TREE_TYPE_BASIC << ": Basic k3-tree." << std::endl;
            std::cout << "\t Type " << sdsl::K3_TREE_TYPE_POINTS << ": k3-tree with limit of points." << std::endl;
            std::cout << "\t Type " << sdsl::K3_TREE_TYPE_LEVEL << ": k3-tree with limit of levels." << std::endl;
            exit(-1);
    }


//    k3_tree.print();
}