#pragma once
#include <iostream>
using namespace std;
class Point
{
    size_t x;
    size_t y;

public:
    Point();
    Point(size_t x, size_t y);
    size_t getX() const;
    size_t getY() const;
    friend istream & operator >> (istream &in,  Point &p);
    static Point get_point(const string& text);
};
