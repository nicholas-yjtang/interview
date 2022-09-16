To compile

Ensure you are on a linux compatible platform (for example ubuntu)\
Ensure the following libraries are installed (log4cxx gtest)\
liblog4cxx-dev\
libgtest-dev\

Run the following to compile/build the executable\
cmake .\
make

Running the application, the log4j.properties file should be in the folder (conf/log4j.properties), with the input as a text file, of the format\
row column\
x x x x x\
x x x x x

where x is 0, 1 or 2 to denote empty ward, uninfected patient, and infected patient respectively\
infect_time sample.txt

Alternatively you can use docker to build the sample, with the docker image called virus\
docker build -t virus .

To run, mount a folder with test files (for example test folder in your home directory)\
docker run -v ~/test:/opt/virus/test virus /opt/virus/test/sample.txt