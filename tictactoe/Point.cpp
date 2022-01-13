#include "Point.h"
#include "Utility.h"
//wczyttywanie wybranego punktu
Point::Point()
{
    x = 0;
    y = 0;
}

Point::Point(size_t x, size_t y)
{
this->x = x;
this->y = y;
}

size_t Point::getX() const {return x;}
size_t Point::getY() const {return y;}

//wczytywanie punktu z klawiatury
istream & operator >> (istream &in, Point &p)
{
    in >> p.x >> p.y;
    return in;
}

Point Point::get_point(const string& text)
{
    Point p;
    while (true)
    {
        cout << text;
        cin >> p;
        if (!cin.fail())
        {
            return p;
        }
        CLEAR_CIN
    }
}
