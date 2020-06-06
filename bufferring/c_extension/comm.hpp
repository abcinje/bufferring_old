#pragma once

#include <torch/extension.h>
#include <mpi.h>
#include <iostream>

bool mpi_init(void);
void mpi_hello_world(void);
