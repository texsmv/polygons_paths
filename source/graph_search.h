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

#endif