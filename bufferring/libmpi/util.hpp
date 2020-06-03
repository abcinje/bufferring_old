#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <cstring>

typedef int hdr_t;

extern int rank;

char *attach_header(char *bytes, int &len, hdr_t name);
char *detach_header(char *message, int &len, hdr_t &src, hdr_t &name);

#endif /* _UTIL_HPP_ */
