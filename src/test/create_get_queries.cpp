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

#include <random>
#include <k3_tree.hpp>
#include <k3_tree_points.hpp>
#include <k3_tree_level.hpp>
#include <LIDAR/k3_tree_LIDAR_points.hpp>

void print_help(char * argv0) {
    printf("Usage: %s <k3_tree_file> <query_file_output> <n_queries>\n", argv0);
}

template <typename k3_tree_type, typename t_return_type, uint8_t t_precision=0>
void create_get_queries(std::string k3_tree_filename, std::string query_filename, size_t n_queries) {
    //************************//
    // Load structure         //
    //************************//
    std::ifstream input_file(k3_tree_filename);
    assert(input_file.is_open() && input_file.good());
    k3_tree_type k3_tree;
    k3_tree.load(input_file);
    input_file.close();

    //************************//
    // Create query file      //
    //************************//
    std::ofstream query_file(query_filename);
    assert(query_file.is_open() && query_file.good());

    //************************//
    // Adds queries           //
    //************************//
    t_return_type x, y, z;
    t_return_type min_x = k3_tree.get_min_size_x();
    t_return_type min_y = k3_tree.get_min_size_y();
    t_return_type min_z = k3_tree.get_min_size_z();
    t_return_type max_x = k3_tree.get_max_size_x();
    t_return_type max_y = k3_tree.get_max_size_y();
    t_return_type max_z = k3_tree.get_max_size_z();

    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<> dis_x(0, max_x - min_x);
    std::uniform_real_distribution<> dis_y(0, max_y - min_y);
    std::uniform_real_distribution<> dis_z(0, max_z - min_z);

    double n1, n2;
    for (size_t q = 0; q < n_queries; q++) {

        // X
        n1 = dis_x(gen) + min_x;
        n2 = dis_x(gen) + min_x;
        x = std::min(n1, n2);

        // Y
        n1 = dis_y(gen) + min_y;
        n2 = dis_y(gen) + min_y;
        y = std::min(n1, n2);

        // Z
        n1 = dis_z(gen) + min_z;
        n2 = dis_z(gen) + min_z;
        z = std::min(n1, n2);

        query_file << std::fixed << std::setprecision(t_precision) << x << " " << y << " " << z;
        if (q != n_queries-1) query_file << std::endl;
    }
}

int main(int argc, char **argv) {
    if (argc != 4) {
        print_help(argv[0]);
        exit(-1);
    }

    // Get input params
    std::string k3_tree_filename = argv[1];
    std::string query_filename = argv[2];
    size_t n_queries = atoi(argv[3]);

    // Read k3_type
    std::ifstream input_file(k3_tree_filename);
    assert(input_file.is_open() && input_file.good());
    ushort k3_tree_type;
    sdsl::read_member(k3_tree_type, input_file);
    input_file.close();

    std::cout << "Creating " << n_queries << " 'get' queries for the k3-tree: " << k3_tree_filename << " (type: " << k3_tree_type << ")" << std::endl;


    switch (k3_tree_type) {
        case sdsl::K3_TREE_TYPE_BASIC:
            create_get_queries<sdsl::k3_tree<>, sdsl::k3_tree_base<>::pos_type, 0>(k3_tree_filename, query_filename, n_queries);
            break;
        case sdsl::K3_TREE_TYPE_POINTS:
            create_get_queries<sdsl::k3_tree_points<>, sdsl::k3_tree_base<>::pos_type, 0>(k3_tree_filename, query_filename, n_queries);
            break;
        case sdsl::K3_TREE_TYPE_LEVEL:
            create_get_queries<sdsl::k3_tree_level<>, sdsl::k3_tree_base<>::pos_type, 0>(k3_tree_filename, query_filename, n_queries);
            break;
        case sdsl::K3_TREE_TYPE_LIDAR_POINTS:
            create_get_queries<sdsl::k3_tree_LIDAR_points<>, double, 2>(k3_tree_filename, query_filename, n_queries);
            break;
        default:
            print_help(argv[0]);
            std::cout << "Invalid type " << k3_tree_type << ": " << std::endl;
            std::cout << "\t Type " << sdsl::K3_TREE_TYPE_BASIC << ": Basic k3-tree." << std::endl;
            std::cout << "\t Type " << sdsl::K3_TREE_TYPE_POINTS << ": k3-tree with limit of points." << std::endl;
            std::cout << "\t Type " << sdsl::K3_TREE_TYPE_LEVEL << ": k3-tree with limit of levels." << std::endl;
            std::cout << "\t Type " << sdsl::K3_TREE_TYPE_LIDAR_POINTS << ": k3-tree LIDAR with limit of points." << std::endl;
            exit(-1);
    }

    std::cout << "Created " << n_queries << " 'get' queries and stored in " << query_filename << " file " << std::endl;
}
