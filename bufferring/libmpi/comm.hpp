#ifndef _COMM_HPP_
#define _COMM_HPP_

#include <thread>

#include "ntable.hpp"
#include "queue.hpp"

using std::thread;

class Receiver {
private:
	NameTable *ntable;
	Queue<char *> *q;
	thread *thr;

	static void recv_routine(void);

public:
	Receiver(NameTable *nametable);
	~Receiver(void);
};

class Sender {
private:
	Queue<char *> *q;
	thread *thr;

	static void send_routine(void);

public:
	Sender(void);
	~Sender(void);
};

#endif /* _COMM_HPP_ */
