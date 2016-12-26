#!/usr/bin/env python

import compiler
from compiler.visitor import ASTVisitor
from cc_stats import Stats, DefStats, ClassStats, IterationStats

class CCVisitor(ASTVisitor):
    """Encapsulates the cyclomatic complexity counting."""

    def __init__(self, ast, stats=None, description=None):
        ASTVisitor.__init__(self)
        if isinstance(ast, basestring):
            ast = compiler.parse(ast)

        self.stats = stats or Stats(description or '<module>')
        for child in ast.getChildNodes():
            compiler.walk(child, self, walker=self)

    def dispatchChildren(self, node):
        for child in node.getChildNodes():
            self.dispatch(child)

    def visitFunction(self, node):
        if not hasattr(node, 'name'): # lambdas
            node.name = '<lambda>'
        stats = DefStats(node.name)
        stats = CCVisitor(node, stats).stats
        self.stats.functions.append(stats)

    visitLambda = visitFunction

    def visitClass(self, node):
        stats = ClassStats(node.name)
        stats = CCVisitor(node, stats).stats
        self.stats.classes.append(stats)

    def visitIf(self, node):
        self.stats.complexity += len(node.tests)
        self.dispatchChildren(node)

    def __processDecisionPoint(self, node):
        stats = IterationStats(None)
        stats = CCVisitor(node, stats).stats
        self.stats.iterations.append(stats)

    visitFor = visitGenExprFor = visitGenExprIf \
            = visitListCompFor = visitListCompIf \
            = visitWhile = _visitWith = __processDecisionPoint

    def visitAnd(self, node):
        self.dispatchChildren(node)
        self.stats.complexity += 1

    def visitOr(self, node):
        self.dispatchChildren(node)
        self.stats.complexity += 1


def measure_complexity(ast, module_name=None):
    return CCVisitor(ast, description=module_name).stats
