#!/bin/bash

g++ check_output/check_output.cpp -o test
cd ./input_generator
make
cd ..