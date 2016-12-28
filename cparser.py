# # -------------------------------------------------------------------------------
# # pycparser: using_gcc_E_libc.py
# #
# # Similar to the using_cpp_libc.py example, but uses 'gcc -E' instead
# # of 'cpp'. The same can be achieved with Clang instead of gcc. If you have
# # Clang installed, simply replace 'gcc' with 'clang' here.
# #
# # Copyright (C) 2008-2015, Eli Bendersky
# # License: BSD
# # -------------------------------------------------------------------------------
# import os
# import sys
#
# # This is not required if you've installed pycparser into
# # your site-packages/ with setup.py
# #
# sys.path.extend(['.', '..'])
#
# from pycparser import parse_file
#
# if __name__ == "__main__":
#     if len(sys.argv) > 1:
#         filename = sys.argv[1]
#     else:
#         filename = os.path.join(os.getcwd(), 'c_code/main.c')
#
#     ast = parse_file(filename, use_cpp=True,
#                      cpp_path='gcc',
#                      cpp_args=['-E', '-I utils/fake_libc_include'])
#
#     ast.show()

# -----------------------------------------------------------------
# pycparser: func_defs.py
#
# Using pycparser for printing out all the calls of some function
# in a C file.
#
# Copyright (C) 2008-2015, Eli Bendersky
# License: BSD
# -----------------------------------------------------------------
from __future__ import print_function
import sys
import os

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
sys.path.extend(['.', '..'])

from pycparser import c_parser, c_ast, parse_file


# A visitor with some state information (the funcname it's
# looking for)
#
class FuncCallVisitor(c_ast.NodeVisitor):
    def __init__(self, funcname):
        self.funcname = funcname

    def visit_FuncCall(self, node):
        if node.name.name == self.funcname:
            print('%s called at %s' % (self.funcname, node.name.coord))


def show_func_calls(filename, funcname):
    ast = parse_file(filename, use_cpp=True)
    v = FuncCallVisitor(funcname)
    v.visit(ast)


if __name__ == "__main__":
    if len(sys.argv) > 2:
        filename = sys.argv[1]
        func = sys.argv[2]
    else:
        filename = os.path.join(os.getcwd(), 'c_code/main.c')
        func = 'test'

    ast = parse_file(filename, use_cpp=True,
                     cpp_path='gcc',
                     cpp_args=['-E', '-std=c99', '-I utils/fake_libc_include'])

    ast.show()

    show_func_calls(filename, func)
