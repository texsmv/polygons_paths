#include <iostream>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

typedef tuple<double, double> point;
typedef unordered_map<string, point> point_map;

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
    }
    // vertices and their coordinates
    point_map vertices;

    // Defines how the vertices are connected
    vector<string> order;
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

        cout << "Nro vertices " << vertices.size() << endl;
        cout << "Nro polygons " << polygons.size() << endl;
        cout << "Origin " << get<0>(origin) << " - " << get<1>(origin) << endl;
        cout << "Destination " << get<0>(destination) << " - " << get<1>(destination) << endl;
    }

    vector<Polygon> polygons;
    point origin;
    point destination;
};

class Graph
{
    point_map vertices;
    map<string, vector<string>> graph;
};