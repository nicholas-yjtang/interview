/*
    C socket server example, handles multiple clients using threads
    Compile
    gcc server.c -lpthread -o server
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
 
typedef struct st {
    int id;
    int socket;
} sock_thread;

//the thread function
void *connection_handler(void *);
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;
     
    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( 8888 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    //puts("Waiting for incoming connections...");	//	PWK, repeated below
    //c = sizeof(struct sockaddr_in);			//	PWK, repeated below

    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	pthread_t thread_id;
	
    struct st th;
    th.id = 0;
    th.socket = 0;

    sock_thread testsock;
    sock_thread *ptr = (sock_thread*) &testsock;
    ptr->id = 0;
    ptr->socket = 0;

    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ) {
        puts("Connection accepted");

        ptr->socket = client_sock;
        ptr->id++;

        th.socket = client_sock;
        th.id++;

        // if( pthread_create( &thread_id , NULL ,  connection_handler , (void*) &client_sock) < 0)
        // if( pthread_create( &thread_id , NULL ,  connection_handler , ptr) < 0)
        if( pthread_create( &thread_id , NULL ,  connection_handler , &th) < 0)
        {
            perror("could not create thread");
            close(client_sock);
            return 1;
        }
        puts("Handler assigned");

        //Now join the thread , so that we dont terminate before the thread
        if(pthread_join( thread_id , NULL)==0)
            printf("%d:thread exit and joined\n", ptr->id);
    }

    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }
    return 0;
}
 
/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
//void *connection_handler(void *param)
{
    sock_thread* t = (sock_thread*)param;	//PWK, fishy! param is not defined

    //Get the socket descriptor
    int sock = *(int*)socket_desc;
    //int sock = t->socket;
    int tid = t->id;

    int read_size;
    char *message , client_message[2000];
     
    //Send some messages to the client
    message = "Greetings! I am your connection handler\n";
    write(sock , message , strlen(message));
     
    message = "Now type something and i shall repeat what you type \n";
    write(sock , message , strlen(message));
     
    //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ) {
        //end of string marker
		client_message[read_size] = '\0';
	    printf("%d:%s\n", tid, client_message);

		//Send the message back to client
        write(sock , client_message , strlen(client_message));
		
		//clear the message buffer
		memset(client_message, 0, 2000);
    }
     
    if(read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    }
    else if(read_size == -1) {
        perror("recv failed");
    }
    close(sock);
    printf("exit thread\n");
         
    return 0;
} 