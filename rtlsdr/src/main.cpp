//#include <strings.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/types.h>
//#include <netinet/in.h>

//#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
//#include <time.h>
#include <string>
#include <unistd.h>

//#include <sys/types.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <netdb.h>
//#include <signal.h>
//#include <time.h>
//#include <cstdlib>

using namespace std;

int main(int argc, char**argv) {
	int sockfd, n;
	struct sockaddr_in servaddr;
	char sendline[1000];
	char recvline[1000];

	std::string serveraddr = "127.0.0.1";

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr(serveraddr.c_str());
	servaddr.sin_port = htons(1234);

	connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

//	int test = 0x0123;

//   std::string test = "this is a test";
	strcpy(sendline, "\tPatricia 2 Morrow\n");
	unsigned int x;
	for (x = 0; x < sizeof(sendline); x++) {
		if (sendline[x] == '\0') {
			break;
		}
	}


	int no = 0x0123456;

	char c[20];
	sprintf(c, "%x", no);


	uint32_t test = 0x012345;

//	itos();

//	char sample[10] = reinterpret_cast<char*>(test);
//sample = reinterpret_cast<char*>(test);

//http://stackoverflow.com/questions/11702673/send-hex-values-through-udp-socket
	send(sockfd, c , 20, 0);


//	send(sockfd, sendline, x * sizeof(char), 0);

//	   std::string test2 = std::to_string(x);

//	   nc -l 127.0.0.1 1234 -v -k

	   //


	/* while (fgets(sendline, 10000,stdin) != NULL)
	 {


	 sendto(sockfd,sendline,strlen(sendline),0,
	 (struct sockaddr *)&servaddr,sizeof(clientaddr.c_str()));
	 n=recvfrom(sockfd,recvline,10000,0,NULL,NULL);
	 recvline[n]=0;
	 fputs(recvline,stdout);
	 }*/

	sleep(10);
	printf("program exiting\n");
}
