class DataSet:
    def __init__(self, function, line, type):
        self.function = function
        self.line = line
        self.type = type

    def __str__(self):
        return '[name: %s, line: %s, type: %s]' % (self.function, self.line, self.type)

    __repr__ = __str__
