/*  
 * Created by Fernando Silva on 04/06/18.
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

#include <k3_tree.hpp>
#include <k3_tree_points.hpp>
#include <k3_tree_level.hpp>

#define SIZE 100
#define PER_NUMBER_OF_POINTS 0.2
#define N_QUERIES 100


typedef sdsl::k3_tree_base<>::size_type size_type;
typedef sdsl::k3_tree_base<>::size_type pos_type;
typedef sdsl::k3_tree_base<>::point_type point_type;

template <typename k3_tree_type>
void test_get_region(std::vector<point_type> points) {

    //************************//
    // Create structure       //
    //************************//
#ifndef NDEBUG
    std::cout << "Encoding k3-tree with  " << points.size() << " points "<< std::endl;
#endif
    k3_tree_type k3_tree(points, SIZE);

    //************************//
    // TEST structure         //
    //************************//
    std::cout << "Checking k3-tree structure......." << std::endl;
    if (k3_tree.check_values(points)) {
        std::cout << "Test Values: OK!!" << std::endl;
    } else {
        std::cout << "Test Values: FAILED!!" << std::endl;
        exit(-1);
    }

    //************************//
    // RUN QUERIES            //
    //************************//

    srand(time(NULL));
    pos_type i_pos_x, i_pos_y, i_pos_z;
    pos_type e_pos_x, e_pos_y, e_pos_z;

    std::vector<sdsl::k3_tree_base<>::point_type> result;

    for (size_type q = 0; q < N_QUERIES; q++) {
        i_pos_x = rand() % (SIZE-1);
        i_pos_y = rand() % (SIZE-1);
        i_pos_z = rand() % (SIZE-1);
        e_pos_x = (rand() % (SIZE-1-i_pos_x)) + i_pos_x;
        e_pos_y = (rand() % (SIZE-1-i_pos_y)) + i_pos_y;
        e_pos_z = (rand() % (SIZE-1-i_pos_z)) + i_pos_z;

#ifndef NDEBUG
        //std::cout << "Query " << q << "| REGION (" << i_pos_x << ", " << i_pos_y << ", " << i_pos_z << ") -> ";
        //std::cout << "(" << e_pos_x << ", " << e_pos_y << ", " << e_pos_z << ")";
#endif

        // Run function
        k3_tree.get_region(i_pos_x, i_pos_y, i_pos_z, e_pos_x, e_pos_y, e_pos_z, result);

#ifndef NDEBUG
        //std::cout << " = " << result.size() << " points" << std::endl;
#endif
        // Check every point in result set
        for (size_type p = 0; p < result.size(); p++) {
            if (!k3_tree.get(std::get<0>(result[p]), std::get<1>(result[p]), std::get<2>(result[p]))){
                std::cout << "Error at point (" << std::get<0>(result[p]) << ", " << std::get<1>(result[p]) << ", " << std::get<2>(result[p]) << ")" << std::endl;
                exit(-1);
            }
        } // END FOR check points

        // Get all points, one by one
        size_type n_points_get = 0;
        for (size_type x = i_pos_x; x <= e_pos_x; x++) {
            for (size_type y = i_pos_y; y <= e_pos_y; y++) {
                for (size_type z = i_pos_z; z <= e_pos_z; z++) {
                    if (k3_tree.get(x, y, z)){
                        n_points_get++;
                    }
                } // END FOR z
            } // END FOR y
        } // END FOR x

        // Compare results
        if (result.size() != n_points_get) {
            std::cout << "Error - Get " << result.size() << " and expected " << n_points_get << std::endl;
            exit(-1);
        }

        result.clear(); // clean vector
    } // END FOR query
}

int main() {

    //************************//
    // Create data            //
    //************************//
    size_type number_of_points = pow(SIZE, 3) * PER_NUMBER_OF_POINTS;
    size_type pos_x, pos_y, pos_z;


#ifndef NDEBUG
    std::cout << "Creating data of size " << SIZE << "x" << SIZE << "x" << SIZE;
    std::cout << " and " << PER_NUMBER_OF_POINTS*100 << "% of points (" << number_of_points << " points)" << std::endl;
#endif

    // Initialize random seed
    srand(time(NULL));

    // Initialize vector of points
    std::vector<point_type> points(number_of_points);

    for (size_type n = 0; n < number_of_points; n++) {
        // generate random numbers
        pos_x = rand() % SIZE;
        pos_y = rand() % SIZE;
        pos_z = rand() % SIZE;

        points[n] = point_type(pos_x, pos_y, pos_z);
    }

    std::sort(points.begin(), points.end() );
    points.erase( std::unique( points.begin(), points.end() ), points.end() );


    //************************//
    // TEST k3-tree Basic     //
    //************************//
    std::cout << std::endl << "Testing k3-tree Basic" << std::endl;
    test_get_region<sdsl::k3_tree<>>(points);

    //************************//
    // TEST k3-tree Points    //
    //************************//
    std::cout << std::endl << "Testing k3-tree Points" << std::endl;
    test_get_region<sdsl::k3_tree_points<>>(points);

    //************************//
    // TESt k3-tree Levels     //
    //************************//
    std::cout << std::endl << "Testing k3-tree Levels" << std::endl;
    test_get_region<sdsl::k3_tree_level<>>(points);
}
