#define MPICH_SKIP_MPICXX 1
#define OMPI_SKIP_MPICXX  1

#include <mpi.h>

#ifdef __cplusplus
extern "C" {
#endif
void init(MPI_Comm comm);
#ifdef __cplusplus
}
#endif

int size, rank;

void init(MPI_Comm comm)
{
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
}
