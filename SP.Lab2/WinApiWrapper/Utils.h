#pragma once
#include <d2d1.h>
#include <windows.h>

#include "Point.h"
#include "Size.h"
#include "Rect.h"
#include "Window.h"

namespace WinApiWrapper
{
    struct PassLPARAM
    {
        LPVOID lpParam{};
        Window* pWindow{};
        HWND* phwnd{};
    };

    Point LParam2Point(LPARAM lParam);

    Rect ToRect(const Size& size);

    float WParam2Float(WPARAM wParam);

    ID2D1Bitmap* LoadImageFromFile(const std::wstring& path, ID2D1RenderTarget& renderTarget);
}
