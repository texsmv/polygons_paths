#include <iostream>

#include "source/graph_search.h"

using std::cout;

int main(int argc, char const *argv[])
{
    Graph *graph = new Graph();

    graph->insert_node('A', 1, 5);
    graph->insert_node('B', 5, 10);
    graph->insert_node('C', 10, 15);
    graph->insert_node('D', 15, 9);
    graph->insert_node('E', 5, 5);
    graph->insert_node('F', 10, 10);
    graph->insert_node('G', 5, 0);
    graph->insert_node('H', 10, 4);

    Node *source = graph->find('A');
    Node *target = graph->find('H');

    graph->a_asterisk(source, target);

    delete source;
    delete target;
    delete graph;

    cout << "Hi\n";
}