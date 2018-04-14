#ifndef _GRAPH_H_
#define _GRAPH_H_

#include "..\PureContainer.h"
class Graph : public Container
{
protected:
    unsigned int numberOfVertices;
    unsigned int numberOfEdges;

    void DepthFirstTraversal (
	PrePostVisitor&, Vertex&, Array<bool>&) const;
public:
    Graph ();

    virtual unsigned int NumberOfEdges () const;
    virtual unsigned int NumberOfVertices () const;
    virtual void AddVertex (Vertex&) = 0;
    virtual Vertex& SelectVertex (Vertex::Number) const = 0;
    virtual Vertex& operator [] (Vertex::Number) const;
    virtual void AddEdge (Edge&) = 0;
    virtual Edge& SelectEdge (
	Vertex::Number, Vertex::Number) const = 0;
    virtual bool IsEdge (
	Vertex::Number, Vertex::Number) const = 0;
    virtual bool IsConnected () const;
    virtual bool IsCyclic () const;

    virtual Iterator& Vertices () const = 0;
    virtual Iterator& Edges () const = 0;
    virtual Iterator& IncidentEdges (Vertex const&) const = 0;
    virtual Iterator& EmanatingEdges (Vertex const&) const = 0;

    virtual void DepthFirstTraversal (
	PrePostVisitor&, Vertex const&) const;
    virtual void BreadthFirstTraversal (
	Visitor&, Vertex const&) const;
    // ...
};

class Digraph : public virtual Graph
{
public:
    virtual bool IsConnected () const;
    virtual bool IsCyclic () const;
    virtual void TopologicalOrderTraversal (
	Visitor&) const;
};

#endif