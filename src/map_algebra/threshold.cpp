// k3-tree
#include <k3_tree_base.hpp>
#include <k3_tree.hpp>
#include <sdsl/vectors.hpp>
#include <k3_tree_points.hpp>
#include <k3_tree_level.hpp>
#include <time.h>
#include <filesystem>
#include <string>
#include <string>

typedef sdsl::k3_tree_base<>::size_type size_type;
typedef sdsl::k3_tree_base<>::size_type pos_type;
typedef sdsl::k3_tree_base<>::point_type point_type;

void print_help(char * argv0) {
    printf("Usage: %s <k3_tree_file> <threshold> <output_k3_tree_file>\n", argv0);
}

template <typename k3_tree_type, typename t_bv=sdsl::bit_vector,
          typename t_rank=typename t_bv::rank_1_type>
k3_tree_type get_k3(std::string k3_tree_filename) {
    
    //************************//
    // Load structure         //
    //************************//
    std::ifstream input_file(k3_tree_filename);
    assert(input_file.is_open() && input_file.good());
    k3_tree_type k3_tree;
    k3_tree.load(input_file);
    input_file.close();
    //k3_tree.print();
    return k3_tree;  // Devuelve el objeto k3_tree creado y cargado
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
    clock_t begin = clock();
    k3_tree.threshold(thresh);
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << std::fixed << std::setprecision(10) << "Time for thresh_method function: " << elapsed_secs << "\n" << std::endl;
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

    
    clock_t begin2 = clock();
    int n = 0;
    size_type size = k3_tree.get_max_size_x();

    size_type number_of_points = size * size;
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
                    continue;
                }
            }
        }
    }
    output_data.close();
    std::sort(points.begin(), points.end() );
    points.erase( std::unique( points.begin(), points.end() ), points.end() );
    k3_tree_type k3_tree_out(output_filename, size);
    clock_t end2 = clock();
    double elapsed_secs2 = double(end2 - begin2) / CLOCKS_PER_SEC;
    std::cout << std::fixed << std::setprecision(10) << "Time for thresh_get function: " << elapsed_secs2 << "\n" << std::endl;

    // std::cout << std::endl;
    // k3_tree_out.print();
    // std::cout << std::endl;
    
    //k3_tree.print();

    // ************************//
    // Load structure         //
    // ************************//

    // std::ifstream input_files("k3_output.thresh");
    // assert(input_files.is_open() && input_files.good());

    // k3_tree_type k3_tree_compare;
    // k3_tree_compare.load(input_files);

    // std::cout << "It's equal: " << k3_tree_out.operator==(k3_tree_compare) << std::endl;
    
}

template <typename k3_tree_type, typename t_bv=sdsl::bit_vector, 
          typename t_rank=typename t_bv::rank_1_type>
void thresh_brute2(std::string k3_tree_file_in, size_t thresh) {

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

    clock_t begin3 = clock();
    size_type size = k3_tree.get_max_size_x();

    size_type number_of_points = size * size;
    size_type pos_x, pos_y, pos_z;

    std::vector<point_type> points(number_of_points);

    //************************//
    // Threshold              //
    //************************//
    // Iterate over all nodes

    size_t point_counter = 0;
    for(int x=0; x<size; x++) {
        // Iterate over all children
        for(int y=0; y<size; y++) {
            // Iterate over all children
            pos_x = x;
            pos_y = y;
            
            if(k3_tree.get_z(x,y)<thresh){
                pos_z = 0;
            }else{
                pos_z = 1;
            }
            // std::cout << "Valor de Z = " << pos_z << " (" << x << "," << y << ")" << std::endl;
            sdsl::write_member(pos_x, output_data);
            sdsl::write_member(pos_y, output_data);
            sdsl::write_member(pos_z, output_data);
            point_counter+=1;
        }
    }
    // Comparacion de espacio utilizado en los puntos de salida
    std::cout << "Peso del vector de puntos: " << output_data.tellp() << std::endl;
    output_data.close();
    std::sort(points.begin(), points.end() );
    
    size_t total_size_in_bytes = point_counter * 24;
    std::cout << "Total size of output_data in bytes: " << total_size_in_bytes << std::endl;
    //std::filesystem::path file_path(output_filename);
    //auto file_size = std::filesystem::file_size(file_path);
    //std::cout << "Size of output file in bytes: " << file_size << std::endl;
    points.erase( std::unique( points.begin(), points.end() ), points.end() );
    k3_tree_type k3_tree_out(output_filename, size);
    clock_t end3 = clock();
    double elapsed_secs3 = double(end3 - begin3) / CLOCKS_PER_SEC;
    std::cout << std::fixed << std::setprecision(10) << "Time for thresh_get_z function: " << elapsed_secs3 << "\n" << std::endl;

    // std::cout << "Bruto2:" << std::endl;
    // k3_tree_out.print();
    // std::cout << std::endl;
    
    //k3_tree.print();

    // ************************//
    // Load structure         //   SOLO  PARA  COMPARAR  SI  SON  IGUALES
    // ************************//

    // std::ifstream input_files("k3_output.thresh");
    // assert(input_files.is_open() && input_files.good());

    // k3_tree_type k3_tree_compare;
    // k3_tree_compare.load(input_files);

    // std::cout << "It's equal: " << k3_tree_out.operator==(k3_tree_compare) << std::endl;
    
}

// Función para encontrar la posición del threshold 't' en el vector
int findThresholdPosition(const std::vector<size_type>& vec, int t) {
    int left = 0;
    int right = vec.size();

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (vec[mid] < t) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left; // Devuelve la posición donde comienzan los valores >= t
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
    
    // Cargar la estructura //
    auto k3_tree = get_k3<sdsl::k3_tree<>>(k3_tree_file_in);

    //calculate time for run_tresh function
    
    //thresh_brute<sdsl::k3_tree<>>(k3_tree_file_in, thresh);
    
    thresh_brute2<sdsl::k3_tree<>>(k3_tree_file_in, thresh);
    
    //run_thresh<sdsl::k3_tree<>>(k3_tree_file_in, thresh);

    //k3_tree.print();

    //////TEST//////
    size_type newvaluev;
    std::vector<size_type> v;        
    int flag; 
    
    for(int x=0; x<k3_tree.get_max_size_x(); x++){
        for(int y=0; y<k3_tree.get_max_size_x(); y++){
            newvaluev = k3_tree.get_z(x, y);
            flag = 0;
            
            for(int i=0; i<v.size(); i++){
                if(v[i]==newvaluev){
                    flag = 1;
                    break;
                }
            }
            if(flag == 0){
                v.push_back(newvaluev);
                std::sort(v.begin(), v.end());
            }
        }
    }

    clock_t begin4 = clock();
    int position = findThresholdPosition(v, thresh);
    clock_t end4 = clock();
    double elapsed_secs4 = double(end4 - begin4) / CLOCKS_PER_SEC;
    std::cout << std::fixed << std::setprecision(10) << "Time for thresh_k2_acc function: " << elapsed_secs4 << "\n" << std::endl;
    std::cout << "El threshold " << thresh << " se encuentra en la posición: " << position << std::endl;
}   