#!/bin/bash

cd ./check_output
g++ ./check_output.cpp -o test
cd ..

cd ./input_generator
make
cd ..
