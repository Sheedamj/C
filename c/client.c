#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<stdio.h>
#define MAX_HOSTNAME 255
void error(char *msg)
{
perror(msg);
exit(0);
}
int main(int argc, char *argv[])
{
int sock, n, ret;
socklen_t length, length2;
struct sockaddr_in server;
struct sockaddr_in from;
struct hostent *hp;
char buffer[1024], hostbuffer[MAX_HOSTNAME +1];
sock=socket(AF_INET, SOCK_DGRAM, 0);
if(sock<0)
{
error("socket");
}
server.sin_family=AF_INET;
hp=gethostbyname("localhost");
if(hp==0)
{
error("unknown host");
}
bcopy((char *)hp->h_addr,(char *)&server.sin_addr,hp->h_length);
server.sin_port=htons(1030);
length=sizeof(server);
length2=sizeof(from);
//gethostname function
ret=gethostname(hostbuffer,MAX_HOSTNAME);
if(ret==0)
{
printf("host name is %s\n", hostbuffer);
}
//end of gethostname
//getsockname function
ret=getsockname(sock,(struct sockaddr_in *)&from, &length2);
if(ret==0)
{
printf("local address:%s\n", inet_ntoa(from.sin_addr));
printf("local port: %d\n", from.sin_port);
}//end of getsockname
printf("please enter the mesage:");
bzero(buffer,1024);
fgets(buffer,1023,stdin);
n=sendto(sock,buffer,strlen(buffer),0,&server,length);
if(n<0)
{
error("sendto");
}
n=recvfrom(sock,buffer,1024,0,&from,&length);
if(n<0)
{
error("recvfrom");
}
//getpeername function
ret=getpeername(sock,(struct sockaddr_in *)&server,&length);
if(ret==0)
{
printf("peer address: %s\n", inet_ntoa(server.sin_addr));
printf("peer port: %d\n", server.sin_port);
}
//end getpeername
//gethostbyname function
hp=gethostbyname("localhost");
if(hp)
printf("h_name: %s", hp->h_name);
printf("\n");
printf("h_addrtype:%d", hp->h_addrtype);
printf("\n");
printf("address:");
int i=0;
while(1)
{
if(hp->h_addr_list[i])
{
struct in_addr theAddr;
memcpy(&theAddr.s_addr,hp->h_addr_list[i],sizeof(theAddr.s_addr));
printf("h_addr_list[%d}=%s\n",i, inet_ntoa(theAddr));
i++;
}
else
break;
}
//end gethostbyname
//gethostbyaddr function
struct in_addr xy;
struct hostent *yx;
inet_aton("127.0.0.1",&xy);
if(yx=gethostbyaddr((char*)&xy.s_addr,sizeof(xy.s_addr),AF_INET))
printf("host name is %s\n", yx->h_name);
//end of gethostbyaddr
//getservbyname function
struct servent *sp;
sp=getservbyname("http","tcp");
if(sp)
printf("(By Name)Service %s is at port %d\n", sp->s_name,ntohs(sp->s_port));
//end getservname
//getservbyport function
struct servent *sd;
sd=getservbyport(htons(80),NULL);
if(sd)
printf("(By Port)Service %s is at port %d\n", sd->s_name, ntohs(sd->s_port));
//end of getservbyport
write(1,"\nConverted:",16);
write(1,buffer,n);
write(1,"\n",1);
}
