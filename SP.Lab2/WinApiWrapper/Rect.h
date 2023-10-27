#pragma once
#include <windows.h>

#include "Point.h"
#include "Size.h"

namespace WinApiWrapper
{
    class Rect : public RECT
    {
    public:
        Rect();

        explicit Rect(const RECT& rc);

        Rect(const POINT& p1, const POINT& p2);

        Rect(const POINT& p1, int width, int height);

        Rect(const POINT& p1, const SIZE& size);

        Rect(int _left, int _top, int _right, int _bottom);

        bool operator==(const RECT& r) const;

        bool operator!=(const RECT& r) const;

        Rect operator&(const RECT& r) const;

        Rect operator|(const RECT& r) const;

        [[nodiscard]] int GetWidth() const;

        [[nodiscard]] int GetHeight() const;

        [[nodiscard]] Size GetSize() const;

        void SetSize(int cx, int cy);

        void SetSize(const SIZE& size);

        [[nodiscard]] bool Contains(const POINT& p) const;

        [[nodiscard]] bool Contains(const RECT& r) const;

        [[nodiscard]] bool IsValid() const;

        [[nodiscard]] bool Intersects(const RECT& r) const;

        [[nodiscard]] Point GetLeftTop();

        Point GetLeftBottom();

        Point GetRightTop();

        Point GetRightBottom();
    };
}
