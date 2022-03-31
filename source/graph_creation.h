#include <iostream>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
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
    // vertices and their coordinates
    point_map vertices;

    // Defines how the vertices are connected
    vector<string> order;

    vector<segment> edges;

    bool isPointInside(point point)
    {
        segment lineToInf = make_pair(point, make_pair(10000000, point.second));
        int intersectionCount = 0;
        for (int i = 0; i < edges.size(); i++)
        {
            if (doLinesIntersect(edges[i].first, edges[i].second, lineToInf.first, lineToInf.second))
            {
                intersectionCount++;
                cout << edges[i].first.first << " - " << edges[i].first.second << endl;
                cout << edges[i].second.first << " - " << edges[i].second.second << endl;
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

        // cout << "Nro vertices " << vertices.size() << endl;
        // cout << "Nro polygons " << polygons.size() << endl;
        // cout << "Origin " << get<0>(origin) << " - " << get<1>(origin) << endl;
        // cout << "Destination " << get<0>(destination) << " - " << get<1>(destination) << endl;
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
        nodes = {};
        graph = {};

        for (auto kv : vertices)
        {
            nodes.push_back(kv.first);
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
            // cout << nodes[i] << "(" << vertices[nodes[i]].first << "," << vertices[nodes[i]].second << ": ";
            for (int j = 0; j < nodes.size(); j++)
            {
                if (i != j)
                {

                    bool intersected = false;
                    segment seg = make_pair(vertices[nodes[i]], vertices[nodes[j]]);
                    for (int k = 0; k < allSegments.size(); k++)
                    {
                        if (doLinesIntersect(seg.first, seg.second, allSegments[k].first, allSegments[k].second))
                        {
                            // cout << "BINGO!" << endl;
                            intersected = true;
                        }
                    }
                    if (!intersected)
                    {
                        // cout << nodes[j] << " - ";
                        graph[nodes[i]].push_back(nodes[j]);
                    }
                }
            }
            // cout << endl;
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