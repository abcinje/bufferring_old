#include "ntable.hpp"

NameTable::NameTable(const std::vector<std::string> &names)
{
	int i = 0;
	for (auto &name : names)
		table.insert(make_pair(name, i++));
}

int NameTable::size(void)
{
	return table.size();
}

int NameTable::find(const std::string &name)
{
	auto it = table.find(name);
	if (it != table.end())
		return it->second;
	return -1;
}
