#define MPICH_SKIP_MPICXX 1
#define OMPI_SKIP_MPICXX  1

#include <mpi.h>

#include "comm.hpp"

#ifdef __cplusplus
extern "C" {
#endif
void init(MPI_Comm comm, const char **names, int names_len);
void deinit(void);
#ifdef __cplusplus
}
#endif

int size, rank;

Receiver *receiver;
Sender *sender;

void init(MPI_Comm comm, const char **names, int names_len)
{
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);

	receiver = new Receiver(names, names_len);
	sender = new Sender();
}

void deinit(void)
{
	delete receiver;
	delete sender;
}
