#pragma once
#include <windows.h>

namespace WinApiWrapper
{
    class Size : public SIZE
    {
    public:
        Size();

        Size(int width, int height);

        explicit Size(const SIZE& size);

        Size operator-() const;

        Size operator-(const SIZE& s) const;

        Size operator+(const SIZE& s) const;

        Size& operator-=(const SIZE& s);

        Size& operator+=(const SIZE& s);

        bool operator==(const SIZE& s) const;

        bool operator!=(const SIZE& s) const;
    };
}
