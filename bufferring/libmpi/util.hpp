#ifndef _UTIL_HPP_
#define _UTIL_HPP_

#include <cstring>

typedef int hdr_t;

extern int rank;

char *attach_source(char *bytes, int len);
char *detach_source(char *message, int len);
hdr_t get_source(char *message);

#endif /* _UTIL_HPP_ */
