#include <tuple>
#include <unordered_map>

using namespace std;
#include <bits/stdc++.h>

typedef pair<float, float> point;
typedef pair<point, point> segment;
typedef unordered_map<string, point> point_map;

/// Splits a String given a character
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

/// Checks wether the point  q is inside the segment pr
bool onSegment(point p, point r, point q)
{
    if (q.first == p.first && q.second == p.second)
    {
        return false;
    }

    if (q.first == r.first && q.second == r.second)
    {
        return false;
    }

    if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) &&
        q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second))
        return true;

    return false;
}

// Given
bool doLinesIntersect(point A, point B, point C, point D)
{

    // Line AB represented as a1x + b1y = c1
    double a1 = B.second - A.second;
    double b1 = A.first - B.first;
    double c1 = a1 * (A.first) + b1 * (A.second);

    // Line CD represented as a2x + b2y = c2
    double a2 = D.second - C.second;
    double b2 = C.first - D.first;
    double c2 = a2 * (C.first) + b2 * (C.second);

    double determinant = a1 * b2 - a2 * b1;

    point p;
    if (determinant == 0)
    {
        // Case when the lines are parallel
        return false;
    }
    else
    {
        double x = (b2 * c1 - b1 * c2) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;

        //
        return onSegment(A, B, make_pair(x, y)) && onSegment(C, D, make_pair(x, y));
    }
}
