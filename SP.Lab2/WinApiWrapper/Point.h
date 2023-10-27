#pragma once
#include <windows.h>

namespace WinApiWrapper
{
    class Point : public POINT
    {
    public:
        Point();

        Point(int _x, int _y);

        explicit Point(const POINT& pt);

        Point operator+(const POINT& p) const;

        Point operator-(const POINT& p) const;

        Point operator-() const;

        Point& operator+=(const POINT& p);

        Point& operator-=(const POINT& p);

        bool operator==(const POINT& p) const;

        bool operator!=(const POINT& p) const;
    };
}
