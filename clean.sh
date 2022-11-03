#!/bin/bash

work_dir=$1
cd $1
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

base_dir=${CRTDIR}


for i in "${!folder_array[@]}"
do
    cd "${base_dir}/${folder_array[$i]}"
    CRTDIR=$(pwd)

    for file in ${CRTDIR}/*; 
    do
        if [[ $file == *\.* ]]
        then
            :
        else
            rm -r ${file}
            echo "remove ${file}"
        fi
    done

done
