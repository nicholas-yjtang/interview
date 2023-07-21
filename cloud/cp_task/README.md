# Problem

How would you copy the contents of a directory into a new directory? Copy a file into the new directory, changing the name of the file by add the last modified date to the beginning of the original filename

# Solution

We created a bash script (cp_task) that takes in two arguments, the first being the directory you want to copy, and the second being the directory you want to copy to. The script will perform stat on the file to get the last modified date, and then copy the file into the new directory, changing the name of the file by adding the last modified date to the beginning of the original filename.

Run cp_task.sh with the first argument being the directory you want to copy, and the second argument being the directory you want to copy to.