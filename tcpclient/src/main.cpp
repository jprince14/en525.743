//#include <strings.h>
//#include <unistd.h>
//#include <netdb.h>
//#include <sys/types.h>
//#include <netinet/in.h>



#include "tcpsocket.hpp"

using namespace std;


//GNU Radio code for interacting with the SDR
//http://git.osmocom.org/gr-osmosdr/tree/lib/rtl_tcp

int main(int argc, char**argv) {

	printf("test");

tcpsocket* rtlsocket = new tcpsocket;
rtlsocket->assignipaddr("127.0.0.1");
rtlsocket->assignport(1234);
rtlsocket->createsocket();
rtlsocket->opensocket();

rtlsocket->set_freq(1234);


return 0;
}
