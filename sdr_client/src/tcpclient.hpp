#ifndef SRC_TCPSOCKET_HPP_
#define SRC_TCPSOCKET_HPP_

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>



namespace std {


class tcpsocket {
public:
    tcpsocket();

    struct sockaddr_in servaddr;
    int sockfd;
    bool socketwasopenflag;

    void assignipaddr(std::string);
    void assignport(int port);
    void createsocket();
    bool opensocket();

    int receive(char*);
    void closesocket();



    virtual ~tcpsocket();

};

} /* namespace std */

#endif /* SRC_TCPSOCKET_HPP_ */
