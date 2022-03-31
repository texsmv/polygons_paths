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

Point::Point(float _x, float _y)
{
    this->x = _x;
    this->y = _y;
}

float Point::distance(Point t)
{
    return (float)(sqrt(pow(this->x - t.x, 2) + pow(this->y - t.y, 2)));
}

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

Node::Node(char _value, Point _point)
{
    this->value = _value;
    this->point = _point;
    this->visit = false;
}

void Node::add_edge(Node *_node)
{
    this->lady.push_back(_node);
    _node->lady.push_back(this);
}

float Node::distance(Node *_t)
{
    return this->point.distance(_t->point);
}

#endif