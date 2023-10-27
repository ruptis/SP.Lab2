#include "Window.h"

#include "Utils.h"

using namespace WinApiWrapper;

Window::Window(const HINSTANCE hInstance) : _hInstance(hInstance)
{
}

Window::~Window()
{
    _isCreated = false;
    if (_hWnd != nullptr)
        SetWindowLongPtr(_hWnd, GWLP_USERDATA, 0);
    _hWnd = nullptr;
}

void Window::SetCreated(const HWND hwnd)
{
    _hWnd = hwnd;
    _isCreated = true;
}

bool Window::Create(const LPCWSTR lpszWindowName, const WindowClass& wndClass,
                    const RECT& rc, const HWND hWndParent, const HMENU hMenu, const DWORD dwExStyle,
                    const LPVOID lpParam, const DWORD dwStyle)
{
    PassLPARAM pass = {lpParam, this, &_hWnd};
    if (_hWnd != nullptr)
        return true;
    const HWND hwndTemp = CreateWindowEx(dwExStyle, static_cast<LPCWSTR>(wndClass), lpszWindowName, dwStyle,
                                         rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
                                         hWndParent, hMenu, _hInstance, &pass);
    if (hwndTemp != nullptr)
    {
        SetCreated(hwndTemp);
    }
    return _isCreated;
}

bool Window::Create(const LPCWSTR lpszWindowName, const RECT& rc, const HWND hWndParent, const HMENU hMenu,
                    const DWORD dwExStyle, const LPVOID lpParam, const DWORD dwStyle)
{
    return Create(lpszWindowName, WindowClass(_hInstance), rc, hWndParent, hMenu, dwExStyle, lpParam, dwStyle);
}

bool Window::Create(const LPCWSTR lpszWindowName, const DWORD dwExStyle, const DWORD dwStyle)
{
    return Create(lpszWindowName, WindowClass(_hInstance), Rect(Point(CW_USEDEFAULT, 0), CW_USEDEFAULT, 0), nullptr,
                  nullptr, dwExStyle, nullptr, dwStyle);
}

bool Window::IsCreated() const
{
    return _isCreated;
}

bool Window::Show(const int nCmdShow) const
{
    return ShowWindow(_hWnd, nCmdShow) != FALSE;
}

bool Window::ShowAsync(const int nCmdShow) const
{
    return ShowWindowAsync(_hWnd, nCmdShow) != FALSE;
}

bool Window::Update() const
{
    return UpdateWindow(_hWnd) != FALSE;
}

bool Window::Redraw(const UINT flags) const
{
    return RedrawWindow(_hWnd, nullptr, nullptr, flags) != FALSE;
}

bool Window::Redraw(const RECT& rcUpdate, const UINT flags) const
{
    return RedrawWindow(_hWnd, &rcUpdate, nullptr, flags) != FALSE;
}

bool Window::Redraw(const HRGN hrgnUpdate, const UINT flags) const
{
    return RedrawWindow(_hWnd, nullptr, hrgnUpdate, flags) != FALSE;
}

bool Window::Invalidate(const bool bErase) const
{
    return ::InvalidateRect(_hWnd, nullptr, bErase) != FALSE;
}

bool Window::InvalidateRect(const RECT& rc, const bool bErase) const
{
    return ::InvalidateRect(_hWnd, &rc, bErase) != FALSE;
}

bool Window::InvalidateRgn(const HRGN hrgn, const bool bErase) const
{
    return ::InvalidateRgn(_hWnd, hrgn, bErase) != FALSE;
}

bool Window::ValidateRect(const RECT& rc) const
{
    return ::ValidateRect(_hWnd, &rc) != FALSE;
}

bool Window::ValidateRgn(const HRGN hrgn) const
{
    return ::ValidateRgn(_hWnd, hrgn) != FALSE;
}

bool Window::Destroy()
{
    if (DestroyWindow(_hWnd))
    {
        _hWnd = nullptr;
        return true;
    }
    return false;
}

bool Window::Close() const
{
    return CloseWindow(_hWnd) != FALSE;
}

