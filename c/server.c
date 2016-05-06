#include<stdio.h>
#include<netdb.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#define MAX_HOSTNAME 255
void error(char *msg)
{
perror(msg);
exit(0);
}
int main(int argc, char *argv[])
{
int ret, buffylen, sock, n;
socklen_t length, fromlen;
struct sockaddr_in server;
struct sockaddr_in from;
char buf[1024], buffy[1024], name[10]="message:";
char hostbuffer[MAX_HOSTNAME+1];
sock=socket(AF_INET, SOCK_DGRAM, 0);
if(sock<0)
{
error("opening socket");
}
strcpy(hostbuffer, "Sheeda");
//sethostname function
ret=sethostname(hostbuffer, strlen(hostbuffer));
if(ret==0){
printf("host name: %s\n",hostbuffer);
}
//end of sethostname
length=sizeof(server);
bzero(&server, length);
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(1030);
if(bind(sock,(struct sockaddr *)&server,length)<0)
{
error("binding");
}
fromlen=sizeof(struct sockaddr_in);
//getsockname function
ret=getsockname(sock,(struct sockaddr_in *)&server, &length);
if(ret==0)
{
printf("local address:%s\n", inet_ntop(server.sin_addr));
printf("local address:%d\n", server.sin_port);
}
//end of get sockname
//while(1)
//{
n=recvfrom(sock,buf,1024,0,(struct sockaddr *)&from, &fromlen);
if(n<0)
{
error("recvfrom");
}
//getpeername function
ret= getpeername(sock,(struct sockaddr *)&from,&fromlen);
if(ret==0)
{
printf("peer address: %s\n", inet_ntop(from.sin_addr));
printf("peer port: %d\n", from.sin_port);
}
//end of getpeername
write(1,name,strlen(name));
for(int i=0;i<n;i++)
	buffy[i]=toupper(buf[i]);
write(1,buf,n);
write(1,"\n",1);
n=sendto(sock,buffy,strlen(buffy),0,&from,fromlen);
if(n<0)
{
error("sendto");
}
//}
}

