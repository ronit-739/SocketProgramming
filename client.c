#include <stdio.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <unistd.h>

int main()
{

   //creating a client socket	
	int fd=socket(AF_INET, SOCK_STREAM,0);
	if(fd==-1)
	{
		perror("error");
		close(fd);
		return -1;
	}
	
	//definig server adress
	
	struct sockaddr_in server_address;
	server_address.sin_family=AF_INET;
	server_address.sin_port=htons(8080);
	server_address.sin_addr.s_addr=htons(INADDR_ANY);
	
	//now its time to connect to server
	int config;
	config=connect(fd, (struct sockaddr* ) &server_address, sizeof(server_address));
	if(config==-1)
	{
		perror("error");
		close(fd);
		return -1;
	}
	
	//receive the message
	
	char message[255];
	recv(fd, message, sizeof(message),0);
	printf("%s\n", message);
	
	close(fd);
	return 0;
}
