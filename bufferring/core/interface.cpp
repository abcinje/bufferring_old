#include <cstdlib>
#include <iostream>

#include <mpi.h>
#include <torch/extension.h>

#include "comm.hpp"
#include "message.hpp"
#include "ntable.hpp"
#include "ptable.hpp"
#include "torchtensor.hpp"

MPI_Comm *comm;
int size, rank;

NameTable *ntable;
ProgressTable *ptable;
Sender *sender;
Receiver *receiver;

int threshold;

void init(uint64_t mpi_comm, const std::vector<std::string> &names, int thresh)
{
	comm = reinterpret_cast<MPI_Comm *>(mpi_comm);
	MPI_Comm_size(*comm, &size);
	MPI_Comm_rank(*comm, &rank);

	int names_len = names.size();

	ntable = new NameTable(names);
	ptable = new ProgressTable(size, rank, names_len);
	sender = new Sender;
	receiver = new Receiver(sender, names_len);

	threshold = thresh;
}

void deinit(void)
{
	delete receiver;
	delete sender;
	delete ptable;
	delete ntable;
}

bool process(torch::Tensor &t, std::string name)
{
	TorchTensor tensor(t);

	int nametag = ntable->find(name);
	if (nametag < 0) {
		std::cerr << "The name " << name << " does not exist in the name table" << std::endl;
		exit(1);
	}
	
	/* Put */
	ptable->update(rank, nametag);
	Message *send_msg = new Message(tensor, rank, nametag);
	sender->put(send_msg);

	/* Get & Update */
	int count = 0;
	while (true) {
		Message *recv_msg;
		if (receiver->get_nowait(recv_msg, nametag)) {
			TorchTensor recv_tensor(t, recv_msg->blob());
			tensor += recv_tensor;
			count++;
			ptable->update(recv_msg->source(), nametag);
			delete recv_msg;
		}
		else if (!ptable->blocked(nametag, threshold))
			break;
	}
	if (count > 0) {
		tensor /= (count + 1);
		return true;
	}
	return false;
}

PYBIND11_MODULE(TORCH_EXTENSION_NAME, m)
{
	m.def("init", &init);
	m.def("deinit", &deinit);
	m.def("process", &process);
}
