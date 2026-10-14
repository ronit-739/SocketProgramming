
#include <stdio.h>
#include <arpa/inet.h>



int main()
{
char *address="255.255.255.255";
struct sockaddr_in  inaddress;

// we will use some function to conver ip tp hexadecimal form

if(!inet_aton(address, &inaddress.sin_addr))
{
// aton stands for address to network
perror("conversion");
return -1;
}
 
printf("ip address is: %s\n", address);
printf("its equivalent hex is:%#x\n",inaddress.sin_addr.s_addr);


return 0;
}
 
