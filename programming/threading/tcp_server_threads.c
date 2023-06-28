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
    pthread_t id;
    int socket;
} sock_thread;

int message_length = 2000;
int default_port = 8888;
int send_message(int sock, char* message);
int recieve_message(int sock, char* message, int message_length);
//the thread function
void *connection_handler(void *);
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c;
    struct sockaddr_in server , client;
    //allow port to be passed as first argument, if none is passed, use 8888
    int port = argc > 1 ? atoi(argv[1]) : default_port;
     
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
    server.sin_port = htons( port );
     
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
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
	
    struct st th;
    th.id = 0;
    th.socket = 0;

    while( (client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c)) ) {
        th.socket = client_sock;
        if( pthread_create( &th.id , NULL ,  connection_handler , &th) < 0)
        {
            perror("could not create thread");
            close(client_sock);
            return 1;
        }
        printf("Connection accepted, Thread-ID=#[%ld]\n", th.id);
        puts("Handler assigned");

    }

    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }
    return 0;
}
 
 //On sending a message, the server expects a response of "ok" from the client
 //Before concluding the message was sent correctly
 //Return 0 on failure, 1 on success
 int send_message(int sock, char* message) {

    int response = write(sock, message, strlen(message));
    if (response <= 0) {
        printf("Failed to send message\n\n");
        return 0;
    }
    char buffer[message_length];
    response = recv(sock, buffer, message_length, 0);
    if (strcmp(buffer, "ok") != 0) {
        printf("Failed to receive acknowledgement, received %s\n", message);
        return 0;
    }
    return 1;
 }

//On recieving a message, the server returns the message received back to the client
//As acknowledgement the message was received
//Return the size of the message received, otherwise 0 for failure
int recieve_message(int sock, char* message, int message_length) {
    int read_size = recv(sock, message, message_length, 0);
    if (read_size <= 0) {
        printf("Failed to receive message\n");
        return 0;
    }	
    int response = write(sock , message , strlen(message));
    if (response <= 0) {
        printf("Failed to send acknowledgement\n");
        return 0;
    }
    return read_size;
}
/*
 * This will handle connection for each client
 * */
void *connection_handler(void *socket_desc)
{
    sock_thread* t = (sock_thread*)socket_desc;

    //Get the socket descriptor
    int sock = t->socket;
    pthread_t tid = t->id;

    int read_size;
    char *message , client_message[2000];
     
    //Send some messages to the client
    message = "Greetings! I am your connection handler\n";
    if (send_message (sock, message) == 0) {
        close(sock);
        return 0;
    }

    message = "Now type something and i shall repeat what you type \n";
    if (send_message (sock, message) == 0) {
        close(sock);
        return 0;
    }
     
    //Receive a message from client
    while( (read_size = recieve_message(sock, client_message, message_length)) > 0) {
        //end of string marker
		client_message[read_size] = '\0';
	    printf("Message from client, Thread-ID=#[%ld]:%s\n", tid, client_message);
		
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