#include "Size.h"

using namespace WinApiWrapper;

Size::Size() : tagSIZE()
{
    cx = 0;
    cy = 0;
}

Size::Size(const int width, const int height) : tagSIZE()
{
    cx = width;
    cy = height;
}

Size::Size(const SIZE& size) : tagSIZE()
{
    cx = size.cx;
    cy = size.cy;
}

Size Size::operator-() const
{
    return {-cx, -cy};
}

Size Size::operator-(const SIZE& s) const
{
    return {cx - s.cx, cy - s.cy};
}

Size Size::operator+(const SIZE& s) const
{
    return {cx + s.cx, cy + s.cy};
}

Size& Size::operator-=(const SIZE& s)
{
    cx -= s.cx;
    cy -= s.cy;
    return *this;
}

Size& Size::operator+=(const SIZE& s)
{
    cx += s.cx;
    cy += s.cy;
    return *this;
}

bool Size::operator==(const SIZE& s) const
{
    return cx == s.cx && cy == s.cy;
}

bool Size::operator!=(const SIZE& s) const
{
    return cx != s.cx || cy != s.cy;
}
