#ifndef _GRAPH_SEARCH_H_
#define _GRAPH_SEARCH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <map>

#include "node_search.h"

using std::cout;
using std::map;
using std::pair;
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
    void clean();

    void insert_node(char, float, float);
    void insert_edge(char, char, bool);

    vector<char> best_first(Node *, Node *);
    vector<char> a_asterisk(Node *, Node *);

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

void Graph::clean()
{
    for (unsigned i = 0; i < this->vnode.size(); i++)
    {
        this->vnode[i]->hg = -1;
        this->vnode[i]->visit = false;
    }
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

vector<char> Graph::a_asterisk(Node *_s, Node *_t)
{
    this->clean();
    vector<char> path, tmp;
    map<char, vector<char>> paths;

    priority_queue<Node *, vector<Node *>, Compare> pq;
    pq.push(_s);

    path.push_back(_s->value);
    paths.insert(pair(_s->value, path));

    Node *current;

    float h;
    float g;

    while (!pq.empty())
    {
        current = pq.top();
        pq.pop();

        if (current == _t)
        {
            path = paths.at(current->value);
            break;
        }

        for (auto it = current->lady.begin(); it != current->lady.end(); it++)
        {
            if (!(*it)->visit)
            {
                (*it)->visit = true;
                h = (*it)->distance(_t);
                g = current->distance(*it);
                (*it)->hg = h + g;
                pq.push(*it);

                tmp = paths.at(current->value);
                tmp.push_back((*it)->value);
                paths.insert(pair((*it)->value, tmp));
            }
        }
    }

    return path;
}

vector<char> Graph::best_first(Node *_s, Node *_t)
{
    this->clean();
    vector<char> path, tmp;
    map<char, vector<char>> paths;

    std::priority_queue<Node *, std::vector<Node *>, Compare> pq;
    pq.push(_s);

    path.push_back(_s->value);
    paths.insert(pair(_s->value, path));

    Node *current;

    float g;

    while (!pq.empty())
    {
        current = pq.top();
        pq.pop();

        if (current == _t)
        {
            path = paths.at(current->value);
            break;
        }

        for (auto it = current->lady.begin(); it != current->lady.end(); it++)
        {
            if (!(*it)->visit)
            {
                (*it)->visit = true;
                g = current->distance(*it);
                (*it)->hg = g;
                pq.push(*it);

                tmp = paths.at(current->value);
                tmp.push_back((*it)->value);
                paths.insert(pair((*it)->value, tmp));
            }
        }
    }

    return path;
}

#endif