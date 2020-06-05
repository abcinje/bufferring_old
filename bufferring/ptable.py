class ProgressTable:
    def __init__(self, size, rank, name_list):
        assert size > 0
        assert rank >= 0 and rank < size
        self.__table = [{name: 0 for name in name_list} for _ in range(size)]
        self.__size = size
        self.__rank = rank

    def get_my_cycle(self, name):
        return self.__table[self.__rank][name]

    def update(self, node, name):
        assert node >= 0 and node < self.__size
        self.__table[node][name] += 1

    def blocked(self, name, thresh):
        cycles = [d[name] for d in self.__table]
        maximum = max(cycles)
        minimum = min(cycles)

        if thresh > maximum - minimum:
            return False
        elif self.__table[self.__rank][name] == minimum:
            return False
        else:
            return True
