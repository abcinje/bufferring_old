#include <mpi.h>

#include "comm.hpp"

extern MPI_Comm *comm;
extern int size, rank;

void Sender::send_routine(void)
{
	while (true) {
		Message *message;
		q->wait_and_pop(message);
		MPI_Send(message->blob(), message->len(), MPI_BYTE, (rank+1)%size, message->mpitag(), *comm);
		delete message;
	}
}

Sender::Sender(void)
{
	q = new Queue<Message *>;
	thr = new std::thread(&Sender::send_routine, this);
}

Sender::~Sender(void)
{
	thr->join();
	delete thr;
	delete q;
}

void Sender::put(Message *message)
{
	q->push(message);
}

void Receiver::recv_routine(void)
{
	while (true) {
		int source = (rank+size-1)%size;
		int msg_size;
		MPI_Status status;

		MPI_Probe(source, MPI_ANY_TAG, *comm, &status);
		MPI_Get_count(&status, MPI_BYTE, &msg_size);

		Message *message = new Message(msg_size, status.MPI_TAG);
		MPI_Recv(message->blob(), msg_size, MPI_BYTE, source, MPI_ANY_TAG, *comm, MPI_STATUS_IGNORE);
		q[message->nametag()].push(message);

		if (message->source() != (rank+1)%size) {
			Message *forward = new Message(*message);
			sender->put(forward);
		}
	}
}

Receiver::Receiver(Sender *the_sender, int names_len) : sender(the_sender)
{
	q = new Queue<Message *>[names_len];
	thr = new std::thread(&Receiver::recv_routine, this);
}

Receiver::~Receiver(void)
{
	thr->join();
	delete thr;
	delete []q;
}

bool Receiver::get_nowait(Message *&message, int nametag)
{
	return q[nametag].try_pop(message);
}
