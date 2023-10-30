// k3-tree
#include <k3_tree_base.hpp>
#include <k3_tree.hpp>
#include <sdsl/vectors.hpp>
#include <k3_tree_points.hpp>
#include <k3_tree_level.hpp>

typedef sdsl::k3_tree_base<>::size_type size_type;
typedef sdsl::k3_tree_base<>::size_type pos_type;
typedef sdsl::k3_tree_base<>::point_type point_type;

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

template <typename k3_tree_type, typename t_bv=sdsl::bit_vector, 
          typename t_rank=typename t_bv::rank_1_type>
void thresh_brute(std::string k3_tree_file_in, size_t thresh) {

    //************************//
    // Load structure         //
    //************************//

    std::ifstream input_file(k3_tree_file_in);
    assert(input_file.is_open() && input_file.good());

    k3_tree_type k3_tree;
    k3_tree.load(input_file);
    //************************//

    typedef sdsl::int_vector<>::size_type size_type;
    std::string output_filename = k3_tree_file_in + ".thresh";

    std::ofstream output_data(output_filename);
    assert(output_data.is_open() && output_data.good());

    

    int n = 0;
    size_type size = k3_tree.get_max_size_x();

    size_type number_of_points = size * 2;
    size_type pos_x, pos_y, pos_z;

    std::vector<point_type> points(number_of_points);

    //************************//
    // Threshold              //
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
                    
                    if (z < thresh) {
                        pos_z = 0;
                        sdsl::write_member(pos_x, output_data);
                        sdsl::write_member(pos_y, output_data);
                        sdsl::write_member(pos_z, output_data);

                    } else {
                        pos_z = 1;
                        sdsl::write_member(pos_x, output_data);
                        sdsl::write_member(pos_y, output_data);
                        sdsl::write_member(pos_z, output_data);
                    }
                    n+=1;
                }
            }
        }
    }
    output_data.close();
    std::sort(points.begin(), points.end() );
    points.erase( std::unique( points.begin(), points.end() ), points.end() );
    k3_tree_type k3_tree_out(output_filename, size);
    std::cout << std::endl;
    k3_tree_out.print();
    
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
    thresh_brute<sdsl::k3_tree<>>(k3_tree_file_in, thresh);
}