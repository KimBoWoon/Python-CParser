#!/usr/bin/env python

import clang.cindex
from dataset import DataSet
from clang.cindex import CursorKind
from cc_stats import Stats, DefStats, ClassStats, IterationStats, IfStats

fileName = ''
codeLines = []
keywordList = []


class CCVisitor(object):
    """Encapsulates the cyclomatic complexity counting."""

    def __init__(self, ast, stats=None, description=None):
        global fileName
        global codeLines

        self.stats = stats or Stats(description or '<module>')
        for child in ast.get_children():
            for node in child.walk_preorder():
                if str(node.location.file).find(fileName) != -1:
                    print '{0}\t{1}\t{2}\t{3}'.format(node.kind, node.spelling, node.location.line, node.displayname)
                    if node.kind == CursorKind.FUNCTION_DECL or node.kind == CursorKind.CALL_EXPR:
                        keywordList.append(DataSet(node.displayname, node.location.line, node.kind))

    # if node.kind == CursorKind.FUNCTION_DECL or node.kind == CursorKind.CXX_METHOD or \
    #                                 node.kind == CursorKind.CONSTRUCTOR or node.kind == CursorKind.DESTRUCTOR:
    #                     if node.is_definition():
    #                         self.visitFunction(node)
    #                         node._kind_id = 99999
    #
    #                 elif node.kind == CursorKind.CLASS_DECL or node.kind == CursorKind.STRUCT_DECL:
    #                     self.visitClass(node)
    #                     node._kind_id = 99999
    #
    #                 elif node.kind == CursorKind.WHILE_STMT or node.kind == CursorKind.FOR_STMT or \
    #                                 node.kind == CursorKind.DO_STMT:
    #                     self.__processDecisionPoint(node)
    #                     node._kind_id = 99999
    #
    #                 elif node.kind == CursorKind.IF_STMT or node.kind == CursorKind.SWITCH_STMT or \
    #                                 node.kind == CursorKind.LINKAGE_SPEC or node.kind == CursorKind.CONDITIONAL_OPERATOR or \
    #                                 node.kind == CursorKind.GOTO_STMT or node.kind == CursorKind.CONDITIONAL_OPERATOR:
    #                     self.stats.complexity += 1
    #
    #                 elif node.kind == CursorKind.BINARY_OPERATOR:
    #                     self.stats.complexity += codeLines[node.location.line - 1].count('&&')
    #                     self.stats.complexity += codeLines[node.location.line - 1].count('||')
    #                     node._kind_id = 99999
    #
    #                 else:
    #                     pass
    #
    # def visitFunction(self, node):
    #     stats = DefStats(node.spelling)
    #     stats = CCVisitor(node, stats).stats
    #     # print 'Func ' + str(stats)
    #     self.stats.functions.append(stats)
    #
    # def visitClass(self, node):
    #     stats = ClassStats(node.spelling)
    #     stats = CCVisitor(node, stats).stats
    #     # print 'Class ' + str(stats)
    #     self.stats.classes.append(stats)
    #
    # def __processDecisionPoint(self, node):
    #     stats = IterationStats(None)
    #     stats = CCVisitor(node, stats).stats
    #     # print 'For ' + str(stats)
    #     self.stats.iterations.append(stats)
    #
    # def visitIf(self, node):
    #     stats = IfStats(node.spelling)
    #     stats = CCVisitor(node, stats).stats
    #     # print 'If ' + str(stats)
    #     self.stats.ifstate.append(stats)
    #
    # def printStatus(self):
    #     print self.stats.classes
    #     print self.stats.functions
    #     print self.stats.iterations

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

    print visitor.getKeywordList()

    return visitor.stats
