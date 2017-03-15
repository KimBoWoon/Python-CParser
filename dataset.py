class DataSet:
    def __init__(self, name, line, type, decltype=None):
        self.name = name
        self.line = line
        self.type = type
        self.declType = decltype

    def __str__(self):
        return '[name: %s, line: %s, type: %s, declType: %s]' % (self.name, self.line, self.type, self.declType)

    __repr__ = __str__

    def __eq__(self, other):
        return other and self.name == other.name and self.type == self.type

    def __ne__(self, other):
        return not self.__eq__(other)

    def __hash__(self):
        return hash((self.name, self.name))
