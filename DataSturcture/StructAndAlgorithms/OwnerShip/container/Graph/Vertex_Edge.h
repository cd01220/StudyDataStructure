#ifndef _VERTEX_EDGE_H_
#define _VERTEX_EDGE_H_

#include ".\StructAndAlgorithms\Object\Object.h" //class Object »ùÀà¡£
//////////////////////////////////////////////////////////////////////////////
//	Class: Vertex
//////////////////////////////////////////////////////////////////////////////
class Vertex : public Object
{
public:
    typedef unsigned int Number;
protected:
    Number number;
public:
    Vertex (Number);
    virtual operator Number () const;
    // added by liuhao 2005-12-15, Object class Object member function.
protected:
    virtual int CompareTo (Object const&) const = 0;
public:
    virtual bool IsNull () const;
    virtual HashValue Hash () const;
    virtual void Put (ostream&) const;
};

//////////////////////////////////////////////////////////////////////////////
//	Class: Edge
//////////////////////////////////////////////////////////////////////////////
class Edge : public Object
{
protected:
    Vertex& v0;
    Vertex& v1;
public:
    Edge (Vertex&, Vertex&);
    virtual Vertex& V0 () const;
    virtual Vertex& V1 () const;
    virtual Vertex& Mate (Vertex const&) const;
    // added by liuhao 2005-12-15, Object class Object member function.
protected:
    virtual int CompareTo (Object const&) const;
public:
    virtual bool IsNull () const;
    virtual HashValue Hash () const;
    virtual void Put (ostream&) const;
};


#endif