#!/usr/bin/env python

import os
import sys
from glob import glob
import cc_python, cc_clang
import re

iterationDep = 0
totalClassCount = 0
totalFunctionCount = 0
totalComplexity = 0
defaultComplexityCount = 0

classSet = []
functionSet = []
iterationSet = []


def checkIterationComplexity(_iter, count=0):
    global totalComplexity
    global iterationDep

    count += 1
    totalComplexity += _iter.complexity

    for innerIter in _iter.iterations:
        checkIterationComplexity(innerIter, count)

    if iterationDep < count:
        iterationDep = count


def checkFunctionComplexity(func):
    global defaultComplexityCount
    global totalFunctionCount
    global totalComplexity

    if func.complexity is 1 and len(func.iterations) is 0 and len(func.functions) is 0:
        defaultComplexityCount += 1

    totalFunctionCount += 1
    totalComplexity += func.complexity

    for _iter in func.iterations:
        checkIterationComplexity(_iter)

    for innerFunc in func.functions:
        checkFunctionComplexity(innerFunc)


def checkClassComplexity(cls):
    global totalClassCount
    global totalComplexity

    totalClassCount += 1
    totalComplexity += cls.complexity

    for _iter in cls.iterations:
        checkIterationComplexity(_iter)

    for func in cls.functions:
        checkFunctionComplexity(func)

    for innerCls in cls.classes:
        checkClassComplexity(innerCls)


def main():
    global totalClassCount
    global totalFunctionCount
    global totalComplexity
    global defaultComplexityCount
    global iterationDep

    extension = {'C': '*.c', 'C++': '*.cpp', 'JAVA': '*.java', 'PYTHON': '*.py', 'TXT': '*indata.txt'}
    statsSet = set()

    args = sys.argv
    # filePath = args[1]
    # language = args[2]
    filePath = os.path.join(os.getcwd(), 'c_code/test')
    language = 'C++'

    for file in glob(os.path.join(filePath, extension['TXT'])):
        old = file
        f = file
        p = re.compile('txt')
        f = p.sub('cpp', f)
        os.rename(old, f)

    files = set()
    if os.path.isdir(filePath):
        for f in glob(os.path.join(filePath, extension[language])):
            if os.path.isfile(f):
                files.add(os.path.abspath(f))

    for _file in files:
        fp = open(_file)
        if language == 'PYTHON':
            totalFunctionCount += 1
            code = fp.read()
            stats = cc_python.measure_complexity(code, _file)

        elif language == 'C' or language == 'C++':
            code = fp.readlines()
            if len(code) is 1:
                code = code[0].split("\r")
            stats = cc_clang.measure_complexity(code, _file)

        else:
            pass
        # break
        statsSet.add(stats)

        if len(stats.classes) != 0:
            classSet.append(stats.classes)
        if len(stats.functions) != 0:
            functionSet.append(stats.functions)
        if len(stats.iterations) != 0:
            iterationSet.append(stats.iterations)

    for stat in statsSet:
        totalComplexity += stats.complexity

        for _iter in stat.iterations:
            checkIterationComplexity(_iter)

        for func in stat.functions:
            checkFunctionComplexity(func)

        for cls in stat.classes:
            checkClassComplexity(cls)

    funcCount = totalFunctionCount - defaultComplexityCount

    if funcCount < 1:
        funcCount = 1

    # print totalComplexity, (totalComplexity - defaultComplexityCount) / (funcCount), iterationDep


if __name__ == '__main__':
    main()

    # print classSet
    # print functionSet
    # print iterationSet
