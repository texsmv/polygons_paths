#ifndef _GRAPH_SEARCH_H_
#define _GRAPH_SEARCH_H_

#include <iostream>
#include <vector>
#include <queue>

#include "node_search.h"

using std::cout;
using std::priority_queue;
using std::vector;

struct Compare
{
    bool operator()(Node *const &_s, Node *const &_t)
    {
        return _s->hg < _t->hg;
    }
};

class Graph
{
private:
    vector<Node *> vnode;

public:
    Graph(){};

    Node *find(char _d);

    void insert_node(char, float, float);
    void insert_edge(char, char, bool);

    void best_first(Node *, Node *);
    void a_asterisk(Node *, Node *);

    ~Graph(){};
};

Node *Graph::find(char _d)
{
    for (unsigned i = 0; i < this->vnode.size(); i++)
    {
        if (this->vnode[i]->value == _d)
        {
            return this->vnode[i];
        }
    }
    return NULL;
}

void Graph::insert_node(char _d, float _x, float _y)
{
    this->vnode.push_back(new Node(_d, Point(_x, _y)));
}

void Graph::insert_edge(char _s, char _t, bool _dir)
{
    Node *ps = find(_s);
    Node *pt = find(_t);

    if (ps == NULL or pt == NULL)
        return;

    if (_dir)
    {
        ps->add_edge(pt);
    }
    else
    {
        ps->add_edge(pt);
        pt->add_edge(ps);
    }
}

void Graph::a_asterisk(Node *_s, Node *_t)
{
    vector<char> path;

    typename std::list<Node *>::iterator it;
    std::priority_queue<Node *, std::vector<Node *>, Compare> pq;

    pq.push(_s);
    Node *current;

    float h;
    float g;

    float tx;
    float ty;

    while (!pq.empty())
    {
        current = pq.top();
        pq.pop();

        cout << current->value << " ";

        if (current == _t)
        {
            break;
        }

        for (it = current->lady.begin(); it != current->lady.end(); it++)
        {
            if (!(*it)->visit)
            {
                (*it)->visit = true;
                h = (*it)->distance(_t);
                g = current->distance(*it);
                (*it)->hg = h + g;
                pq.push(*it);

                tx = (*it)->point.x;
                ty = (*it)->point.y;
            }
        }
    }
}

void Graph::best_first(Node *_s, Node *_t)
{
    typename std::list<Node *>::iterator it;
    std::priority_queue<Node *, std::vector<Node *>, Compare> pq;

    pq.push(_s);
    Node *current;

    float g;

    while (!pq.empty())
    {
        current = pq.top();
        pq.pop();

        cout << current->value << " ";

        if (current == _t)
        {
            break;
        }

        for (it = current->lady.begin(); it != current->lady.end(); it++)
        {
            if (!(*it)->visit)
            {
                (*it)->visit = true;
                g = current->distance(*it);
                (*it)->hg = g;
                pq.push(*it);
            }
        }
    }
}

#endif