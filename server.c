
#include <stdio.h>
#include <sys/socket.h> 
#include <netinet/in.h>
#include <unistd.h>

  
int main()
{
	char message[255]="hello this is the message sent from server side . i can send  a whole page";
	
	// now i need to make socket
	// int socket(int domain , int type, int protocol)
	//  i will use ipv4 for that domain is AF_INET
	// it is int value that means there is certain some string associated with it
	// domain can have SOCK_STREAM(reliable), SOCK_DGRAM(unreliable)
	// protocol 0 means system decide itself(TCP)
	
	int file_descriptor=socket(AF_INET, SOCK_STREAM,0);
	// this value is passed down to further calls like bind (), connect()
	// -1 for failure
	 
	 if(file_descriptor==-1)
	 {
		 perror("error"); 
		 close(file_descriptor);
		 return -1;
		 // perror takes current value of error , maps to human readable form and print stderr in form <s>: <error message>\n
	 }
	 
	 
	 /* now we need to define some address variable for that we use structure
	  we are not going define own structure , but use structure from <netinet/in.h>
	 struct have its
	 #family
	 # port no.
	 # address unsigned 32 bit => 4 billion
	 #padding
	 
	*/
	
	struct sockaddr_in  server_address;
// i have created address variable of sockaddr_in typede

server_address.sin_family=AF_INET ;   // this is family declaration , no need for memorization just see the structure type
server_address.sin_port=htons(8080);  //uint16_t hostshort — a 16-bit value in host byte order->	The same value converted to network byte order (big-endian)
//host to network
//It converts byte order — it rearranges the bytes of a number so they go in the order the network expects (big-endian). That's all it does. No math, no value change, just a byte swap.
// eg 0x 0050 is stored as 0x 50 00 then it is converted to 0x 0050 and sent

	
server_address.sin_addr.s_addr=htonl(INADDR_ANY);
//htonl does same work as htnos but for 32 bit i.e addresses rather than 16 bit port no
//INADD_ANY is simply 0.0.0.0 (look for all interfaces)



// now its time for binding address and port to socket
//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

if(bind(file_descriptor, (const struct sockaddr *)&server_address, sizeof(server_address)))
{
	perror("bind");
	close(file_descriptor);
	return -1;	
}
	
/*  Type mismatch
bind(sockfd, &servaddr, sizeof(servaddr));
         ^^^^^^^^^^  type is struct sockaddr_in *          expected:    const struct sockaddr *  

socketaddr_in is a type(ipv4) of socketaddr)
*/	 


/*now its time for listening()
int listen(int sockfd, int backlog);
he maximum number of pending connections the kernel should queue.
If the queue is full, clients may receive an error or the connection may be ignored until space opens up
it act as buffer before accept()
*/
listen(file_descriptor, 5);

int client_socket=accept(file_descriptor,NULL,NULL);
// returns a file descriptor or say socket obj for client 
//donot use prev descriptor

send(client_socket, message, sizeof(message), 0);
// 0  is flag here
close(file_descriptor);
return 0;
}

