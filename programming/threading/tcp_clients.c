#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>


/*
    In order to ensure the messages are sent and received in the correct order, 
    we will have a function to read and send back an acknowledgement the message was received
*/

int recv_message(int socket) {
    int length = 256;
    char buffer[length];
    int response = read(socket,buffer,length);
    if (response <= 0) {
        printf("Failed to receive message\n");
        return 0;
    }
    printf("Message from server: %s\n",buffer);
    response = write(socket,"ok",2);
    if (response <= 0) {
        printf("Failed to send acknowledgement\n");
        return 0;
    }
    return 1;
}

/*
    We utilize the fact that the server sends back the same message received, as an indication the message was received
    0 on failure, 1 on success
*/

int send_message(int socket, char* message) {
    int length = 256;
    char buffer[length];
    int response = write(socket, message, strlen(message));
    if (response <= 0) {
        printf("Failed to send message\n");
        return 0;
    }
    response = read(socket, buffer, length);
    if (response <= 0) {
        printf("Failed to receive acknowledgement\n");
        return 0;
    }
    buffer[response] = '\0';
    printf("Message from server: %s\n",buffer);
    return 1;
}

int main()
{
    int socket_desc, val;
    struct sockaddr_in client_addr;
    char buffer[256];
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    printf("Enter the port number\n");
    int port;
    scanf("%d", &port);

    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr =  INADDR_ANY; 
    client_addr.sin_port = htons(port);

    if(connect(socket_desc, (struct sockaddr*)&client_addr, sizeof(client_addr)) == 0)
        printf("CONNECT STATE: Connected to Server on port %d\n", port);
    else
        printf("Connection to server failed !\n");

    //expecting first message from server
    if (recv_message(socket_desc) == 0) {
        close(socket_desc);
        return 1;
    }

    //expecting second message from server telling us to send a message over
    if (recv_message(socket_desc) == 0) {
        close(socket_desc);
        return 1;
    }
    while(1) {
        
        printf("Message to server: ");
        bzero(buffer,256);
        scanf("%s", buffer);
        
        if (strcmp(buffer, "exit") == 0 || strcmp(buffer, "quit") == 0) {
            printf("Exiting...\n");
            break;
        }
        if (send_message(socket_desc, buffer) == 0) {
            close(socket_desc);
            return 1;
        }
        bzero(buffer,256);        
    }
	close(socket_desc);
	return 0;	
}