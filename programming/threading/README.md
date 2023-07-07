# Problem
You are given a server program that is able to accept multiple clients concurrently.

```cpp
    ...
    void *connection_handler(void *socket_desc);
    ...
    int socket_desc , client_sock , c;
    pthread_t thread_id;

    while((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        ,,,         
        if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) client_sock) < 0)
        ...
    }
    ...
```
However what you want to achieve is to print out the thread ID as it receives messages from client programs with messages inside the implementation of the connection_handle. How would you do this?

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

## Additional note

In the original implementation, the server and client program has a bug where the client program will occasionally block on waiting for a 2nd recv call. This is because a streaming connection itself does not know boundaries of the message being sent, and in this case, the 2 send calls from the server were combined into a single recv call on the client, so the client program will wait indefinitely for the 2nd recv call.

In order to fix this issue, you will need to implement a protocol that will allow the client to know when the message has ended.

In our case we wait to receive an OK message from the client before we move onto the next message.

Other possible implementations include sending the length of the message before sending the message itself.

# Compile
To compile run the compile.sh

# Clean
To clean the build, run clean.sh