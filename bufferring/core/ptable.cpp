#include "ptable.hpp"

ProgressTable::ProgressTable(int size, int rank, int names_len) : size_(size), rank_(rank), names_len_(names_len)
{
	table = new int *[names_len];
	for (int i = 0; i < names_len; i++)
		table[i] = new int[size]();
}

ProgressTable::~ProgressTable(void)
{
	for (int i = 0; i < names_len_; i++)
		delete []table[i];
	delete []table;
}

void ProgressTable::update(int node, int nametag)
{
	table[nametag][node]++;
}

bool ProgressTable::blocked(int nametag, int thresh)
{
	int max, min;
	max = min = table[nametag][0];

	for (int i = 1; i < size_; i++) {
		if (max < table[nametag][i])
			max = table[nametag][i];
		if (min > table[nametag][i])
			min = table[nametag][i];
	}

	if (thresh > max - min)
		return false;
	else if (table[nametag][rank_] == min)
		return false;
	else
		return true;
}
