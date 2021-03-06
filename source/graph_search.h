#ifndef _GRAPH_SEARCH_H_
#define _GRAPH_SEARCH_H_

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <fstream>
#include <stack>
#include <chrono>

#include "node_search.h"
#include "graph_utils.h"

using std::cout;
using std::ifstream;
using std::make_pair;
using std::map;
using std::pair;
using std::priority_queue;
using std::stack;
using std::string;
using std::vector;

using namespace std::chrono;

struct Compare
{
    bool operator()(Node *const &_s, Node *const &_t)
    {
        return _s->hg > _t->hg;
    }
};

class Graph
{
private:
    vector<Node *> vnode;

public:
    Graph(){};
    Graph(string, bool);

    Node *find(char);
    void clean();

    void insert_node(char, float, float);
    void insert_edge(char, char, bool);

    vector<char> best_first(Node *, Node *);
    vector<char> a_star(Node *, Node *);

    vector<char> id_astar(Node *, Node *);
    vector<char> id_astar_fun(Node *, Node *, float);

    vector<char> id_dfs(Node *, Node *);
    vector<char> dfs(Node *, Node *, int);

    unsigned size();

    ~Graph(){};
};

Graph::Graph(string _file, bool _dir = false)
{
    ifstream file(_file);
    string str;
    bool vertexs_read = false;
    vector<string> tokens;

    while (getline(file, str))
    {
        if (!vertexs_read)
        {
            if (str.empty())
            {
                vertexs_read = true;
            }
            else
            {
                tokens = split(str, ' ');
                this->insert_node(tokens[0][0], stof(tokens[1]), stof(tokens[2]));
            }
        }
        else
        {
            tokens = split(str, ' ');
            for (int i = 1; i < tokens.size(); i++)
            {
                this->insert_edge(tokens[0][0], tokens[i][0], _dir);
            }
        }
    }
}

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

unsigned Graph::size()
{
    return this->vnode.size();
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

vector<char> Graph::a_star(Node *_s, Node *_t)
{
    this->clean();
    int visits = 0;

    auto start = high_resolution_clock::now();

    vector<char> path, tmp;
    map<char, vector<char>> paths;

    priority_queue<Node *, vector<Node *>, Compare> pq;
    _s->visit = true;
    pq.push(_s);

    path.push_back(_s->value);
    paths.insert(make_pair(_s->value, path));

    Node *current;

    float h;
    float g;

    while (!pq.empty())
    {
        visits++;
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
                paths.insert(make_pair((*it)->value, tmp));
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "A*\n";
    cout << "Time: " << duration.count() << " microseconds\n";
    print_vector("Path", path);
    cout << "Size: " << path.size() << "\n";
    cout << "Visits: " << visits << "\n";
    cout << "\n";

    return path;
}

vector<char> Graph::id_astar_fun(Node *_s, Node *_t, float _limit)
{
    this->clean();
    int visits = 0;

    vector<char> path;
    map<char, pair<float, vector<char>>> paths;
    pair<float, vector<char>> tmp;

    priority_queue<Node *, vector<Node *>, Compare> pq;
    _s->visit = true;
    pq.push(_s);

    path.push_back(_s->value);
    paths.insert(make_pair(_s->value, make_pair(0, path)));

    Node *current;

    float h;
    float g;

    while (!pq.empty())
    {
        visits++;
        current = pq.top();
        pq.pop();

        if (current == _t)
        {
            path = paths.at(current->value).second;
            break;
        }

        for (auto it = current->lady.begin(); it != current->lady.end(); it++)
        {
            if (!(*it)->visit)
            {
                (*it)->visit = true;
                h = (*it)->distance(_t);
                g = current->distance(*it);

                tmp = paths.at(current->value);
                if (h + (g + tmp.first) < _limit)
                {

                    (*it)->hg = h + g;
                    pq.push(*it);

                    tmp.first += g;
                    tmp.second.push_back((*it)->value);
                    paths.insert(make_pair((*it)->value, tmp));
                }
            }
        }
    }

    cout << "Limit: " << _limit << "\n";
    cout << "Visits: " << visits << "\n";

    return path;
}

vector<char> Graph::id_astar(Node *_s, Node *_t)
{
    vector<char> path;
    float limit = 1.5 * _s->distance(_t);
    float e = 3;

    cout << "IDA*\n";
    auto start = high_resolution_clock::now();

    path = id_astar_fun(_s, _t, limit);
    while (path.back() != _t->value)
    {
        limit += e;
        path = id_astar_fun(_s, _t, limit);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time: " << duration.count() << " microseconds\n";
    print_vector("Path", path);
    cout << "Size: " << path.size() << "\n";
    cout << "\n";

    return path;
}

vector<char> Graph::best_first(Node *_s, Node *_t)
{
    this->clean();
    int visits = 0;

    auto start = high_resolution_clock::now();

    vector<char> path, tmp;
    map<char, vector<char>> paths;

    std::priority_queue<Node *, std::vector<Node *>, Compare> pq;
    _s->visit = true;
    pq.push(_s);

    path.push_back(_s->value);
    paths.insert(make_pair(_s->value, path));

    Node *current;

    float g;

    while (!pq.empty())
    {
        current = pq.top();
        pq.pop();
        visits++;

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
                paths.insert(make_pair((*it)->value, tmp));
            }
        }
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "BF\n";
    cout << "Time: " << duration.count() << " microseconds\n";
    print_vector("Path", path);
    cout << "Size: " << path.size() << "\n";
    cout << "Visits: " << visits << "\n";
    cout << "\n";

    return path;
}

vector<char> Graph::dfs(Node *_s, Node *_t, int _limit)
{
    this->clean();
    int visits = 0;

    vector<char> path, tmp;
    map<char, vector<char>> paths;

    std::stack<Node *> stack_dfs;

    path.push_back(_s->value);
    paths.insert(make_pair(_s->value, path));

    Node *current;

    _s->hg = 0;
    _s->visit = true;
    stack_dfs.push(_s);

    while (!stack_dfs.empty())
    {
        current = stack_dfs.top();
        stack_dfs.pop();
        visits++;

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
                (*it)->hg = (current->hg) + 1;

                if (current->hg < _limit)
                {
                    stack_dfs.push(*it);
                    tmp = paths.at(current->value);
                    tmp.push_back((*it)->value);
                    paths.insert(make_pair((*it)->value, tmp));
                }
            }
        }
    }

    cout << "Limit: " << _limit << "\n";
    cout << "Visits: " << visits << "\n";

    return path;
}

vector<char> Graph::id_dfs(Node *_s, Node *_t)
{
    vector<char> path;
    int limit = this->vnode.size() / 4;

    cout << "IDDFS\n";
    auto start = high_resolution_clock::now();

    path = dfs(_s, _t, limit);
    while (path.back() != _t->value)
    {
        limit++;
        path = dfs(_s, _t, limit);
    }

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);

    cout << "Time: " << duration.count() << " microseconds\n";
    print_vector("Path", path);
    cout << "Size: " << path.size() << "\n";
    cout << "\n";

    return path;
}

#endif