#include <iostream>

#include "source/graph_search.h"

using std::cout;
using std::string;
using std::vector;

template <typename T>
void print_vector(string name, vector<T> _vector)
{
    cout << name << " : ";
    for (unsigned i = 0; i < _vector.size(); i++)
    {
        cout << _vector[i] << " ";
    }
    cout << "\n";
}

int main(int argc, char const *argv[])
{
    Graph *graph = new Graph();
    bool dir = true;

    graph->insert_node('A', 1, 5);
    graph->insert_node('B', 5, 10);
    graph->insert_node('C', 10, 15);
    graph->insert_node('D', 15, 9);
    graph->insert_node('E', 5, 5);
    graph->insert_node('F', 10, 10);
    graph->insert_node('G', 5, 0);
    graph->insert_node('H', 10, 4);

    graph->insert_edge('A', 'B', dir);
    graph->insert_edge('A', 'E', dir);
    graph->insert_edge('A', 'G', dir);
    graph->insert_edge('B', 'C', dir);
    graph->insert_edge('B', 'F', dir);
    graph->insert_edge('B', 'H', dir);
    graph->insert_edge('G', 'H', dir);
    graph->insert_edge('C', 'D', dir);
    graph->insert_edge('F', 'D', dir);
    graph->insert_edge('H', 'D', dir);

    Node *source = graph->find('A');
    Node *target = graph->find('H');

    print_vector("A*", graph->a_asterisk(source, target));
    print_vector("BF", graph->best_first(source, target));

    delete source;
    delete target;
    delete graph;
    return 0;
}