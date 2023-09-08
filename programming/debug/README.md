# Problem

You were given a cpp file that is supposed to display the numbers in increasing order, but it is not working (see original.cpp)

```cpp
    // retrieve and display "0,1,2,3,4,5,6,7,8,9,10"
    for(int i = 0; i <= numSize; i++) {
        for(int j = 0; j < i; j++) {
            char c = (j <= i) ? ',' : '\r';
            cout << position[j]->get() << c;
        }
    }
```

Modify the code to display the numbers in increasing order in each new line. For example
0\
0,1\
0,1,2\
...
0,1,2,3,4,5,6,7,8,9,10\

Additionally, modify the code to also display alphabets in increasing order. For example
A\
A,B\
A,B,C\
...
A,B,C,D,E,F,G,H,I,J,K\

Make additional improvements as you see fit

# Solution

The code has a few problems.\
We look at the inner loop first.\
This prints out the numbers j until it reaches i.\
So in the last case, where i = 10, the loop will run 10 times.\
But it will only print 0,1,2,3,4,5,6,7,8,9.\
So we end up missing the last number (expecting to print the number 10).\
The second problem is that the carriage return does not actually moves the cursor to the next line.\
So we need to add a new line character to the end of the string.\

As for the second part of the problem, we can use the same logic as the first part.\
We just need to convert the numbers to alphabets via ASCII.\
Notice that the ASCII table A is 65, so we just need to add 65 to the number output and cast the int to char.\

In order to make it easier for displaying both solutions in the same code, we refactor the display code portion into a function.\
We also add a new parameter to the function to indicate if we are displaying numbers or alphabets.\

Additionally instead of doing a manual clean up, we will use unique_ptr to manage the memory for us.

# Compile
To compile run the compile.sh

# Clean
To clean the build, run clean.sh