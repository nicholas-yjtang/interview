#!/bin/bash

#generate empty files in a directory
#usage: ./generate_files.sh <number of files> <directory>

#check how many arguments were passed
if [ $# -eq 0 ]; then
    echo "Usage: ./generate_files.sh <number of files> <directory>"
    exit 1
fi

#check if the first argument is a number
if ! [[ $1 =~ ^[0-9]+$ ]]; then
    echo "The first argument must be a number"
    exit 1
fi

#check if second argument is not empty
if [ -z "$2" ]; then
    echo "The second argument must not be empty"
    exit 1
fi

#check if the second argument directory already exists, if it does not, create it
if ! [ -d $2 ]; then
    mkdir -p $2
fi

#generate the files
for i in $(seq 1 $1); do
    touch $2/file$i
done