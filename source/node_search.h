#ifndef _NODE_SEARCH_H_
#define _NODE_SEARCH_H_

#include <list>
#include <math.h>

using std::list;

// Point Class
class Point
{
public:
    float x; // Coordinate X
    float y; // Coordinate Y

    Point(float, float);
    Point() {}

    float distance(Point t);
};

// Node Class
class Node
{
public:
    char value;        // Value
    bool visit;        // Visited
    float hg;          // h(x) + g(x)
    Point point;       // Point
    list<Node *> lady; // Adjacency List

    Node(char, Point);
    Node(){};

    void add_edge(Node *);
    float distance(Node *);
};

#endif