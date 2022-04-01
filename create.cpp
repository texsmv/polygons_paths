#include <iostream>

#include "source/graph_creation.h"

using namespace std;

int main(int argc, char const *argv[])
{
    string arg1(argv[1]);
    GraphInput input = GraphInput(arg1);
    Graph graph = Graph(input);
    graph.saveTxt();
}