#ifndef SRC_udpSOCKET_HPP_
#define SRC_udpSOCKET_HPP_

#include <errno.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string>
#include <unistd.h>
#include <iostream>
#include <fstream>



namespace std {


class udpsocket {
public:
    udpsocket();

    struct sockaddr_in servaddr;
    int sockfd;

    void assignipaddr(std::string);
    void assignport(int port);
    void createsocket();
    bool opensocket();

    int receive(char*);
    void closesocket();



    virtual ~udpsocket();

};

} /* namespace std */

#endif /* SRC_udpSOCKET_HPP_ */
