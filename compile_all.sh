#!/bin/bash

work_dir=$1
cd $1
CRTDIR=$(pwd)
echo "loading programs from ${CRTDIR}"



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

    for src_code in ${CRTDIR}/*.cpp;
    do
        readarray -d . -t output_filename_ls<<<"$src_code"

        execut=${output_filename_ls[0]}
        echo -e "compile \e[31m${src_code}\e[0m as \e[34m${execut}\e[0m"
        g++ ${src_code} -o ${execut} -w # ignore all warnings
    done

done