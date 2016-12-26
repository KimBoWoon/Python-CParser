#!/usr/bin/env python

import clang.cindex
from clang.cindex import CursorKind
from cc_stats import Stats, DefStats, ClassStats, IterationStats

fileName = ''
codeLines = []

class CCVisitor(object):
    """Encapsulates the cyclomatic complexity counting."""

    def __init__(self, ast, stats=None, description=None):
        global fileName
        global codeLines

        self.stats = stats or Stats(description or '<module>')
        for child in ast.get_children():
            for node in child.walk_preorder():
                if str(node.location.file).find(fileName) != -1:
                    if node.kind == CursorKind.FUNCTION_DECL or node.kind == CursorKind.CXX_METHOD or \
                        node.kind == CursorKind.CONSTRUCTOR or node.kind == CursorKind.DESTRUCTOR:
                        if node.is_definition():
                            self.visitFunction(node)
                            node._kind_id = 99999

                    elif node.kind == CursorKind.CLASS_DECL or node.kind == CursorKind.STRUCT_DECL:
                        self.visitClass(node)
                        node._kind_id = 99999

                    elif node.kind == CursorKind.WHILE_STMT or node.kind == CursorKind.FOR_STMT or\
                        node.kind == CursorKind.DO_STMT:
                        self.__processDecisionPoint(node)
                        node._kind_id = 99999

                    elif node.kind == CursorKind.IF_STMT or node.kind == CursorKind.SWITCH_STMT or\
                        node.kind == CursorKind.LINKAGE_SPEC or node.kind == CursorKind.CONDITIONAL_OPERATOR or\
                        node.kind == CursorKind.GOTO_STMT or node.kind == CursorKind.CONDITIONAL_OPERATOR:
                        self.stats.complexity += 1

                    elif node.kind == CursorKind.BINARY_OPERATOR:
                        self.stats.complexity += codeLines[node.location.line-1].count('&&')
                        self.stats.complexity += codeLines[node.location.line-1].count('||')
                        node._kind_id = 99999

                    else:
                        pass

    def visitFunction(self, node):
        stats = DefStats(node.spelling)
        stats = CCVisitor(node, stats).stats
        self.stats.functions.append(stats)

    def visitClass(self, node):
        stats = ClassStats(node.spelling)
        stats = CCVisitor(node, stats).stats
        self.stats.classes.append(stats)

    def __processDecisionPoint(self, node):
        stats = IterationStats(None)
        stats = CCVisitor(node, stats).stats
        self.stats.iterations.append(stats)


def measure_complexity(code, module_name):
    global fileName
    global codeLines

    codeLines = code

    index = clang.cindex.Index.create()
    tu = index.parse(module_name)

    ast = tu.cursor
    fileName = module_name.split('/')[-1]

    return CCVisitor(ast, description=module_name).stats