bool Window::Enable(const bool bEnable) const
{
    return EnableWindow(_hWnd, bEnable) != FALSE;
}

bool Window::IsEnabled() const
{
    return IsWindowEnabled(_hWnd) != FALSE;
}

bool Window::GetClientRect(RECT* lpRect) const
{
    return ::GetClientRect(_hWnd, lpRect) != FALSE;
}

Rect Window::GetClientRect() const
{
    Rect rc(0, 0, 0, 0);
    GetClientRect(&rc);
    return rc;
}

bool Window::GetWindowRect(RECT* lpRect) const
{
    return ::GetWindowRect(_hWnd, lpRect) != FALSE;
}

Rect Window::GetWindowRect() const
{
    Rect rc(0, 0, 0, 0);
    GetWindowRect(&rc);
    return rc;
}

bool Window::IsChild(const HWND hwndParent) const
{
    return ::IsChild(hwndParent, _hWnd) != FALSE;
}

bool Window::IsWindow() const
{
    return _hWnd != nullptr && ::IsWindow(_hWnd) != FALSE;
}

bool Window::IsVisible() const
{
    return IsWindowVisible(_hWnd) != FALSE;
}

bool Window::IsZoomed() const
{
    return ::IsZoomed(_hWnd) != FALSE;
}

bool Window::GetPlacement(WINDOWPLACEMENT* lpwndpl) const
{
    return GetWindowPlacement(_hWnd, lpwndpl) != FALSE;
}

bool Window::SetPlacement(const WINDOWPLACEMENT* lpwndpl) const
{
    return SetWindowPlacement(_hWnd, lpwndpl) != FALSE;
}

std::string Window::GetText() const
{
    std::string s;
    const int len = GetWindowTextLength(_hWnd);
    if (len > 0)
    {
        s.resize(len + 1);
        GetWindowText(_hWnd, LPWSTR(s.c_str()), len + 1);
        s.resize(len);
    }
    return s;
}

bool Window::Move(const POINT& pt, const int width, const int height, const bool bRepaint) const
{
    return MoveWindow(_hWnd, pt.x, pt.y, width, height, bRepaint) != FALSE;
}

bool Window::Move(const RECT& rc, const bool bRepaint) const
{
    return MoveWindow(_hWnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, bRepaint) != FALSE;
}

bool Window::SetPos(const POINT& pt) const
{
    return SetWindowPos(_hWnd, nullptr, pt.x, pt.y, 0, 0,
                        SWP_ASYNCWINDOWPOS | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSIZE | SWP_NOZORDER) !=
        FALSE;
}

bool Window::SetPos(const int width, const int height) const
{
    return SetWindowPos(_hWnd, nullptr, 0, 0, width, height,
                        SWP_ASYNCWINDOWPOS | SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER) !=
        FALSE;
}

bool Window::SetPos(const RECT& rc) const
{
    return SetWindowPos(_hWnd, nullptr, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
                        SWP_ASYNCWINDOWPOS | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER) != FALSE;
}

bool Window::SetPos(const HWND hwndAfter) const
{
    return SetWindowPos(_hWnd, hwndAfter, 0, 0, 0, 0, SWP_ASYNCWINDOWPOS | SWP_NOMOVE | SWP_NOSIZE) != FALSE;
}

bool Window::SetPos(const HWND hwndAfter, const RECT& rc, const UINT uFlags) const
{
    return SetWindowPos(_hWnd, hwndAfter, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, uFlags) != FALSE;
}

bool Window::SetScrollPos(const int nBar, const int nPos, const bool bRedraw) const
{
    return ::SetScrollPos(_hWnd, nBar, nPos, bRedraw) != FALSE;
}

int Window::GetScrollPos(const int nBar) const
{
    return ::GetScrollPos(_hWnd, nBar);
}

bool Window::PostMessageW(const UINT uMsg, const WPARAM wParam, const LPARAM lParam) const
{
    return ::PostMessage(_hWnd, uMsg, wParam, lParam) != FALSE;
}

