#ifndef _GRAPH_UTILS_H_
#define _GRAPH_UTILS_H_

#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::cout;
using std::string;
using std::stringstream;
using std::vector;

vector<string>
split(const string &s, char delim)
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

#endif