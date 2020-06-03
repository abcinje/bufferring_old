#include "comm.hpp"
#include "util.hpp"

extern MPI_Comm comm;
extern int size, rank;

QEntry::QEntry(void) : QEntry(NULL, 0)
{
}

QEntry::QEntry(char *databuf, int length) : data(databuf), len(length)
{
}

void Sender::send_routine(void)
{
	while (true) {
		QEntry qentry(NULL, 0);
		q->wait_and_pop(qentry);
		MPI_Send(qentry.data, qentry.len, MPI_BYTE, (rank+1)%size, 0, comm);
		delete qentry.data;
	}
}

Sender::Sender(void)
{
	q = new Queue<QEntry>;
	thr = new thread(&Sender::send_routine, this);
}

Sender::~Sender(void)
{
	thr->join();
	delete thr;
	delete q;
}

void Sender::put(QEntry &qentry)
{
	q->push(qentry);
}

void Receiver::recv_routine(void)
{
	while (true) {
		int source = (rank+size-1)%size;
		int msg_size;
		MPI_Status status;

		MPI_Probe(source, 0, comm, &status);
		MPI_Get_count(&status, MPI_BYTE, &msg_size);

		char *message = new char[msg_size];
		MPI_Recv(message, msg_size, MPI_BYTE, source, 0, comm, MPI_STATUS_IGNORE);

		int msg_src, msg_name, bytes_size = msg_size;
		char *bytes = detach_header(message, bytes_size, msg_src, msg_name);
		QEntry rqentry(bytes, bytes_size);
		q[msg_name].push(rqentry);

		if (msg_src != (rank+1)%size) {
			QEntry sqentry(message, msg_size);
			sender->put(sqentry);
		}
		else
			delete message;
	}
}

Receiver::Receiver(NameTable *nametable, Sender *the_sender) : ntable(nametable), sender(the_sender)
{
	q = new Queue<QEntry>[nametable->size()];
	thr = new thread(&Receiver::recv_routine, this);
}

Receiver::~Receiver(void)
{
	thr->join();
	delete thr;
	delete q;
}

bool Receiver::get_nowait(QEntry &qentry, int nametag)
{
	return q[nametag].try_pop(qentry);
}
