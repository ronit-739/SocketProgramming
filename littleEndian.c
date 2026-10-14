
#include <stdio.h>
#include <netinet/in.h>

int main()
{
unsigned short host_port=0x1234;
unsigned long host_address=0x12345678;

unsigned short net_port=htons(host_port);
unsigned long net_address=htonl(host_address);



printf("%x\n",host_port);
printf("%x\n",net_port); 
printf("%lx\n",host_address); 
printf("%lx\n",net_address); 
 




return 0;
}
