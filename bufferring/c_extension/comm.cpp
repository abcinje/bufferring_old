#include "comm.hpp"

int rank, size;

bool mpi_init(void)
{
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(mMPI_COMM_WORLD, &size);
	return true;
}

void mpi_hello_world(void)
{
	printf("hello world rank %d of size %d\n", rank, size);
}
