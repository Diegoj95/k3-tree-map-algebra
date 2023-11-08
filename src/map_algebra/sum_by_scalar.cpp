// k3-tree
#include <k3_tree_base.hpp>
#include <k3_tree.hpp>
#include <sdsl/vectors.hpp>
#include <k3_tree_points.hpp>
#include <k3_tree_level.hpp>
#include <time.h>

typedef sdsl::k3_tree_base<>::size_type size_type;
typedef sdsl::k3_tree_base<>::size_type pos_type;
typedef sdsl::k3_tree_base<>::point_type point_type;

void print_help(char * argv0) {
    printf("Usage: %s <k3_tree_file> <scalar> <output_k3_tree_file>\n", argv0);
}

template <typename k3_tree_type, typename t_bv=sdsl::bit_vector, 
          typename t_rank=typename t_bv::rank_1_type>
void scalar_sum(std::string k3_tree_file_in, size_t scalar){
    
    // //************************//
    // // Load structure         //
    // //************************//
    // std::ifstream input_file(k3_tree_file_in);
    // assert(input_file.is_open() && input_file.good());

    // k3_tree_type k3_tree;
    // k3_tree.load(input_file);
    // k3_tree.threshold(thresh);
    // input_file.close();
    return;
  
}

template <typename k3_tree_type, typename t_bv=sdsl::bit_vector, 
          typename t_rank=typename t_bv::rank_1_type>
void scalar_sum_brute(std::string k3_tree_file_in, size_t scalar) {

    //************************//
    // Load structure         //
    //************************//

    std::ifstream input_file(k3_tree_file_in);
    assert(input_file.is_open() && input_file.good());

    k3_tree_type k3_tree;
    k3_tree.load(input_file);
    //************************//

    k3_tree.print();

    typedef sdsl::int_vector<>::size_type size_type;
    std::string output_filename = k3_tree_file_in + ".scalar";

    std::ofstream output_data(output_filename);
    assert(output_data.is_open() && output_data.good());

    int n = 0;
    size_type size = k3_tree.get_max_size_x();
    size_type number_of_points = size * size;
    size_type pos_x, pos_y, pos_z;

    std::vector<point_type> points(number_of_points);

    //************************//
    // Sum by scalar          //
    //************************//
    // Iterate over all nodes

    for(int x=0; x<size; x++) {
        // Iterate over all children
        for(int y=0; y<size; y++) {
            // Iterate over all children
            for(int z=0; z<size; z++) {
                if (k3_tree.get(x,y,z) == 1) {
                    pos_x = x;
                    pos_y = y;
                    pos_z = z + scalar;
                                 
                    sdsl::write_member(pos_x, output_data);
                    sdsl::write_member(pos_y, output_data);
                    sdsl::write_member(pos_z, output_data);

                    continue;
                }
            }
        }
    }
    output_data.close();
    std::sort(points.begin(), points.end() );
    points.erase( std::unique( points.begin(), points.end() ), points.end() );

    k3_tree_type k3_tree_out(output_filename, size + scalar);
    std::cout << std::endl;
    k3_tree_out.print();
    std::cout << std::endl;
    //k3_tree.print();

    // ************************//
    // Load structure          //
    // ************************//

    // std::ifstream input_files("k3_output.thresh");
    // assert(input_files.is_open() && input_files.good());

    // k3_tree_type k3_tree_compare;
    // k3_tree_compare.load(input_files);

    // std::cout << "It's equal: " << k3_tree_out.operator==(k3_tree_compare) << std::endl;
    
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
    size_t scalar = atoi(argv[2]);
    std::string k3_tree_file_out = argv[3];
    
    // Read k3_type

    std::ifstream input_file(k3_tree_file_in);
    assert(input_file.is_open() && input_file.good());
    ushort k3_tree_type;
    sdsl::read_member(k3_tree_type, input_file);
    input_file.close();
    

    //calculate time for run_sum function
    clock_t begin = clock();
    // scalar_sum<sdsl::k3_tree<>>(k3_tree_file_in, scalar);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    //calculate time for scalar_sum_brute function
    clock_t begin2 = clock();
    scalar_sum_brute<sdsl::k3_tree<>>(k3_tree_file_in, scalar);
    clock_t end2 = clock();
    double elapsed_secs2 = double(end2 - begin2) / CLOCKS_PER_SEC;
    std::cout << "Time for scalar_sum function: " << elapsed_secs << "\n" << std::endl;
    std::cout << "Time for scalar_sum_brute function: " << elapsed_secs2 << "\n" << std::endl;
}   