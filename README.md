### NJUCS, Software Engineering, Lab04

Generate random input for multiple C++ programs and judge whether they are equivalent.   

File structure is shown below.
.
├── check_output
│   ├── check_output.cpp
│   └── makefile
├── clean.sh
├── compile_all.sh
├── execute_all.sh
├── init.sh
├── input
│   ├── 4A
│   ├── 50A
│   └── my_test
├── input_generator
│   ├── input_generator.cpp
│   ├── input_generator.h
│   ├── makefile
│   └── stdin_format_parser.cpp
├── LICENSE
├── README.md
└── run.sh


1. Put all your source code of programs in directory `input`.    
Each cluster contains several programs to be tested, for emample    

input
├── cluster1
│   ├── 101036360.cpp
│   ├── 117364748.cpp
│   ├── 127473352.cpp
│   ├── 134841308.cpp
│   ├── 173077807.cpp
│   └── stdin_format.txt
├── cluster2
│   ├── 138805414.cpp
│   ├── 142890373.cpp
│   ├── 164831265.cpp
│   └── stdin_format.txt
└── cluster3
    ├── 1.cpp
    ├── 2.cpp
    ├── 3.cpp
    └── stdin_format.txt

2. run `bash init.sh` to initialize and compile this tool.
3. run `bash run.sh -a N` to test every program in every cluster with `N` sets of random input.
4. N sets of random input and output will be generated in each cluster's directory.
5. The results will be in output/equal.csv, output/inequal.csv and output/error.csv, TLE.txt has all time-limit-exceeded cases.
6. run `bash run.sh -d` to clean all results.

Last update: 2022-11-04