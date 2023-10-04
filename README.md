k<sup>3</sup>-tree -  A compacta data strucutre to represent a 3-dimensional binary matrix
=========================



## Compilation ##
 
 To compile the code you need to execute the following commands:
 ```bash
 cd k3-tree_sdsl
 mkdir build
 cd build
 cmake -DCMAKE_BUILD_TYPE=Release ..
 make
 ```
 or 
  ```bash
  cd k3-tree_sdsl
  sh compile.sh
 ```
 
 
 Executables files are stored in
 * ./build/bin/
 
 Library files are stored in
 * ./build/lib/


## Encode data ##

To encode a file of unsigned integers (32 bits), you have to run the command:

 ```bash
 ./k3_tree_encode <input_data> <size> <output_data> <set_check> <k3_tree_type>
 ```

Where:
* **\<input_data>** input file (lit of unsigned integers of 32 bits)
* **\<size>** size of the input data (size x size x size)
* **\<output_data>** output path where store the k<sup>3</sup>-tree
* **\<check>** A 1 if after constructing the structure performs a check point by point. Or a 0 otherwise
* **\<k3_tree_type>** Type of k<sup>3</sup>-tree that is used to encode the input data. The possible values are:
    * **Type 0**: Basic k<sup>3</sup>-tree
    * **Type 1**: k<sup>3</sup>-tree with limit of points
    * **Type 2**: k<sup>3</sup>-tree with limit of levels

#### Example ####
For example, a data cube of size 6x6x6 with 4 points [(0, 2, 3), (2, 2, 5), (3, 5, 1) and (5, 5, 6)] is stored  in ./input_data.bin as sequence of unsigned integers of 32 bits. And we want to encode with type 0 (basic k<sup>3</sup>-tree)

The input file would be: \[ 0 2 3 2 2 5 3 5 1 5 5 6 ] (4 points * 3 coordinates = 12 values, where the first three numbers correspond to the first point, the next three numbers correspond to the second point and so on).

```bash
 ./k3_tree_encode ./input_data.bin 6 ./output_file.k3tree 1 0
```


## Encode LIDAR data ##

To encode a LIDAR file, you have to run the command:

```bash
 ./k3_tree_LIDAR_encode <input_data> <n_digits> <n_params> <output_data> <set_check>
```

Where:
* **\<input_data>** input file (a LAS or LAZ file)
* **\<output_data>** output path where store the k<sup>3</sup>-tree
* **\<check>** A 1 if after constructing the structure performs a check point by point. Or a 0 otherwise
* **\<k3_tree_type>** Type of k<sup>3</sup>-tree that is used to encode the input data. The possible values are:
    * **Type 10**: k<sup>3</sup>-tree LIDAR with limit of points
    
#### Example ####
```bash
 ./k3_tree_LIDAR_encode ./input_data.las ./output_file.k3tree 1 10
```


## Queries ##

#### Obtaining a point ####
Given a position (x, y, z), this query returns if there is that point in the dataset.
 
```bash
./k3_tree_get <k3_tree_file> <query_file>
```
Where:
  
* **\<k3_tree_file>** Path of the file where the *k<sup>3</sup>-tree* is stored 
* **\<query_file>**  File with a set of queries. Each line is a query with format *"pos_X pos_Y pos_Z"*

#### Obtaining a point (with attributes) ####

Given a position (x, y, z), this query returns the information about that point. Only for k<sup>3</sup>-tree LIDAR.
 
```bash
./k3_tree_LIDAR_get <k3_tree_file> <query_file>
```
Where:
  
* **\<k3_tree_file>** Path of the file where the *k<sup>3</sup>-tree* is stored 
* **\<query_file>**  File with a set of queries. Each line is a query with format *"pos_X pos_Y pos_Z"*


#### Obtaining all points of a region ####
Given a region, this query retrieves all points that are within that region.

```bash
 ./k3_tree_get_region <k3_tree_file> <query_file> <check>
 ```
 Where:
 
 * **\<k3_tree_file>** Path of the file where the *k<sup>3</sup>-tree* is stored 
 * **\<query_file>**  File with a set of queries. Each line is a query with format *"i_pos_X i_pos_Y i_pos_Z e_pos_X e_pos_Y e_pos_Z"* (**i**nitial and **e**nd point)
 * **\<check>** 1 to check if the final result is correct. 0 in other case.

#### Obtaining all points of a region (with attributes)####
Given a region, this query retrieves all points that are within that region. For each point information of its attributes is included. Only for k<sup>3</sup>-tree LIDAR.

```bash
 ./k3_tree_LIDAR_get_region <k3_tree_file> <query_file> <check>
 ```
 Where:
 
 * **\<k3_tree_file>** Path of the file where the *k<sup>3</sup>-tree* is stored 
 * **\<query_file>**  File with a set of queries. Each line is a query with format *"i_pos_X i_pos_Y i_pos_Z e_pos_X e_pos_Y e_pos_Z"* (**i**nitial and **e**nd point)
 * **\<check>** 1 to check if the final result is correct. 0 in other case.


#### Implemented By ####
Fernando Silva-Coira - <fernando.silva@udc.es>


