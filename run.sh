#!/bin/bash

para=$1
para_n=$2
targeted_dir="./input"


function move_output() {
	if [ -d ./output ]
	then
		:
	else
		mkdir output
	fi
	
	if [ -f "${targeted_dir}/equal.csv" ]
	then
		mv "${targeted_dir}/equal.csv" ./output/
	fi
	
	if [ -f "${targeted_dir}/inequal.csv" ]
	then
		mv "${targeted_dir}/inequal.csv" ./output/
	fi

	if [ -f "${targeted_dir}/error.csv" ]
	then
		mv "${targeted_dir}/error.csv" ./output/
	fi
}


if [ -z $1 ]
then
	echo "invalid command, use -h for help"
elif [ $1 == "-c" ]
then
	bash compile_all.sh ${targeted_dir}
elif [ $1 == "-e" ]
then
	bash execute_all.sh ${targeted_dir}
elif [ $1 == "-i" ]
then
	./input_generator/test ${targeted_dir} $2
elif [ $1 == "-j" ]
then
	./check_output/test ${targeted_dir}
	move_output
elif [ $1 == "-a" ]
then
	./input_generator/test ${targeted_dir} $2
	bash compile_all.sh ${targeted_dir}
	bash execute_all.sh ${targeted_dir}
	./check_output/test ${targeted_dir}
	move_output
elif [ $1 == "-h" ]
then
	echo "-i generate random input"
	echo "-c compile all programs"
	echo "-e execute all programs, compile if not compiled"
	echo "-j check programs output"
	echo "-a run all procedures"
	echo "-h help"
else
	echo "invalid command, use -h for help"
fi
