#ifndef _COMM_HPP_
#define _COMM_HPP_

#include <mpi.h>
#include <thread>

#include "ntable.hpp"
#include "queue.hpp"

using std::thread;

class QEntry {
public:
	char *data;
	int len;

	QEntry(void);
	QEntry(char *databuf, int length);
};

class Sender {
private:
	Queue<QEntry> *q;
	thread *thr;

	void send_routine(void);

public:
	Sender(void);
	~Sender(void);

	void put(QEntry &qentry);
};

class Receiver {
private:
	NameTable *ntable;
	Queue<QEntry> *q;
	thread *thr;
	Sender *sender;

	void recv_routine(void);

public:
	Receiver(NameTable *nametable, Sender *the_sender);
	~Receiver(void);

	bool get_nowait(QEntry &qentry, int nametag);
};

#endif /* _COMM_HPP_ */
