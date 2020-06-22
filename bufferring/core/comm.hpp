#ifndef _COMM_HPP_
#define _COMM_HPP_

#include <thread>

#include "message.hpp"
#include "queue.hpp"

class Sender {
private:
	Queue<Message *> *q;
	std::thread *thr;

	void send_routine(void);

public:
	Sender(void);
	~Sender(void);

	void put(Message *message);
};

class Receiver {
private:
	Queue<Message *> *q;
	std::thread *thr;
	Sender *sender;

	void recv_routine(void);

public:
	Receiver(Sender *the_sender, int names_len);
	~Receiver(void);

	bool get_nowait(Message *&message, int nametag);
};

#endif /* _COMM_HPP_ */
