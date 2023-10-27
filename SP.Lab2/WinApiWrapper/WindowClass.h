#pragma once
#include <windows.h>

namespace WinApiWrapper
{
    class WindowClass
    {
    public:
        explicit WindowClass(HINSTANCE hInstance,
                             UINT style = CS_HREDRAW | CS_VREDRAW,
                             int cbClsExtra = 0,
                             int cbWndExtra = 0,
                             HICON hIcon = LoadIcon(nullptr, IDI_APPLICATION),
                             HCURSOR hCursor = LoadCursor(nullptr, IDC_ARROW),
                             HBRUSH hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
                             LPCWSTR lpszMenuName = nullptr);
        explicit WindowClass(HINSTANCE hInstance,
                             HICON hIcon,
                             HBRUSH hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
                             LPCWSTR lpszMenuName = nullptr,
                             UINT style = CS_HREDRAW | CS_VREDRAW,
                             HCURSOR hCursor = LoadCursor(nullptr, IDC_ARROW));

        [[nodiscard]] bool IsRegistered() const;

        explicit operator LPCWSTR() const;

    protected:
        WindowClass(HINSTANCE hInstance, WNDPROC wndProc, UINT style, int cbClsExtra, int cbWndExtra, HICON hIcon,
                    HCURSOR hCursor, HBRUSH hbrBackground, LPCWSTR lpszMenuName);

    private:
        TCHAR _className[64]{};

        void Register(HINSTANCE hInstance, WNDPROC wndProc, UINT style, int cbClsExtra, int cbWndExtra, HICON hIcon,
                      HCURSOR hCursor, HBRUSH hbrBackground, LPCWSTR lpszMenuName);
    };
}
