#include "Point.h"

using namespace WinApiWrapper;

Point::Point() : tagPOINT()
{
    x = 0;
    y = 0;
}

Point::Point(const int _x, const int _y) : tagPOINT()
{
    x = _x;
    y = _y;
}

Point::Point(const POINT& pt) : tagPOINT()
{
    x = pt.x;
    y = pt.y;
}

Point Point::operator+(const POINT& p) const
{
    return {x + p.x, y + p.y};
}

Point Point::operator-(const POINT& p) const
{
    return {x - p.x, y - p.y};
}

Point Point::operator-() const
{
    return {-x, -y};
}

Point& Point::operator+=(const POINT& p)
{
    x += p.x;
    y += p.y;
    return *this;
}

Point& Point::operator-=(const POINT& p)
{
    x -= p.x;
    y -= p.y;
    return *this;
}

bool Point::operator==(const POINT& p) const
{
    return x == p.x && y == p.y;
}

bool Point::operator!=(const POINT& p) const
{
    return x != p.x || y != p.y;
}
