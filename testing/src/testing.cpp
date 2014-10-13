#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <cstring>
#include <string>
#include <unistd.h>

using namespace std;

int tune(int socket, uint32_t freq){

	send(socket, (char*)&freq, sizeof(freq), 0);




return 0;
}




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

	uint32_t frequency = 10000; //in Hz


	tune(sockfd, frequency);

//	int sendsize;
//	sendsize = snprintf(sendline, sizeof(sendline), "%x", number);


}
