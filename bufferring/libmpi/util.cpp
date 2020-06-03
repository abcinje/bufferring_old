#include "util.hpp"

char *attach_header(char *bytes, int &len, hdr_t nametag)
{
	char *message = new char[(2 * sizeof(hdr_t)) + len];
	*((hdr_t *)message) = rank;
	*(((hdr_t *)message) + 1) = nametag;
	memcpy(message + (2 * sizeof(hdr_t)), bytes, len);

	len += 2 * sizeof(hdr_t);
	return message;
}

char *detach_header(char *message, int &len, hdr_t &src, hdr_t &nametag)
{
	src = *((hdr_t *)message);
	nametag = *(((hdr_t *)message) + 1);

	len -= 2 * sizeof(hdr_t);
	char *bytes = new char[len];
	memcpy(bytes, message + (2 * sizeof(hdr_t)), len);

	return bytes;
}
