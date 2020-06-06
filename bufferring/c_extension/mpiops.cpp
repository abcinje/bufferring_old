#pragma once

#include <torch/extension.h> 
#include <stdio.h>
#include <mpi.h>

int rank;
int size;

bool mpi_init(void)
{
	MPI_Init(NULL,NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_rank(MPI_COMM_WORLD, &size);
	return true;
}


