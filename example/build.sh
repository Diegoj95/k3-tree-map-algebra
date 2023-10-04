#!/bin/sh

rm -rf output
mkdir output
../build/bin/k3_tree_LIDAR_encode ./data/alcoy_5_300k.laz ./output/alcoy_5_300k.k3tree 1 10
../build/bin/k3_tree_LIDAR_encode ./data/example_1.laz ./output/example_1.k3tree 1 10

#xdg-open ./output/alcoy_5_300k.k3tree.html
