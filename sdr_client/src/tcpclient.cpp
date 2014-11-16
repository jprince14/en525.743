#include "tcpclient.hpp"

namespace std {

tcpsocket::tcpsocket() {
    // TODO Auto-generated constructor stub
    sockfd = 0;
    bzero(&servaddr, sizeof(servaddr));

}

void tcpsocket::assignipaddr(std::string ipaddr) {
    servaddr.sin_addr.s_addr = inet_addr(ipaddr.c_str());

}

void tcpsocket::assignport(int port) {
    servaddr.sin_port = htons(port);
}

void tcpsocket::createsocket() {

    servaddr.sin_family = AF_INET;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
}

void tcpsocket::closesocket() {
    close(sockfd);

}

bool tcpsocket::opensocket() {
    bool returnFlag = false;
    if (connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr)) == 0) {
        //Success opening socket
        returnFlag = true;
    }
    return returnFlag;

}


int tcpsocket::receive(char* passedinbuffer) {


    return 0;
}



tcpsocket::~tcpsocket() {
// TODO Auto-generated destructor stub

}

} /* namespace std */
