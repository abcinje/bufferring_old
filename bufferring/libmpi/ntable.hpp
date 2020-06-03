#ifndef _NTABLE_HPP_
#define _NTABLE_HPP_

#include <map>
#include <string>

using std::map;
using std::string;

typedef map<string, int> map_t;

class NameTable {
private:
	map_t table;

public:
	NameTable(const char **names, int names_len);
	
	int size(void);
	int find(string name);
};

#endif /* _NTABLE_HPP_ */
