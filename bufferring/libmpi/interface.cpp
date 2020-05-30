#define MPICH_SKIP_MPICXX 1
#define OMPI_SKIP_MPICXX  1

#include <mpi.h>

#include "comm.hpp"

#ifdef __cplusplus
extern "C" {
#endif
void init(MPI_Comm comm);
void deinit(void);
#ifdef __cplusplus
}
#endif

int size, rank;

Receiver *receiver;
Sender *sender;

void init(MPI_Comm comm)
{
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

	receiver = new Receiver();
	sender = new Sender();
}

void deinit(void)
{
	delete receiver;
	delete sender;
}
