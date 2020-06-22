#ifndef _NTABLE_HPP_
#define _NTABLE_HPP_

#include <map>
#include <string>
#include <vector>

class NameTable {
private:
	std::map<std::string, int> table;

public:
	NameTable(const std::vector<std::string> &names);

	int size(void);
	int find(const std::string &name);
};

#endif /* _NTABLE_HPP_ */
