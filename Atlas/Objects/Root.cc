// This file may be redistributed and modified only under the terms of
// the GNU Lesser General Public License (See COPYING for details).
// Copyright (C) 2000 Stefanus Du Toit

#include "../Message/Encoder.h"
#include "Root.h"

using namespace Atlas;
using namespace Atlas::Message;
using namespace std;

namespace Atlas { namespace Objects {

Root::Root()
{
    Object::ListType parents;
    SetParents(parents);
    SetId("root");
    SetObjtype("meta");
    SetName("");
}

Root::Root(const string& id)
{
    Object::ListType parents;
    parents.push_back(string("root"));
    SetParents(parents);
    SetId(id);
    SetObjtype("instance");
}

Root::~Root()
{
}

Root Root::Instantiate()
{
    Root root("");
    return root;
}

bool Root::HasAttr(const string& name) const
{
    if (name == "parents") return true;
    if (name == "id") return true;
    if (name == "objtype") return true;
    if (name == "name") return true;
    return (attributes.find(name) == attributes.end());
}

Object Root::GetAttr(const string& name) const
    throw (NoSuchAttrException) 
{
    if (name == "parents") return attr_parents;
    if (name == "id") return attr_id;
    if (name == "objtype") return attr_objtype;
    if (name == "name") return attr_name;
    if (attributes.find(name) == attributes.end())
        throw NoSuchAttrException(name);
    return ((*attributes.find(name)).second);
}

void Root::SetAttr(const string& name, const Object& attr)
{
    if (name == "parents") { SetParents(attr.AsList()); return; }
    if (name == "id") { SetId(attr.AsString()); return; }
    if (name == "objtype") { SetObjtype(attr.AsString()); return; }
    if (name == "name") { SetName(attr.AsString()); return; }
    attributes[name] = attr;
}

void Root::RemoveAttr(const string& name)
{
    if (name == "parents") return;
    if (name == "id") return;
    if (name == "objtype") return;
    if (name == "name") return;
    attributes.erase(name);
}

Object Root::AsObject() const
{
    Object::MapType allattrs = attributes;
    allattrs["parents"] = Object(attr_parents);
    allattrs["id"] = Object(attr_id);
    allattrs["objtype"] = Object(attr_objtype);
    allattrs["name"] = Object(attr_name);
    return Object(allattrs);
}

Object::MapType Root::AsMap() const
{
    Object::MapType allattrs = attributes;
    allattrs["parents"] = Object(attr_parents);
    allattrs["id"] = Object(attr_id);
    allattrs["objtype"] = Object(attr_objtype);
    allattrs["name"] = Object(attr_name);
    return allattrs;
}

void Root::SendContents(Bridge* b) const
{
    SendParents(b);
    SendId(b);
    SendObjtype(b);
    SendName(b);

    Message::Encoder e(b);
    typedef map<string, Object>::const_iterator Iter;
    for (Iter I = attributes.begin(); I != attributes.end(); I++)
        e.MapItem((*I).first, (*I).second);
}

} } // namespace Atlas::Objects
