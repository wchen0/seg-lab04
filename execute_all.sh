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
    if [ -d $temp_folder ]
    then
        folder_array[i]=$temp_folder
        ((i=i+1))
    fi
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
        echo -e "run \e[31m${execut}\e[0m"
        execut=${src_code%.*}
        input_folder="${CRTDIR}/random_input"
        output_folder="${execut}_out"

        if [ -d $output_folder ]
        then
            rm -r ${output_folder}
            mkdir ${output_folder}
        else
            mkdir ${output_folder}
        fi

        for input_file in ${input_folder}/*.txt
        do
            # echo -e "run \e[31m${execut}\e[0m, input=\e[31m${input_file}\e[0m"
            k=${input_file##*/}
            k=${k%.*}
            if [ -f $execut ]
            then
                ${execut} <"${input_file}">"${output_folder}/${k}.txt"
            else
                g++ ${src_code} -o ${execut} -w # ignore all warnings
                echo -e "compile \e[31m${src_code}\e[0m as \e[34m${execut}\e[0m"
                ${execut} <"${input_file}">"${output_folder}/${k}.txt"
            fi
            # echo "output generated in ${output_folder}/${k}.txt"
        done
    done

done