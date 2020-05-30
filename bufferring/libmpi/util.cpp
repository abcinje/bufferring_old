#include "util.hpp"

char *attach_source(char *bytes, int len)
{
	char *message = new char[sizeof(hdr_t) + len];
	*((hdr_t *)message) = rank;
	memcpy(message + sizeof(hdr_t), bytes, len);

	return message;
}

char *detach_source(char *message, int len)
{
	char *bytes = new char[len - sizeof(hdr_t)];
	memcpy(bytes, message + sizeof(hdr_t), len - sizeof(hdr_t));

	return bytes;
}

hdr_t get_source(char *message)
{
	return *((hdr_t *)message);
}
