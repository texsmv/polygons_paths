#include <iostream>

#include "source/graph_search.h"
#include "source/graph_utils.h"

int main(int argc, char const *argv[])
{
    Graph *graph = new Graph("data/real_1.txt");

    Node *source = graph->find('O');
    Node *target = graph->find('D');

    print_vector("A*", graph->a_star(source, target));
    print_vector("BF", graph->best_first(source, target));
    print_vector("IDA*", graph->id_astar(source, target));
    print_vector("IDDFS", graph->id_dfs(source, target));

    delete source;
    delete target;
    delete graph;
    return 0;
}