#ifndef _MESSAGE_HPP_
#define _MESSAGE_HPP_

#include "torchtensor.hpp"

class Message {
private:
	char *blob_;
	int len_;
	int mpitag_;

public:
	Message(const Message &copy);
	Message(int len, int mpitag);
	Message(const TorchTensor &tensor, int source, int nametag);
	~Message(void);

	char *blob(void) const;
	int len(void) const;
	int mpitag(void) const;
	int source(void) const;
	int nametag(void) const;
};

#endif /* _MESSAGE_HPP_ */
