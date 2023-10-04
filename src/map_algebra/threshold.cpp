// k3-tree
#include <k3_tree_base.hpp>
#include <k3_tree.hpp>
#include <sdsl/vectors.hpp>

void print_help(char * argv0) {
    printf("Usage: %s <k3_tree_file> <threshold> <output_k3_tree_file>\n", argv0);
}

template <typename k3_tree_type, typename t_bv=sdsl::bit_vector, 
          typename t_rank=typename t_bv::rank_1_type>
void run_thresh(std::string k3_tree_file_in, size_t thresh){
    
    //************************//
    // Load structure         //
    //************************//
    std::ifstream input_file(k3_tree_file_in);
    assert(input_file.is_open() && input_file.good());

    k3_tree_type k3_tree;
    k3_tree.load(input_file);
    input_file.close();

    //************************//
    // Parameters             //
    //************************//
    int min = 0; int max = 0;
    int k3_size_x = k3_tree.get_max_size_x();
    int k3_size_y = k3_tree.get_max_size_y();
    //////// execution parameters
    size_t submatrix_size_l = k3_size_x;
    size_t node_pos;
    size_t children_pos = 0;
    /////// k3_tree parameters
    uint8_t k = k3_tree.get_k_k1();
    size_t k_k1_3 = pow(k, 3);
    t_rank k_t_rank = k3_tree.get_k_t_rank();
    uint16_t k_height = k3_tree.get_k_height();
    t_bv k_t = k3_tree.get_k_t();
    t_bv k_l = k3_tree.get_k_l();
    /////// result
    std::string result;

    //************************//
    // Prints                 //
    //************************//
    k3_tree.print();
    std::cout << "Tamano de matriz " << k3_tree.get_max_size_z() << std::endl;
    std::cout << "min = " << min << " max = " << max << std::endl;
    std::cout << "Thresh = " << thresh << std::endl;
    std::cout<< "submatriz_size_l = " << submatrix_size_l << std::endl;
    std::cout<< "k_height = " << k_height << std::endl;
    std::cout<< "k^3 = " << k_k1_3 << std::endl;

    std::cout << "ktrank = ";
    for(int i=0; i<k_t_rank.size(); i++){
        std::cout << k_t_rank (i) << " " ;
    }
    std::cout << "\n";
    
    //************************//
    // Code execution         //
    //************************//
    // each point of the tree
    for(int pos_x=0; pos_x<k3_size_x; pos_x++){
        for(int pos_y=0; pos_y<k3_size_y; pos_y++){
            /*// search for thresh
            for (uint16_t l = 0; l < k_height-1; l++) {
                submatrix_size_l /= k;
                std::cout << "submatriz("<< l << ") = " << submatrix_size_l << std::endl;
                node_pos = (pos_x / submatrix_size_l) * k * k + pos_y / submatrix_size_l * k + thresh / submatrix_size_l;
                node_pos += children_pos;
                std::cout << "node_pos(" << l << ") = " << node_pos << std::endl;
                if (k_t[node_pos] == 0) {
                    return false; // Empty submatrix
                } else {
                    // Go to next level
                    children_pos = k_t_rank (node_pos+1) * k_k1_3;
                }
                std::cout << "children_pos(" << l << ") = " << children_pos << std::endl;
                // Calculate local position on the current submatrix
                pos_x %= submatrix_size_l;
                pos_y %= submatrix_size_l;
                thresh %= submatrix_size_l;
                std::cout << "x=" << pos_x << " y=" << pos_y << " z=" << thresh << "   ("<< l << ")" << std::endl;
            }


            // Last level
            submatrix_size_l /= k;
            std::cout << "submatrix_size_l (last level) = " << submatrix_size_l << std::endl;
            node_pos = (pos_x / submatrix_size_l) * k * k + pos_y / submatrix_size_l * k + thresh / submatrix_size_l;
            node_pos += children_pos;
            std::cout << "node_pos = " << node_pos << " \nchildren_pos = " << children_pos << " (last level)" << std::endl;
            std::cout << "k_l[" << (node_pos-k_t.size()) << ", con k_t.size=" << k_t.size() << std::endl;
            return (k_l[node_pos - k_t.size()] == 1);*/
        }
    }
    
}

int main(int argc, char **argv) {
    
    // Input verification
    if (argc != 4) {
        print_help(argv[0]);
        exit(-1);
    }

    /*********************/
    /* Reads params      */
    /*********************/
    std::string k3_tree_file_in = argv[1];
    size_t thresh = atoi(argv[2]);
    std::string k3_tree_file_out = argv[3];
    
    // Read k3_type
    std::ifstream input_file(k3_tree_file_in);
    assert(input_file.is_open() && input_file.good());
    ushort k3_tree_type;
    sdsl::read_member(k3_tree_type, input_file);
    input_file.close();

    std::cout << "Threshold con umbral de " << thresh << std::endl;

    run_thresh<sdsl::k3_tree<>>(k3_tree_file_in, thresh);
}