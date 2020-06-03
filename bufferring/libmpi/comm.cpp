#include "comm.hpp"
#include "util.hpp"

void Receiver::recv_routine(void)
{
	while (true);
}

Receiver::Receiver(NameTable *nametable) : ntable(nametable)
{
	q = new Queue<char *>[nametable->size()];
	thr = new thread(recv_routine);
}

Receiver::~Receiver(void)
{
	thr->join();
	delete thr;
	delete q;
}

void Sender::send_routine(void)
{
	while (true);
}

Sender::Sender(void)
{
	q = new Queue<char *>;
	thr = new thread(send_routine);
}

Sender::~Sender(void)
{
	thr->join();
	delete thr;
	delete q;
}
