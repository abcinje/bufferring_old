#ifndef _COMM_HPP_
#define _COMM_HPP_

#include <map>
#include <thread>

#include "queue.hpp"

using std::map;
using std::string;
using std::thread;

class Receiver {
private:
	map<string, Queue<char *> *> *m;
	thread *thr;

	static void recv_routine(void);

public:
	Receiver(const char **names, int names_len);
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
