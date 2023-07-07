# Problem
You are given a server program that is able to accept multiple clients concurrently.

However what you want to achieve is to print out the thread ID as it receives messages from client programs with messages

# Solution

We will simply pass in a struct to the thread function that contains the thread ID, and have the create_thread function write the thread id to a reference of the struct

```cpp
    struct thread_data {
        int id;
        int sock;
    };
    ...
    thread_data th;
    ...
    if( pthread_create( &th.id , NULL ,  connection_handler , &th) < 0)
    ...
```

After compiling, run the threaded server program first

You can thererafter run multiple clients to connect to the server from different terminals

# Compile
To compile run the compile.sh

# Clean
To clean the build, run clean.sh