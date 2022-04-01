#include <iostream>

#include "source/graph_creation.h"

using namespace std;

int main()
{
    GraphInput input = GraphInput("data/input_2.txt");
    Graph graph = Graph(input);
    graph.saveTxt();

    // point p1 = make_pair(1, 1);
    // point p2 = make_pair(1, 2);
    // point q1 = make_pair(10, 1);
    // point q2 = make_pair(10, 2);

    point p1 = make_pair(10, 0);
    point p2 = make_pair(0, 0);
    point q1 = make_pair(0, 10);
    point q2 = make_pair(10, 10);

    // point p1 = make_pair(-5, -5);
    // point p2 = make_pair(1, 1);
    // point q1 = make_pair(0, 0);
    // point q2 = make_pair(10, 10);

    // bool intersect = doLinesIntersect(p1, q1, p2, q2);

    // cout << intersect << endl;

    // point p = make_pair(5, 3);

    // for (int i = 0; i < input.polygons.size(); i++)
    // {
    //     cout << input.polygons[i].order[0] << input.polygons[i].order[1] << input.polygons[i].order[2] << endl;

    //     cout << input.polygons[i].isPointInside(p) << endl;
    // }
}