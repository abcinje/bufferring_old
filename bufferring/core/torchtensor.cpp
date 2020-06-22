#include "torchtensor.hpp"

TorchTensor::TorchTensor(torch::Tensor tensor) : tensor_(tensor)
{
}

TorchTensor::TorchTensor(torch::Tensor tensor, void *blob)
{
	std::vector<int64_t> shape;
	for (int i = 0; i < tensor.dim(); i++)
		shape.push_back(tensor.size(i));
	tensor_ = torch::from_blob(blob, shape, tensor.dtype());
}

TorchTensor &TorchTensor::operator+=(const TorchTensor &operand)
{
	tensor_ += operand.tensor_;
	return *this;
}

TorchTensor &TorchTensor::operator/=(int operand)
{
	tensor_ /= operand;
	return *this;
}

void *TorchTensor::data(void) const
{
	return tensor_.data_ptr();
}

int TorchTensor::data_len(void) const
{
	return tensor_.element_size() * tensor_.numel();
}
