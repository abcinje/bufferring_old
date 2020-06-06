#pragma once 

#include <torch/extension.h>
#include <queue>
#include "queue.hpp"
#include <vector>

void hello(void)
{
	printf("hello world\n");
}



PYBIND11_MODULE(TORCH_EXTENSION_NAME, m) {
  m.def("hello_world", &hello, "hello");
}
