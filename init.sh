#!/bin/bash

cd ./check_output
make
cd ..

cd ./input_generator
make
cd ..
