class ProgressTable:
    def __init__(self, size, rank):
        assert size > 0
        assert rank >= 0 and rank < size
        self.__table = size * [0]
        self.__size = size
        self.__rank = rank

    def update(self, node):
        assert node >= 0 and node < self.__size
        self.__table[node] += 1

    def bounded(self, thresh):
        maximum = max(self.__table)
        minimum = min(self.__table)

        if thresh > maximum - minimum:
            return True
        elif self.__table[self.__rank] == minimum:
            return True
        else:
            return False

    def print(self):
        string = ''
        string += '+------------------+\n'
        string += '| P.Table (node%2d) |\n' % self.__rank
        string += '+--------+---------+\n'
        string += '|  node  |  cycle  |\n'
        string += '+--------+---------+\n'

        for i in range(self.__size):
            string += '|  %4d  |  %5d  |\n' % (i, self.__table[i])
            string += '+--------+---------+\n'

        print(string)
