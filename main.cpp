#include <iostream>

#include "source/graph_creation.h"

using namespace std;

int main()
{
    GraphInput input = GraphInput("data/input_2.txt");
    Graph graph = Graph(input);
    graph.saveTxt();
}