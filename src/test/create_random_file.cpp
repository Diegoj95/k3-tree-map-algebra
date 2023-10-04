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

#include <iostream>
#include <fstream>
#include <assert.h>
#include <sdsl/int_vector.hpp>
#include <util/file.hpp>


void print_help(char * argv0) {
    printf("Usage: %s <size> <number_of_points> <output_data>\n", argv0);
}

int main(int argc, char **argv) {
    if (argc != 4) {
        print_help(argv[0]);
        exit(-1);
    }

    typedef sdsl::int_vector<>::size_type size_type;
    size_type size = atoi(argv[1]);
    size_type number_of_points = atoi(argv[2]);
    std::string output_filename = argv[3];

    std::ofstream output_data(output_filename);
    assert(output_data.is_open() && output_data.good());

    sdsl::add_random_points(size, number_of_points, output_data);
    output_data.close();
}