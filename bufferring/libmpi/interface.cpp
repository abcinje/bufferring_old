#define MPICH_SKIP_MPICXX 1
#define OMPI_SKIP_MPICXX  1

#include <mpi.h>

#include "comm.hpp"
#include "util.hpp"

#ifdef __cplusplus
extern "C" {
#endif
void init(MPI_Comm comm, const char **names, int names_len);
void deinit(void);

void put(char *name, char *bytes, int len);
bool get_nowait_fetch(char *name);
int get_nowait_len(void); 
void *get_nowait_data(void);
void get_nowait_free(void);
#ifdef __cplusplus
}
#endif

MPI_Comm comm;
int size, rank;

NameTable *ntable;
Sender *sender;
Receiver *receiver;

#include <stdio.h>
void init(MPI_Comm mpi_comm, const char **names, int names_len)
{
	comm = mpi_comm;
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

	ntable = new NameTable(names, names_len);
	sender = new Sender;
	receiver = new Receiver(ntable, sender);
}

void deinit(void)
{
	delete sender;
	delete receiver;
	delete ntable;
}

void put(char *name, char *bytes, int len)
{
	string strname = name;
	int nametag = ntable->find(strname);
	char *message = attach_header(bytes, len, nametag);
	QEntry qentry(message, len);
	sender->put(qentry);
}

static QEntry qentry;

bool get_nowait_fetch(char *name)
{
	string strname = name;
	int nametag = ntable->find(strname);
	return receiver->get_nowait(qentry, nametag);
}

int get_nowait_len(void)
{
	return qentry.len;
}

void *get_nowait_data(void)
{
	return (void *)qentry.data;
}

void get_nowait_free(void)
{
	delete qentry.data;
}
