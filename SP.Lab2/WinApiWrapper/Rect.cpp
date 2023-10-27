#include "Rect.h"

using namespace WinApiWrapper;

Rect::Rect() : tagRECT()
{
}

Rect::Rect(const RECT& rc) : tagRECT()
{
    left = rc.left;
    top = rc.top;
    right = rc.right;
    bottom = rc.bottom;
}

Rect::Rect(const POINT& p1, const POINT& p2) : tagRECT()
{
    left = p1.x;
    top = p1.y;
    right = p2.x;
    bottom = p2.y;
}

Rect::Rect(const POINT& p1, const int width, const int height) : tagRECT()
{
    left = p1.x;
    top = p1.y;
    right = p1.x + width;
    bottom = p1.y + height;
}

Rect::Rect(const POINT& p1, const SIZE& size) : tagRECT()
{
    left = p1.x;
    top = p1.y;
    right = p1.x + size.cx;
    bottom = p1.y + size.cy;
}

Rect::Rect(const int _left, const int _top, const int _right, const int _bottom) : tagRECT()
{
    left = _left;
    top = _top;
    right = _right;
    bottom = _bottom;
}

bool Rect::operator==(const RECT& r) const
{
    return left == r.left && top == r.top && right == r.right && bottom == r.bottom;
}

bool Rect::operator!=(const RECT& r) const
{
    return left != r.left || top != r.top || right != r.right || bottom != r.bottom;
}

Rect Rect::operator&(const RECT& r) const
{
    return {
        left < r.left ? r.left : left, top < r.top ? r.top : top, right > r.right ? r.right : right,
        bottom > r.bottom ? r.bottom : bottom
    };
}

Rect Rect::operator|(const RECT& r) const
{
    return {
        left < r.left ? left : r.left, top < r.top ? top : r.top, right > r.right ? right : r.right,
        bottom > r.bottom ? bottom : r.bottom
    };
}

int Rect::GetWidth() const
{
    return right - left;
}

int Rect::GetHeight() const
{
    return bottom - top;
}

Size Rect::GetSize() const
{
    return Size(GetWidth(), GetHeight());
}

void Rect::SetSize(const int cx, const int cy)
{
    right = left + cx;
    bottom = top + cy;
}

void Rect::SetSize(const SIZE& size)
{
    right = left + size.cx;
    bottom = top + size.cy;
}

bool Rect::Contains(const POINT& p) const
{
    return (p.x >= left) && (p.x < right) && (p.y >= top) && (p.y < bottom);
}

bool Rect::Contains(const RECT& r) const
{
    return left <= r.left && top <= r.top && right >= r.right && bottom >= r.bottom;
}

bool Rect::IsValid() const
{
    return left < right && top < bottom;
}

bool Rect::Intersects(const RECT& r) const
{
    return left < r.right && right > r.left && top < r.bottom && bottom > r.top;
}

Point Rect::GetLeftTop()
{
    return {left, top};
}

Point Rect::GetLeftBottom()
{
    return {left, bottom};
}

Point Rect::GetRightTop()
{
    return {right, top};
}

Point Rect::GetRightBottom()
{
    return {right, bottom};
}
