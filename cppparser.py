from pygccxml import utils
from pygccxml import declarations
from pygccxml import parser
import os

# Find out the c++ parser
generator_path, generator_name = utils.find_xml_generator()

# Configure the xml generator
xml_generator_config = parser.xml_generator_configuration_t(
    xml_generator_path=generator_path,
    xml_generator=generator_name)

# The c++ file we want to parse
filename = os.path.join(os.getcwd(), 'c_code/main.cpp')

decls = parser.parse([filename], xml_generator_config)
global_namespace = declarations.get_global_namespace(decls)
# ns = global_namespace.namespace("ns")

# The variables() method will return a list of variables.
# We know that the c variable is the third one in the list:
# c = ns.variables()[2]
# print("My name is: " + c.name)
# print("My type is: " + str(c.decl_type))
# print("My value is: " + c.value)

# Of course you can also loop over the list and look for the right name
# for var in ns.variables():
#     print("My name is: " + str(var.name))
#     print("My type is: " + str(var.decl_type))
#     print("My value is: " + str(var.value))

for var in global_namespace.variables():
    print("My name is: " + str(var.name))
    print("My type is: " + str(var.decl_type))
    print("My value is: " + str(var.value))

# One way to get a variable is to use the variable() method and
# a lambda function. This is the most flexible way as you can implement
# your own lambda function to filter out variables following your
# specific criteria.
# c = ns.variable(lambda v: v.name == "c")
# print("My name is: " + c.name)
# print("My type is: " + str(c.decl_type))
# print("My value is: " + c.value)

# We have just one declaration in ns, which is our Test class:
# classTest = ns.declarations[0]
# print(classTest.name, type(classTest))
# > 'Test', <class 'pygccxml.declarations.class_declaration.class_t'

# Loop over the two constructors:
# for constructor in classTest.constructors():
#     print(str(constructor), constructor.is_artificial)
# > ns::Test::Test() [constructor], False
# > ns::Test::Test(ns::Test const & arg0) [constructor], True
