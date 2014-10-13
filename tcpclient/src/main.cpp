//#include <strings.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/types.h>
//#include <netinet/in.h>



#include "tcpsocket.hpp"

using namespace std;




int main(int argc, char**argv) {

	printf("test");

tcpsocket* rtlsocket = new tcpsocket;
rtlsocket->assignipaddr("127.0.0.1");
rtlsocket->assignport(1234);
rtlsocket->createsocket();
rtlsocket->opensocket();

uint32_t command = 0x02001234;






rtlsocket->senduint32(command);











	/*
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

	strcpy(sendline, "Particia 2 Morrow");
	unsigned int x;
	for (x = 0; x < sizeof(sendline); x++) {
		if (sendline[x] == '\0') {
			break;
		}
	}
//http://stackoverflow.com/questions/11702673/send-hex-values-through-udp-socket

	send(sockfd, (char*)&number, sizeof(number), 0);

	//	send(sockfd, sendline, x * sizeof(char), 0);


	sleep(10);
	printf("program exiting\n");

	*/

return 0;
}
