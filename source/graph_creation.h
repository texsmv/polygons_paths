#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

#include "math_helpers.h"

using namespace std;

vector<string> split(const string &s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}

class Polygon
{
public:
    Polygon(point_map vertices, vector<string> order)
    {
        this->vertices = vertices;
        this->order = order;
        edges = {};
        for (int i = 0; i < order.size() - 1; i++)
        {
            edges.push_back(make_pair(vertices[order[i]], vertices[order[i + 1]]));
        }
    }

    vector<string> polygonVertices()
    {
        return vector<string>(order.begin(), order.end() - 1);
    }

    bool hasNode(string node)
    {
        return find(order.begin(), order.end(), node) != order.end();
    }

    // vertices and their coordinates
    point_map vertices;

    // Defines how the vertices are connected
    vector<string> order;

    vector<segment> edges;

    bool isConnected(string nodeA, string nodeB)
    {
        vector<string> polVertices = polygonVertices();
        for (int i = 0; i < polVertices.size(); i++)
        {
            if (polVertices[i] == nodeA)
            {
                if (i == 0)
                {
                    return polVertices[polVertices.size() - 1] == nodeB || polVertices[1] == nodeB;
                }
                else if (i == polVertices.size() - 1)
                {
                    return polVertices[polVertices.size() - 2] == nodeB || polVertices[0] == nodeB;
                }
                else
                {
                    return polVertices[i - 1] == nodeB || polVertices[i + 1] == nodeB;
                }
            }
        }
        return false;
    }

    bool isPointInside(point point)
    {
        segment lineToInf = make_pair(point, make_pair(10000000, point.second));
        int intersectionCount = 0;
        for (int i = 0; i < edges.size(); i++)
        {
            if (doLinesIntersect(edges[i].first, edges[i].second, lineToInf.first, lineToInf.second))
            {
                intersectionCount++;
                // cout << edges[i].first.first << " - " << edges[i].first.second << endl;
                // cout << edges[i].second.first << " - " << edges[i].second.second << endl;

                // cout << edges[i].second << endl;
            }
        }
        // cout << intersectionCount << endl;

        return !(intersectionCount % 2 == 0);
    }
};

class GraphInput
{
public:
    GraphInput(string path)
    {
        // Define the vertices
        point_map vertices = {};
        vector<vector<string>> polygons_order = {};

        ifstream file(path);
        string str;
        bool vertices_read = false;
        bool polygons_read = false;
        bool origin_read = false;

        while (getline(file, str))
        {
            if (!vertices_read)
            {
                if (str.empty())
                {
                    vertices_read = true;
                }
                else
                {
                    vector<string> tokens = split(str, ' ');
                    vertices.insert({tokens[0], {stof(tokens[1]), stof(tokens[2])}});
                }
            }
            else if (!polygons_read)
            {
                if (str.empty())
                {
                    polygons_read = true;
                }
                else
                {
                    vector<string> tokens = split(str, ' ');
                    vector<string> polygon = {tokens.begin() + 1, tokens.end()};
                    polygons_order.push_back(polygon);
                }
            }
            else if (!origin_read)
            {

                vector<string> tokens = split(str, ' ');
                origin = {stof(tokens[0]), stof(tokens[1])};
                origin_read = true;
            }
            else
            {
                vector<string> tokens = split(str, ' ');
                destination = {stof(tokens[0]), stof(tokens[1])};
            }
        }

        this->polygons = {};
        for (int i = 0; i < polygons_order.size(); i++)
        {
            this->polygons.push_back(Polygon(vertices, polygons_order[i]));
        }
    }

    vector<segment> getAllSegments()
    {
        vector<segment> allSegments = {};
        for (int i = 0; i < polygons.size(); i++)
        {
            allSegments.insert(allSegments.end(), polygons[i].edges.begin(), polygons[i].edges.end());
        }
        return allSegments;
    }
    vector<Polygon> polygons;

    point origin;
    point destination;
};

