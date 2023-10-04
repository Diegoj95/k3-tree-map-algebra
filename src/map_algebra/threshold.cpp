// k3-tree
#include <k3_tree_base.hpp>
#include <k3_tree.hpp>

void print_help(char * argv0) {
    printf("Usage: %s <k3_tree_file> <threshold> <size> <output_k3_tree_file>\n", argv0);
}

template <typename k3_tree_type>
void run_thresh(std::string k3_tree_file_in, size_t size){
    
    //************************//
    // Load structure         //
    //************************//
    std::ifstream input_file(k3_tree_file_in);
    assert(input_file.is_open() && input_file.good());

    k3_tree_type k3_tree;
    k3_tree.load(input_file);
    input_file.close();

    k3_tree.print();

}

int main(int argc, char **argv) {
    
    // Input verification
    if (argc != 5) {
        print_help(argv[0]);
        exit(-1);
    }

    /*********************/
    /* Reads params      */
    /*********************/
    std::string k3_tree_file_in = argv[1];
    size_t thresh = atoi(argv[2]);
    size_t size = atoi(argv[3]);
    std::string k3_tree_file_out = argv[4];
    
    // Read k3_type
    std::ifstream input_file(k3_tree_file_in);
    assert(input_file.is_open() && input_file.good());
    ushort k3_tree_type;
    sdsl::read_member(k3_tree_type, input_file);
    input_file.close();

    std::cout << thresh << std::endl;

    std::cout << size << " tamaño entrada " << std::endl;

    run_thresh<sdsl::k3_tree<>>(k3_tree_file_in, size);
}