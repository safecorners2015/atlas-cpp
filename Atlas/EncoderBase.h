// This file may be redistributed and modified only under the terms of
// the GNU Lesser General Public License (See COPYING for details).
// Copyright (C) 2000 Stefanus Du Toit

#ifndef ATLAS_ENCODERBASE_H
#define ATLAS_ENCODERBASE_H

#include "Bridge.h"

namespace Atlas {

class EncoderBase : public Atlas::Bridge {
public:
    EncoderBase(Atlas::Bridge* b) : b(b) { }

    virtual ~EncoderBase() { }
    
    virtual void StreamBegin() { b->StreamBegin(); }
    virtual void StreamMessage(const Map& m) { b->StreamMessage(m); }
    virtual void StreamEnd() { b->StreamEnd(); }
    
    virtual void MapItem(const std::string& name, const Bridge::Map& m)
    { b->MapItem(name, m); }
    virtual void MapItem(const std::string& name, const Bridge::List& l)
    { b->MapItem(name, l); }
    virtual void MapItem(const std::string& name, int i)
    { b->MapItem(name, i); }
    virtual void MapItem(const std::string& name, double d)
    { b->MapItem(name, d); }
    virtual void MapItem(const std::string& name, const std::string& s)
    { b->MapItem(name, s); }
    virtual void MapEnd() { b->MapEnd(); }
    
    virtual void ListItem(const Bridge::Map& m) { b->ListItem(m); }
    virtual void ListItem(const Bridge::List& l) { b->ListItem(l); }
    virtual void ListItem(int i) { b->ListItem(i); }
    virtual void ListItem(double d) { b->ListItem(d); }
    virtual void ListItem(const std::string& s) { b->ListItem(s); }
    virtual void ListEnd() { b->ListEnd(); }

protected:
    Atlas::Bridge* b;
};

} // namespace Atlas 