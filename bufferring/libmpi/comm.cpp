#include "comm.hpp"
#include "util.hpp"

void Receiver::recv_routine(void)
{
	while (true);
}

Receiver::Receiver(const char **names, int names_len)
{
	m = new map<string, Queue<char *> *>;
	for (int i = 0; i < names_len; i++) {
		string name = names[i];
		m->insert(make_pair(name, new Queue<char *>));
	}

	thr = new thread(recv_routine);
}

Receiver::~Receiver(void)
{
	thr->join();
	delete thr;

	map<string, Queue<char *> *>::iterator it;
	for (it = m->begin(); it != m->end(); it++)
		delete it->second;
	delete m;
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
