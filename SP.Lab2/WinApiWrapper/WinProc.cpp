#include <iostream>

#include "WindowClass.h"
#include <windows.h>

#include "Utils.h"
#include "Window.h"

namespace WinApiWrapper
{
    inline LRESULT CALLBACK WndProc(const HWND hWnd, const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
    {
        auto window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        bool def = true;
        if (window == nullptr || static_cast<HWND>(*window) != hWnd)
        {
            if (uMsg == WM_NCCREATE)
            {
                const auto lpCreate = reinterpret_cast<LPCREATESTRUCT>(lParam);
                const auto* pass = static_cast<PassLPARAM*>(lpCreate->lpCreateParams);

                if (pass != nullptr)
                {
                    window = static_cast<Window*>(pass->pWindow);
                    if (window != nullptr)
                    {
                        *pass->phwnd = hWnd;
                        lpCreate->lpCreateParams = pass->lpParam;
                        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
                        def = false;
                    }
                }
            }
        }
        else
        {
            def = false;
        }
        if (def) return DefWindowProc(hWnd, uMsg, wParam, lParam);
        switch (uMsg)
        {
        case WM_NCDESTROY:
            window->HandleMessage(uMsg, wParam, lParam);
            if (window->IsCreated())
                window->Destroy();
            return 0;
        case WM_CREATE:
            return window->OnCreate(reinterpret_cast<LPCREATESTRUCT>(lParam)) ? 0 : -1;
        case WM_DESTROY:
            window->OnDestroy();
            return 0;
        case WM_CLOSE:
            window->OnClose();
            return 0;
        case WM_ACTIVATEAPP:
            window->OnActivateApp(wParam != 0);
            return 0;
        case WM_COMMAND:
            window->OnCommand(LOWORD(wParam), HIWORD(wParam), reinterpret_cast<HWND>(lParam));
            return 0;
        case WM_NOTIFY:
            return window->OnNotify(static_cast<int>(wParam), reinterpret_cast<LPNMHDR>(lParam));
        case WM_PAINT:
            window->OnPaint();
            return 0;
        case WM_SIZE:
            window->OnSize(static_cast<int>(wParam), Size(LOWORD(lParam), HIWORD(lParam)));
            return 0;
        case WM_ENTERSIZEMOVE:
            window->OnEnterSizeMove();
            return 0;
        case WM_EXITSIZEMOVE:
            window->OnExitSizeMove();
            return 0;
        case WM_MOUSEMOVE:
            window->OnMouseMove(LParam2Point(lParam), static_cast<int>(wParam));
            return FALSE;
        case WM_LBUTTONDOWN:
            window->OnMouseDown(LParam2Point(lParam), static_cast<int>(wParam), Window::LeftButton);
            return FALSE;
        case WM_LBUTTONUP:
            window->OnMouseUp(LParam2Point(lParam), static_cast<int>(wParam), Window::LeftButton);
            return FALSE;
        case WM_RBUTTONDOWN:
            window->OnMouseDown(LParam2Point(lParam), static_cast<int>(wParam), Window::RightButton);
            return FALSE;
        case WM_RBUTTONUP:
            window->OnMouseUp(LParam2Point(lParam), static_cast<int>(wParam), Window::RightButton);
            return FALSE;
        case WM_MBUTTONDOWN:
            window->OnMouseDown(LParam2Point(lParam), static_cast<int>(wParam), Window::MiddleButton);
            return FALSE;
        case WM_MBUTTONUP:
            window->OnMouseUp(LParam2Point(lParam), static_cast<int>(wParam), Window::MiddleButton);
            return FALSE;
        case WM_LBUTTONDBLCLK:
            window->OnMouseDoubleClick(LParam2Point(lParam), static_cast<int>(wParam), Window::LeftButton);
            return FALSE;
        case WM_RBUTTONDBLCLK:
            window->OnMouseDoubleClick(LParam2Point(lParam), static_cast<int>(wParam), Window::RightButton);
            return FALSE;
        case WM_MBUTTONDBLCLK:
            window->OnMouseDoubleClick(LParam2Point(lParam), static_cast<int>(wParam), Window::MiddleButton);
            return FALSE;
        case WM_MOUSEWHEEL:
            window->OnMouseWheel(LParam2Point(lParam), static_cast<int>(wParam), WParam2Float(wParam));
        case WM_KEYDOWN:
            window->OnKeyDown(static_cast<int>(wParam), static_cast<int>(lParam));
            return FALSE;
        case WM_KEYUP:
            window->OnKeyUp(static_cast<int>(wParam), static_cast<int>(lParam));
            return FALSE;
        default:
            return window->HandleMessage(uMsg, wParam, lParam);
        }
    }


    WindowClass::WindowClass(const HINSTANCE hInstance, const UINT style, const int cbClsExtra, const int cbWndExtra,
                             const HICON hIcon, const HCURSOR hCursor,
                             const HBRUSH hbrBackground, const LPCWSTR lpszMenuName)
    {
        Register(hInstance, WndProc, style, cbClsExtra, cbWndExtra, hIcon, hCursor, hbrBackground, lpszMenuName);
    }

    WindowClass::WindowClass(const HINSTANCE hInstance, const HICON hIcon, const HBRUSH hbrBackground,
                             const LPCWSTR lpszMenuName,
                             const UINT style, const HCURSOR hCursor)
    {
        Register(hInstance, WndProc, style, 0, 0, hIcon, hCursor, hbrBackground, lpszMenuName);
    }
}
