#include <cstring>

#include "message.hpp"

Message::Message(const Message &copy) : len_(copy.len_), mpitag_(copy.mpitag_)
{
	blob_ = new char[len_];
	memcpy(blob_, copy.blob_, len_);
}

Message::Message(int len, int mpitag) : len_(len), mpitag_(mpitag)
{
	blob_ = new char[len];
}

Message::Message(const TorchTensor &tensor, int source, int nametag)
{
	len_ = tensor.data_len();
	blob_ = new char[len_];
	memcpy(blob_, tensor.data(), len_);

	mpitag_ = ((source & 0xffff) << 16) | (nametag & 0xffff);
}
	
Message::~Message(void)
{
	delete []blob_;
}

char *Message::blob(void) const
{
	return blob_;
}

int Message::len(void) const
{
	return len_;
}

int Message::mpitag(void) const
{
	return mpitag_;
}

int Message::source(void) const
{
	return (int)((mpitag_ >> 16) & 0xffff);
}

int Message::nametag(void) const
{
	return (int)(mpitag_ & 0xffff);
}
