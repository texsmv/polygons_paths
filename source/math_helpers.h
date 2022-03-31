#include <tuple>
#include <unordered_map>

using namespace std;
#include <bits/stdc++.h>

typedef pair<float, float> point;
typedef pair<point, point> segment;
typedef unordered_map<string, point> point_map;

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
        // The lines are parallel. This is simplified
        // by returning a pair of FLT_MAX
        return false;
    }
    else
    {
        double x = (b2 * c1 - b1 * c2) / determinant;
        double y = (a1 * c2 - a2 * c1) / determinant;
        // cout << "L1: " << A.first << ", " << A.second << "  -  " << B.first << ", " << B.second << endl;
        // cout << "L2: " << C.first << ", " << C.second << "  -  " << D.first << ", " << D.second << endl;
        // cout << "x: " << x << "y: " << y << endl;

        return onSegment(A, B, make_pair(x, y)) && onSegment(C, D, make_pair(x, y));

        // float min_x, max_x;
        // point point1, point2;

        // if (A.first - B.first != 0)
        // {
        //     cout << "Right" << endl;
        //     point1 = A;
        //     point2 = B;

        //     if (point1.first > point2.first)
        //     {
        //         min_x = point2.first;
        //         max_x = point1.first;
        //     }
        //     else
        //     {
        //         max_x = point2.first;
        //         min_x = point1.first;
        //     }
        // }
        // else
        // {
        //     cout << "Left" << endl;
        //     // point1 = C;
        //     // point2 = D;
        //     if (point1.second > point2.second)
        //     {
        //         min_x = point2.second;
        //         max_x = point1.second;
        //     }
        //     else
        //     {
        //         max_x = point2.second;
        //         min_x = point1.second;
        //     }
        // }

        // // Checking wheter the point is within the
        // // ! Check the > and <
        // if (x > min_x && x < max_x)
        // {
        //     return true;
        // }
        // return false;
    }
}
