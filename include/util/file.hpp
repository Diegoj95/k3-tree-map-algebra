/*  
 * Created by Fernando Silva on 9/04/18.
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

#ifndef INCLUDED_SDSL_K3_TREE_FILE
#define INCLUDED_SDSL_K3_TREE_FILE

//! Namespace for the succint data structure library
namespace sdsl {

    typedef sdsl::int_vector<>::size_type size_type;

    void add_random_points(size_type size, size_type number_of_points, std::ofstream &output_data) {
        size_type pos_x, pos_y, pos_z;

        // Initialize random seed
        srand(time(NULL));

        for (size_type n = 0; n < number_of_points; n++) {
            // generate random numbers
            pos_x = rand() % size;
            pos_y = rand() % size;
            pos_z = rand() % size;

            sdsl::write_member(pos_x, output_data);
            sdsl::write_member(pos_y, output_data);
            sdsl::write_member(pos_z, output_data);
        }

        output_data.close();
    }
} // END NAMESPACE sdsl

#endif // INCLUDED_SDSL_K3_TREE_FILE
