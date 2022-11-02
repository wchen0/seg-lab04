#!/bin/bash

work_dir=$1
cd $1
echo "loading programs from $(pwd)"

CRTDIR=$(pwd)
declare -a folder_array
i=0

for folder in ${CRTDIR}/*; 
do
    temp_folder=`basename $folder`
    folder_array[i]=$temp_folder
    ((i=i+1))
done



for i in "${!folder_array[@]}"
do
    echo cluster "$i": "${folder_array[$i]}"
done

base_dir=${CRTDIR}



for i in "${!folder_array[@]}"
do
    cd "${base_dir}/${folder_array[$i]}"
    CRTDIR=$(pwd)
    echo "in ${CRTDIR}"
    declare -a file_array

    for file in ${CRTDIR}/*; 
    do
        temp_file=`basename $file`
        file_array[i]=$temp_file
        ((i=i+1))
    done

    for prog in ${CRTDIR}/*;
    do
        if [[ $prog == ${CRTDIR}/*.cpp ]]
        then
            readarray -d . -t output_filename_ls<<<"$prog"

            execut=${output_filename_ls[0]}
            output_folder="${execut}_output"
            mkdir output_folder
            
            
            echo run "\e[41m${execut}\e[0m", input:
            ${execut} <${CRTDIR}"/stdin_random.txt" >${output_filename}
            echo "output generated in ${output_filename}"
        fi
    done

done