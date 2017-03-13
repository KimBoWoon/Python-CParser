class DataSet:
    def __init__(self, function, line, type, decltype=None):
        self.function = function
        self.line = line
        self.type = type
        self.declType = decltype

    def __str__(self):
        return '[name: %s, line: %s, type: %s, declType: %s]' % (self.function, self.line, self.type, self.declType)

    __repr__ = __str__
