#ifndef _COMM_HPP_
#define _COMM_HPP_

#include <thread>

using std::thread;

class Receiver {
private:
	thread *thr;

	static void recv_routine(void);

public:
	Receiver(void);
	~Receiver(void);
};

class Sender {
private:
	thread *thr;

	static void send_routine(void);

public:
	Sender(void);
	~Sender(void);
};

#endif /* _COMM_HPP_ */
