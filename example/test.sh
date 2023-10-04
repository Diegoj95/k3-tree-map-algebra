#!/bin/sh
echo "Testing alcoy_5_300k............"

echo "Creating a file with 1000 random queries"
../build/bin/create_get_region_queries ./output/alcoy_5_300k.k3tree ./output/queries_region_alcoy_5_300k.txt 100

echo "Running test"
../build/bin/k3_tree_LIDAR_get_region ./output/alcoy_5_300k.k3tree ./output/queries_region_alcoy_5_300k.txt 1

echo ""
echo ""
echo "Testing example_1............"

echo "Creating a file with 1000 random queries"
../build/bin/create_get_region_queries ./output/alcoy_5_300k.k3tree ./output/queries_region_example_1.txt 100

echo "Running test"
../build/bin/k3_tree_LIDAR_get_region ./output/alcoy_5_300k.k3tree ./output/queries_region_example_1.txt 1