#include "ntable.hpp"

NameTable::NameTable(const char **names, int names_len)
{
	for (int i = 0; i < names_len; i++) {
		string name = names[i];
		table.insert(make_pair(name, i));
	}
}

int NameTable::size(void)
{
	return table.size();
}

int NameTable::find(string name)
{
	map_t::iterator it = table.find(name);
	if (it != table.end())
		return it->second;
	return -1;
}
