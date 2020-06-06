#pragma once 

#include <torch/extension.h>
#include <vector>

//#include "queue.hpp"

void hello(void)
{
	printf("hello world\n");
}

torch::Tensor c2p_tensor(torch::Tensor z)
{
	return z + 1;
}
	
PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  m.def("hello_world", &hello, "hello");
  m.def("c2p_tensor", &c2p_tensor, "c2p");
}
