// This file may be redistributed and modified only under the terms of
// the GNU Lesser General Public License (See COPYING for details).
// Copyright 2000 Stefanus Du Toit.
// Automatically generated using gen_cc.py.

#include "Logout.h"

using Atlas::Message::Object;

namespace Atlas { namespace Objects { namespace Operation { 

Logout::Logout()
     : Login()
{
    SetId(std::string("logout"));
    Object::ListType parents(1,std::string("login"));
    SetParents(parents);
}

Logout Logout::Instantiate()
{
    Logout value;

    value.SetParents(Object::ListType(1,std::string("logout")));
    value.SetObjtype(std::string("op"));
    
    return value;
}

} } } // namespace Atlas::Objects::Operation
