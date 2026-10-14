#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFF_SIZE 1024

void error_handling(char * error);

int main(int argc, char * argv[])
{
	// we are taking port no from user initially
	if(argc!=2)
	{
		printf("usage: %s <port no eg 8080>", argv[0]);
		exit(1);
	}
	
	// make a socket
	int server_sock=socket(AF_INET, SOCK_STREAM, 0);
	
	//checking for error
	if(server_sock==-1)
	{
		error_handling("server Socket Creation Error");
	}
	
	
	// for binding create address
	
	
        struct sockaddr_in server_addr = {0};
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[1]));   // atoi converts ascii to int
	server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	
	if(bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr))==-1)
	{
		error_handling("binding error:");
	}
	
	//listening 
	if(listen(server_sock, 5)==-1) // here 5 means 5 client queue is maintained
	{
		error_handling("listening error");
	}
	
     // accept
	 // we are gonna except sequentially for 5 clients and end the program
	 /*for (int i=0; i<5; i++)
	 {
		 int client_sock=accept(server_sock, NULL, NULL);
		 
		 if(client_sock==-1)
		 {
			 error_handling("client_socket  acceptence error");
		 }
		 else{
			 printf("connected to client %d \n", i+1);
		 }
		 
        char message[BUFF_SIZE];
		int size;
		 while((size=read(client_sock, message, sizeof(message)))>0)
		 {
		 write(client_sock,message, size);
	     }
		 close(client_sock);
	 }*/
	 
	 
	 
	 
	 

int client_no = 0;

while (1)
{
    int client_sock = accept(server_sock, NULL, NULL);

    if (client_sock == -1)
    {
        perror("accept failed");
        continue;
    }

    client_no++;
    printf("Client %d connected\n", client_no);

    char message[BUFF_SIZE];
    ssize_t size;

    while ((size = read(client_sock, message, sizeof(message))) > 0)
    {
        write(client_sock, message, size);
    }

    if (size == 0)
        printf("Client %d disconnected normally\n", client_no);
    else
        perror("read failed");

    close(client_sock);
}
	 
	close (server_sock);
	return 0;
}

void error_handling(char * error)
{
	perror(error);
	exit(1);
}
