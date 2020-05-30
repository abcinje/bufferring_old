#include "comm.hpp"

void Receiver::recv_routine(void)
{
	while (true);
}

Receiver::Receiver(void)
{
	thr = new thread(recv_routine);
}

Receiver::~Receiver(void)
{
	thr->join();
	delete thr;
}

void Sender::send_routine(void)
{
	while (true);
}

Sender::Sender(void)
{
	thr = new thread(send_routine);
}

Sender::~Sender(void)
{
	thr->join();
	delete thr;
}
