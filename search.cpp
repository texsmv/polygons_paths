#include <iostream>

#include "source/graph_search.h"

int main(int argc, char const *argv[])
{
    Graph *graph = new Graph("data/graph_1.txt");

    Node *source = graph->find('O');
    Node *target = graph->find('D');

    graph->a_star(source, target);
    graph->id_astar(source, target);
    graph->best_first(source, target);
    graph->id_dfs(source, target);

    delete source;
    delete target;
    delete graph;
    return 0;
}