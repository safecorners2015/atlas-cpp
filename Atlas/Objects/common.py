#This file is distributed under the terms of 
#the GNU Lesser General Public license (See the file COPYING for details).
#Copyright (C) 2000 Stefanus Du Toit and Aloril

import sys, os, filecmp
sys.path.append("../../../Atlas-Python")
from atlas import *
from atlas.codecs import *

def deb(): import pdb; pdb.pm()

copyright_template = \
"""// This file may be redistributed and modified only under the terms of
// the GNU Lesser General Public License (See COPYING for details).
// Copyright 2000-2001 %s.
// Automatically generated using gen_cpp.py.
"""

copyright = copyright_template % "Stefanus Du Toit and Aloril"

#objects that will have static attributes
static_objects = ["root", "root_entity", "root_operation"]

# C++ equivalents of atlas types              
cpp_type = {'map' : 'Atlas::Message::Object::MapType',
            'list' : 'Atlas::Message::Object::ListType',
            'string' : 'std::string',
            'int' : 'long',
            'float' : 'double',
            'RootList' : 'std::vector<Root>',
            'string_list' : 'std::list<std::string>',
            'int_list' : 'std::list<long>',
            'float_list' : 'std::list<double>',
            'string_list_length' : 'std::vector<std::string>',
            'int_list_length' : 'std::vector<long>',
            'float_list_length' : 'std::vector<double>'}

# Const references
cpp_param_type = {'map' : 'const ' + cpp_type['map'] + '&',
                  'list' : 'const ' + cpp_type['list'] + '&',
                  'string' : 'const ' + cpp_type['string'] + '&',
                  'int' : cpp_type['int'],
                  'float' : cpp_type['float'],
                  'RootList' : 'const ' + cpp_type['RootList'] + '&',
                  'string_list' : 'const ' + cpp_type['string_list'] + '&',
                  'int_list' : 'const ' + cpp_type['int_list'] + '&',
                  'float_list' : 'const ' + cpp_type['float_list'] + '&',
                  'string_list_length' : 'const ' + cpp_type['string_list_length'] + '&',
                  'int_list_length' : 'const ' + cpp_type['int_list_length'] + '&',
                  'float_list_length' : 'const ' + cpp_type['float_list_length'] + '&'}

# Non-const references
cpp_param_type2 = {'map' : cpp_type['map'] + '&',
                  'list' : cpp_type['list'] + '&',
                  'string' : cpp_type['string'] + '&',
                  'int' : cpp_type['int'] + '&',
                  'float' : cpp_type['float'] + '&',
                  'RootList' : cpp_type['RootList'] + '&',
                  'string_list' : cpp_type['string_list'] + '&',
                  'int_list' : cpp_type['int_list'] + '&',
                  'float_list' : cpp_type['float_list'] + '&',
                  'string_list_length' : cpp_type['string_list_length'] + '&',
                  'int_list_length' : cpp_type['int_list_length'] + '&',
                  'float_list_length' : cpp_type['float_list_length'] + '&'}

def capitalize_only(str):
    return string.upper(str[:1]) + str[1:]

# Turns some_thing into SomeThing
def classize(id, data=0):
    if type(id)!=StringType: id = id.id
    cid = string.join( map(capitalize_only, string.split(id, '_') ), "")
    if data: return cid + "Data"
    return cid

def doc(indent, text):
    return " " * indent + "/// %s\n" % text

def find_in_parents(obj, attr_name):
    for parent in obj.parents:
        if hasattr(parent, attr_name):
            return parent
    return None

