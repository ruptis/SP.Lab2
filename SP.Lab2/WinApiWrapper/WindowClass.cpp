#include "WindowClass.h"

using namespace WinApiWrapper;

bool WindowClass::IsRegistered() const
{
    return _className[0] != 0;
}

WindowClass::operator const wchar_t*() const
{
    return _className;
}

WindowClass::WindowClass(const HINSTANCE hInstance, const WNDPROC wndProc, const UINT style, const int cbClsExtra,
                         const int cbWndExtra, const HICON hIcon,
                         const HCURSOR hCursor, const HBRUSH hbrBackground, const LPCTSTR lpszMenuName)
{
    Register(hInstance, wndProc, style, cbClsExtra, cbWndExtra, hIcon, hCursor, hbrBackground, lpszMenuName);
}

void WindowClass::Register(const HINSTANCE hInstance, const WNDPROC wndProc, const UINT style, const int cbClsExtra,
                           const int cbWndExtra, const HICON hIcon,
                           const HCURSOR hCursor, const HBRUSH hbrBackground, const LPCWSTR lpszMenuName)
{
    static int cls_index = 0;
    cls_index++;
    wsprintf(_className, L"WindowClass%d", cls_index);
    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = style;
    wcex.lpfnWndProc = wndProc;
    wcex.cbClsExtra = cbClsExtra;
    wcex.cbWndExtra = cbWndExtra;
    wcex.hInstance = hInstance;
    wcex.hIcon = hIcon;
    wcex.hCursor = hCursor;
    wcex.hbrBackground = hbrBackground;
    wcex.lpszMenuName = lpszMenuName;
    wcex.lpszClassName = _className;
    wcex.hIconSm = hIcon;

    if (RegisterClassEx(&wcex) == 0)
        _className[0] = 0;
}