class Graph
{
public:
    point_map vertices;
    vector<string> nodes;
    map<string, vector<string>> graph;
    Graph(GraphInput input)
    {
        vertices = input.polygons[0].vertices;
        vector<segment> allSegments = input.getAllSegments();
        map<string, Polygon *> polygonsMap = {};
        nodes = {};
        graph = {};

        // for (auto kv : vertices)
        // {
        //     nodes.push_back(kv.first);
        // }

        for (int i = 0; i < input.polygons.size(); i++)
        {
            vector<string> pnodes = input.polygons[i].polygonVertices();
            for (int j = 0; j < pnodes.size(); j++)
            {
                nodes.push_back(pnodes[j]);
                polygonsMap[pnodes[j]] = &(input.polygons[i]);
            }
        }

        nodes.push_back("O");
        nodes.push_back("D");

        vertices.insert({"O", input.origin});
        vertices.insert({"D", input.destination});

        // cout << "Nro segments " << allSegments.size() << endl;
        // cout << "Nro nodes " << nodes.size() << endl;

        for (int i = 0; i < nodes.size(); i++)
        {
            graph[nodes[i]] = {};
            // cout << i << endl;
            // cout << nodes[i] << "(" << vertices[nodes[i]].first << "," << vertices[nodes[i]].second << ": ";
            for (int j = 0; j < nodes.size(); j++)
            {
                // cout << j << endl;
                if (i != j)
                {
                    Polygon *polygon = polygonsMap[nodes[i]];
                    // cout << polygon << endl;
                    if (polygon != 0 && polygon->hasNode(nodes[j]))
                    {
                        bool intersected = false;
                        segment seg = make_pair(vertices[nodes[i]], vertices[nodes[j]]);
                        vector<segment> polygonSegments = polygon->edges;
                        for (int k = 0; k < polygonSegments.size(); k++)
                        {
                            if (doLinesIntersect(seg.first, seg.second, allSegments[k].first, allSegments[k].second))
                            {
                                intersected = true;
                            }
                        }
                        // if (nodes[i] == "c" && nodes[j] == "a")
                        // {
                        //     cout << "Intersected: " << intersected << endl;
                        // }
                        if (!intersected)
                        {
                            if (nodes[i] == "c" && nodes[j] == "a")
                            {
                                // cout << "isConnected: " << polygon->isConnected(nodes[i], nodes[j]) << endl;
                                // cout << "isInside: " << !polygon->isPointInside(make_pair((vertices[nodes[i]].first + vertices[nodes[j]].first) / 2, (vertices[nodes[i]].second + vertices[nodes[j]].second) / 2)) << endl;
                            }
                            if (polygon->isConnected(nodes[i], nodes[j]) || !polygon->isPointInside(make_pair((vertices[nodes[i]].first + vertices[nodes[j]].first) / 2, (vertices[nodes[i]].second + vertices[nodes[j]].second) / 2)))
                            {
                                graph[nodes[i]].push_back(nodes[j]);
                            }
                        }
                    }
                    else
                    {

                        bool intersected = false;
                        segment seg = make_pair(vertices[nodes[i]], vertices[nodes[j]]);
                        for (int k = 0; k < allSegments.size(); k++)
                        {
                            if (doLinesIntersect(seg.first, seg.second, allSegments[k].first, allSegments[k].second))
                            {
                                intersected = true;
                            }
                        }
                        if (!intersected)
                        {
                            graph[nodes[i]].push_back(nodes[j]);
                        }
                    }
                }
            }
        }
    }

    void saveTxt()
    {
        // Print all nodes
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << nodes[i] << " " << vertices[nodes[i]].first << " " << vertices[nodes[i]].second << endl;
        }
        cout << endl;

        // Print all edges
        for (int i = 0; i < nodes.size(); i++)
        {
            cout << nodes[i] << ": ";
            vector<string> edges = graph[nodes[i]];
            for (int j = 0; j < edges.size(); j++)
            {
                cout << edges[j] << " ";
            }
            cout << endl;
        }
    }
};