class Message:
    def __init__(self, src=-1, cycle=-1, grads=None):
        self.src = src
        self.cycle = cycle
        self.grads = grads
