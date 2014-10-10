//#include <strings.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/types.h>
//#include <netinet/in.h>

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>

int main(int argc, char**argv)
{
   int sockfd,n;
   struct sockaddr_in servaddr;
   char sendline[1000];
   char recvline[1000];

   std::string serveraddr = "127.0.0.1";

   sockfd=socket(AF_INET,SOCK_STREAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=inet_addr(serveraddr.c_str());
   servaddr.sin_port=htons(32000);

   connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

//   while (fgets(sendline, 10000,stdin) != NULL)
//   {
//      sendto(sockfd,sendline,strlen(sendline),0,
//             (struct sockaddr *)&servaddr,sizeof(clientaddr.c_str()));
//      n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
//      recvline[n]=0;
//      fputs(recvline,stdout);
//   }
}
