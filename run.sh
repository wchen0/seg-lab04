#!/bin/bash

para=$1
para_n=$2
targeted_dir="./input"


start=$(date +%s)


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
elif [ $1 == "-d" ]
then
	bash clean.sh ${targeted_dir}
	if [ -z $2 ]
	then
		:
	elif [ $2 == "1" ]
	then
		cd ./input_generator
		make clean
		cd ..
		cd ./check_output
		make clean
		cd ..
	fi
elif [ $1 == "-h" ]
then
	echo "-i N		generate random input, N=16 by default"
	echo "-c 		compile all programs"
	echo "-e 		execute all programs, compile if not compiled"
	echo "-j 		check programs output"
	echo "-a N 	run all procedures, N=16 by default"
	echo "-d 		clean"
	echo "-h 		help"
else
	echo "invalid command, use -h for help"
fi





end=$(date +%s)
take=$(( end - start ))
echo Time taken to execute commands is ${take} seconds.