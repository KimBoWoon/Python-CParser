#!/usr/bin/env python

import clang.cindex
from dataset import DataSet
from clang.cindex import CursorKind
from cc_stats import Stats, DefStats, ClassStats, IterationStats, IfStats

codeLines = []
keywordList = set()
usedSet = set()
cursor = {'CursorKind.FUNCTION_DECL': 0, 'CursorKind.FOR_STMT': 1, 'CursorKind.CLASS_DECL': 2,
          'CursorKind.STRUCT_DECL': 3, 'CursorKind.CALL_EXPR': 4, 'CursorKind.IF_STMT': 5,
          'CursorKind.BINARY_OPERATOR': 6, 'CursorKind.FIELD_DECL': 7, 'CursorKind.WHILE_STMT': 8,
          'CursorKind.DO_STMT': 9, 'CursorKind.VAR_DECL': 10}


class CCVisitor(object):
    """Encapsulates the cyclomatic complexity counting."""

    def __init__(self, ast, stats=None, description=None):
        global fileName
        global codeLines

        self.stats = stats or Stats(description or '<module>')
        for child in ast.get_children():
            for node in child.walk_preorder():
                if str(node.location.file).find(fileName) != -1:
                    if node.kind == CursorKind.FUNCTION_DECL or node.kind == CursorKind.CALL_EXPR:
                        keywordList.add(DataSet(node.displayname, node.location.line, node.kind))
                        usedSet.add(node.kind)
                    if node.kind == CursorKind.FOR_STMT or node.kind == CursorKind.WHILE_STMT or node.kind == CursorKind.DO_STMT:
                        keywordList.add(DataSet(node.displayname, node.location.line, node.kind))
                        usedSet.add(node.kind)
                    if node.kind == CursorKind.IF_STMT or node.kind == CursorKind.SWITCH_STMT:
                        keywordList.add(DataSet(node.displayname, node.location.line, node.kind))
                        usedSet.add(node.kind)
                    if node.kind == CursorKind.STRUCT_DECL or node.kind == CursorKind.UNION_DECL or \
                                    node.kind == CursorKind.UNION_DECL or node.kind == CursorKind.CLASS_DECL or node.kind == CursorKind.ENUM_DECL:
                        keywordList.add(DataSet(node.displayname, node.location.line, node.kind))
                        usedSet.add(node.kind)
                    if node.kind == CursorKind.FIELD_DECL or node.kind == CursorKind.VAR_DECL:
                        # keywordList.append(DataSet(node.displayname, node.location.line, node.kind, node.type.kind))
                        keywordList.add(DataSet(node.displayname, node.location.line, node.kind))
                        usedSet.add(node.kind)
                    if node.kind == CursorKind.BINARY_OPERATOR:
                        if '&&' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('&&', node.location.line, node.kind))
                        if '||' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('||', node.location.line, node.kind))
                        if '&' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('&', node.location.line, node.kind))
                        if '|' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('|', node.location.line, node.kind))
                        if '<' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('<', node.location.line, node.kind))
                        if '>' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('>', node.location.line, node.kind))
                        if '<=' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('<=', node.location.line, node.kind))
                        if '>=' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('>=', node.location.line, node.kind))
                        if '!' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('!', node.location.line, node.kind))
                        if '~' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('~', node.location.line, node.kind))
                        if '^' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('^', node.location.line, node.kind))
                        if '+' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('+', node.location.line, node.kind))
                        if '-' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('-', node.location.line, node.kind))
                        if '*' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('*', node.location.line, node.kind))
                        if '/' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('/', node.location.line, node.kind))
                        if '++' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('++', node.location.line, node.kind))
                        if '--' in codeLines[node.location.line - 1]:
                            keywordList.add(DataSet('--', node.location.line, node.kind))
                        usedSet.add(node.kind)


def measure_complexity(code, module_name):
    global fileName
    global codeLines

    codeLines = code

    index = clang.cindex.Index.create()
    tu = index.parse(module_name)

    ast = tu.cursor
    fileName = module_name.split('/')[-1]

    visitor = CCVisitor(ast, description=module_name)

    kindMatrix = []
    usedMatrix = []
    functionDecl = 50
    functionCall = 65
    classDecl = 46
    structDecl = 48
    valueDecl = 11

    for kind in keywordList:
        temp = [0. for row in range(80)]

        if 'CursorKind.IF_STMT' == str(kind.type):
            temp[cursor[str(kind.type)]] = 1.
            usedMatrix.append(temp)
            kindMatrix.append(kind)
        elif 'CursorKind.BINARY_OPERATOR' == str(kind.type):
            temp[cursor[str(kind.type)]] = 1.
            usedMatrix.append(temp)
            kindMatrix.append(kind)
        elif 'CursorKind.FIELD_DECL' == str(kind.type):
            temp[cursor[str(kind.type)]] = 1.
            usedMatrix.append(temp)
            kindMatrix.append(kind)
        elif 'CursorKind.FOR_STMT' == str(kind.type):
            temp[cursor[str(kind.type)]] = 1.
            usedMatrix.append(temp)
            kindMatrix.append(kind)
        elif 'CursorKind.WHILE_STMT' == str(kind.type):
            temp[cursor[str(kind.type)]] = 1.
            usedMatrix.append(temp)
            kindMatrix.append(kind)
        elif 'CursorKind.DO_STMT' == str(kind.type):
            temp[cursor[str(kind.type)]] = 1.
            usedMatrix.append(temp)
            kindMatrix.append(kind)
        elif 'CursorKind.FUNCTION_DECL' == str(kind.type):
            temp[functionDecl] = 1.
            usedMatrix.append(temp)
            kindMatrix.append(kind)
            functionDecl += 1
        elif 'CursorKind.CLASS_DECL' == str(kind.type):
            temp[classDecl] = 1.
            usedMatrix.append(temp)
            kindMatrix.append(kind)
            classDecl += 1
        elif 'CursorKind.STRUCT_DECL' == str(kind.type):
            temp[structDecl] = 1.
            usedMatrix.append(temp)
            kindMatrix.append(kind)
            structDecl += 1
        elif 'CursorKind.VAR_DECL' == str(kind.type):
            temp[valueDecl] = 1.
            usedMatrix.append(temp)
            kindMatrix.append(kind)
            valueDecl += 1
        elif 'CursorKind.CALL_EXPR' == str(kind.type):
            temp[functionCall] = 1.
            usedMatrix.append(temp)
            kindMatrix.append(kind)
            functionCall += 1

    for i in usedMatrix:
        print i

    # print len(keywordList), keywordList
    # print len(usedSet), usedSet
    keywordList.clear()

    return visitor.stats
