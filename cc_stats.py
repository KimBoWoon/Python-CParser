class Stats(object):
    def __init__(self, name):
        self.name = name
        self.classes = []
        self.functions = []
        self.iterations = []
        self.ifState = []
        self.complexity = 1

    def __str__(self):
        return 'Stats: name=%r, classes=%r, functions=%r, iterations=%r, complexity=%r' \
               % (self.name, self.classes, self.functions, self.iterations, self.complexity)

    __repr__ = __str__


class ClassStats(Stats):
    def __str__(self):
        return 'Stats: name=%r, methods=%r, iterations=%r, complexity=%r, inner_class=%r' \
               % (self.name, self.functions, self.iterations, self.complexity, self.classes)

    __repr__ = __str__


class DefStats(Stats):
    def __str__(self):
        return 'DefStats: name=%r, iterations=%r, complexity=%r' \
               % (self.name, self.iterations, self.complexity)

    __repr__ = __str__


class IterationStats(Stats):
    def __str__(self):
        return 'IterationStats: name=%r, iterations=%r, complexity=%r' \
               % (self.name, self.iterations, self.complexity)

    __repr__ = __str__

class IfStats(Stats):
    def __str__(self):
        return 'IfStats: name=%r, iterations=%r, complexity=%r' \
               % (self.name, self.iterations, self.complexity)

    __repr__ = __str__
