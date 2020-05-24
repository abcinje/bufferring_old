class ProgressTable:
    def __init__(self, size, rank, name_list):
        assert size > 0
        assert rank >= 0 and rank < size
        self.__table = size * [{name: 0 for name in name_list}]
        self.__size = size
        self.__rank = rank

    def get_my_cycle(self, name):
        return self.__table[self.__rank][name]

    def update(self, node, name):
        assert node >= 0 and node < self.__size
        self.__table[node][name] += 1

    def blocked(self, thresh):
        maximum = max([max(d.values()) for d in self.__table])
        minimum = min([min(d.values()) for d in self.__table])

        if thresh > maximum - minimum:
            return False
        elif minimum in self.__table[self.__rank].values():
            return False
        else:
            return True
