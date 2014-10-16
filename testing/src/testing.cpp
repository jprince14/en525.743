#include <unistd.h>
#include <thread>
#include <iostream>
//#include <stdio.h>

using namespace std;

void testthread() {
	std::cout << "Thread was run" << std::endl;
}

int main(int argc, char**argv) {
	std::thread thread1;

	if (true) {
		thread1 = std::thread(testthread);
	}
	sleep(1);
	thread1.join();
	return 0;
}
