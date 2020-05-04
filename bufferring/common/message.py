class Message:
    def __init__(self, src=-1, cycle=-1, name=None, grad=None):
        self.src = src
        self.cycle = cycle
        self.name = name
        self.grad = grad
