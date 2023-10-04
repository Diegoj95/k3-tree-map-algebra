/*  
 * Created by Fernando Silva on 3/04/18.
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

#ifndef INCLUDED_SDSL_K3_TREE_CONCEPTUAL_NODE
#define INCLUDED_SDSL_K3_TREE_CONCEPTUAL_NODE

#include <cstdint>
#include <cstdio>
#include <cmath>
#include <cstdlib>

namespace sdsl {

class conceptual_node
{
    private:
        conceptual_node **children;

    public:

    //*******************************************************//
    //******************* CONSTRUCTOR ***********************//
    //*******************************************************//
    conceptual_node(){
        children = nullptr;
    }

    ~conceptual_node() {
        if (has_children()) {
            free(children);
        }
    }

    //*******************************************************//
    //******************** CHILDREN *************************//
    //*******************************************************//
    conceptual_node * get_child(size_t pos) {
        if (!has_children()) {
            return nullptr;
        } else {
            return children[pos];
        }
    }

    bool has_children() {
        return children != nullptr;
    }

    void initialize_children(uint8_t k){
        if (!has_children()) {
            size_t n_children = pow(k,3);
            children = (conceptual_node**)malloc(n_children * sizeof(conceptual_node*));
            for (size_t c = 0; c < n_children; c++) {
                children[c] = nullptr;
            }
        }
    }

    conceptual_node* insert_node(size_t pos, uint8_t k) {
        assert(pos < pow(k,3));

        if (!has_children()) {
            initialize_children(k);
        }

        if (children[pos] == nullptr) {
            // Create a new child
            children[pos] = new conceptual_node();
        }

        return children[pos];
    }
}; // END CLASS conceptual_node

} // END NAMESPACE sdsl

#endif // INCLUDED_SDSL_K3_TREE_CONCEPTUAL_NODE
