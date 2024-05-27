#!/bin/bash

build_dir="build"
prefix='#====[ Linux C++ Sandbox ]===# '

echo $prefix "Initializing repository."

rm -rf $build_dir
mkdir $build_dir
cd $build_dir
cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
make -j 16

echo $prefix "Done."
