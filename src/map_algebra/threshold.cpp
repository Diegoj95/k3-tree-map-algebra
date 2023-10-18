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
    k3_tree.threshold(thresh);
    input_file.close();
  
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


    run_thresh<sdsl::k3_tree<>>(k3_tree_file_in, thresh);
}