#ifndef _TORCHTENSOR_HPP_
#define _TORCHTENSOR_HPP_

#include <torch/extension.h>

class TorchTensor {
private:
	torch::Tensor tensor_;

public:
	TorchTensor(torch::Tensor tensor);
	TorchTensor(torch::Tensor tensor, void *blob);

	TorchTensor &operator+=(const TorchTensor &operand);
	TorchTensor &operator/=(int operand);

	void *data(void) const;
	int data_len(void) const;
};

#endif /* _TORCHTENSOR_HPP_ */