int Window::SendMessageW(const UINT uMsg, const WPARAM wParam, const LPARAM lParam) const
{
    return static_cast<int>(::SendMessage(_hWnd, uMsg, wParam, lParam));
}

bool Window::SendMessageTimeoutW(const UINT uMsg, const WPARAM wParam, const LPARAM lParam, const UINT uFlags,
                                 const UINT uTimeout, const PDWORD_PTR lpdwResult) const
{
    return ::SendMessageTimeout(_hWnd, uMsg, wParam, lParam, uFlags, uTimeout, lpdwResult) != FALSE;
}

int Window::MessageBoxW(const LPCTSTR lpText, const LPCTSTR lpCaption, const UINT uType) const
{
    return ::MessageBox(_hWnd, lpText, lpCaption, uType);
}

void Window::BeginPaint(const LPPAINTSTRUCT lpPaint) const
{
    ::BeginPaint(_hWnd, lpPaint);
}

void Window::EndPaint(const LPPAINTSTRUCT lpPaint) const
{
    ::EndPaint(_hWnd, lpPaint);
}

Window::operator HWND__*() const
{
    return _hWnd;
}

HWND Window::GetHandle() const
{
    return _hWnd;
}

int Window::HandleMessage(const UINT uMsg, const WPARAM wParam, const LPARAM lParam)
{
    return static_cast<int>(DefWindowProc(_hWnd, uMsg, wParam, lParam));
}

bool Window::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    return true;
}

void Window::OnClose()
{
    DefWindowProc(_hWnd, WM_CLOSE, 0, 0);
}

void Window::OnDestroy()
{
}

void Window::OnActivateApp(bool isActive)
{
}

void Window::OnCommand(int nIdentifier, int nNotifyCode, HWND hwndControl)
{
}

int Window::OnNotify(const int nIdentifier, LPNMHDR pnmh)
{
    return static_cast<int>(DefWindowProc(_hWnd, WM_NOTIFY, nIdentifier, reinterpret_cast<LPARAM>(pnmh)));
}

void Window::OnPaint()
{
    DefWindowProc(_hWnd, WM_PAINT, 0, 0);
}

void Window::OnSize(const int sizing, const Size new_size)
{
    DefWindowProc(_hWnd, WM_SIZE, sizing, MAKELPARAM(new_size.cx, new_size.cy));
}

void Window::OnEnterSizeMove()
{
}

void Window::OnExitSizeMove()
{
}

void Window::OnMouseMove(const Point point, const int keys)
{
    DefWindowProc(_hWnd, WM_MOUSEMOVE, keys, MAKELPARAM(point.x, point.y));
}

void Window::OnMouseDown(const Point point, const int keys, const MouseButtons button)
{
    DefWindowProc(
        _hWnd, button == LeftButton ? WM_LBUTTONDOWN : (button == RightButton ? WM_RBUTTONDOWN : WM_MBUTTONDOWN), keys,
        MAKELPARAM(point.x, point.y));
}

void Window::OnMouseUp(const Point point, const int keys, const MouseButtons button)
{
    DefWindowProc(_hWnd, button == LeftButton ? WM_LBUTTONUP : (button == RightButton ? WM_RBUTTONUP : WM_MBUTTONUP),
                  keys, MAKELPARAM(point.x, point.y));
}

void Window::OnMouseDoubleClick(const Point point, const int keys, const MouseButtons button)
{
    DefWindowProc(
        _hWnd, button == LeftButton ? WM_LBUTTONDOWN : (button == RightButton ? WM_RBUTTONDOWN : WM_MBUTTONDOWN), keys,
        MAKELPARAM(point.x, point.y));
}

void Window::OnMouseWheel(const Point point, const int keys, const float delta)
{
    DefWindowProc(_hWnd, WM_MOUSEWHEEL, MAKEWPARAM(keys, delta), MAKELPARAM(point.x, point.y));
}

void Window::OnKeyDown(const int key, const int keyData)
{
    DefWindowProc(_hWnd, WM_KEYDOWN, key, keyData);
}

void Window::OnKeyUp(const int key, const int keyData)
{
    DefWindowProc(_hWnd, WM_KEYUP, key, keyData);
}
