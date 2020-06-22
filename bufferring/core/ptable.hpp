#ifndef _PTABLE_HPP_
#define _PTABLE_HPP_

class ProgressTable {
private:
	int **table;
	int size_, rank_, names_len_;

public:
	ProgressTable(int size, int rank, int names_len);
	~ProgressTable(void);

	void update(int node, int nametag);
	bool blocked(int nametag, int thresh);
};

#endif /* _PTABLE_HPP_ */
