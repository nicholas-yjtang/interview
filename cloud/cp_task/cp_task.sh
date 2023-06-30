#!/bin/bash

#check there are at least 2 parameters, first parameter being the a currently valid directory, second parameter being the name of the new directory
if [ $# -lt 2 ]; then
    echo "Usage: ./cp_task.sh <source directory> <destination directory>"
    exit 1
fi

#check if the first argument is a directory
if ! [ -d $1 ]; then
    echo "The first argument must be a directory"
    exit 1
fi

#create new directory
mkdir -p $2

#copy files from source directory to destination directory, prepending the last modified date with the time of the file to the file name
for file in $1/*; do
    stat -c %y $file | awk '{print $1}' | xargs -I {} cp $file $2/{}_$(basename $file)
done