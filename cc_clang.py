#!/usr/bin/env python

import clang.cindex
from dataset import DataSet
from clang.cindex import CursorKind
from cc_stats import Stats, DefStats, ClassStats, IterationStats, IfStats

fileName = ''
codeLines = []
keywordList = []
usedSet = set()


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
                        keywordList.append(DataSet(node.displayname, node.location.line, node.kind))
                        usedSet.add(node.kind)
                    if node.kind == CursorKind.FOR_STMT or node.kind == CursorKind.WHILE_STMT or node.kind == CursorKind.DO_STMT:
                        keywordList.append(DataSet(node.displayname, node.location.line, node.kind))
                        usedSet.add(node.kind)
                    if node.kind == CursorKind.IF_STMT or node.kind == CursorKind.SWITCH_STMT:
                        keywordList.append(DataSet(node.displayname, node.location.line, node.kind))
                        usedSet.add(node.kind)
                    if node.kind == CursorKind.STRUCT_DECL or node.kind == CursorKind.UNION_DECL or \
                                    node.kind == CursorKind.UNION_DECL or node.kind == CursorKind.CLASS_DECL or node.kind == CursorKind.ENUM_DECL:
                        keywordList.append(DataSet(node.displayname, node.location.line, node.kind))
                        usedSet.add(node.kind)
                    if node.kind == CursorKind.FIELD_DECL or node.kind == CursorKind.VAR_DECL:
                        keywordList.append(DataSet(node.displayname, node.location.line, node.kind))
                        usedSet.add(node.kind)
                    if node.kind == CursorKind.BINARY_OPERATOR:
                        if '&&' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('&&', node.location.line, node.kind))
                        if '||' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('||', node.location.line, node.kind))
                        if '&' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('&', node.location.line, node.kind))
                        if '|' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('|', node.location.line, node.kind))
                        if '<' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('<', node.location.line, node.kind))
                        if '>' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('>', node.location.line, node.kind))
                        if '<=' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('<=', node.location.line, node.kind))
                        if '>=' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('>=', node.location.line, node.kind))
                        if '!' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('!', node.location.line, node.kind))
                        if '~' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('~', node.location.line, node.kind))
                        if '^' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('^', node.location.line, node.kind))
                        if '+' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('+', node.location.line, node.kind))
                        if '-' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('-', node.location.line, node.kind))
                        if '*' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('*', node.location.line, node.kind))
                        if '/' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('/', node.location.line, node.kind))
                        if '++' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('++', node.location.line, node.kind))
                        if '--' in codeLines[node.location.line - 1]:
                            keywordList.append(DataSet('--', node.location.line, node.kind))
                        usedSet.add(node.kind)

    def getKeywordList(self):
        return keywordList


def measure_complexity(code, module_name):
    global fileName
    global codeLines

    codeLines = code

    index = clang.cindex.Index.create()
    tu = index.parse(module_name)

    ast = tu.cursor
    fileName = module_name.split('/')[-1]

    visitor = CCVisitor(ast, description=module_name)

    # print visitor.getKeywordList()
    print usedSet

    return visitor.stats
