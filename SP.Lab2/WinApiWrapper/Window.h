#pragma once
#include <windows.h>
#include <string>

#include "Point.h"
#include "Rect.h"
#include "Size.h"
#include "WindowClass.h"

namespace WinApiWrapper
{
    class Window
    {
    public:
        explicit Window(HINSTANCE hInstance);
        virtual ~Window();
        void SetCreated(HWND hwnd);

        bool Create(LPCWSTR lpszWindowName,
                    const WindowClass& wndClass,
                    const RECT& rc = Rect(Point(CW_USEDEFAULT, 0), CW_USEDEFAULT, 0),
                    HWND hWndParent = nullptr,
                    HMENU hMenu = nullptr,
                    DWORD dwExStyle = 0,
                    LPVOID lpParam = nullptr,
                    DWORD dwStyle = WS_OVERLAPPEDWINDOW);

        bool Create(LPCWSTR lpszWindowName,
                    const RECT& rc = Rect(Point(CW_USEDEFAULT, 0), CW_USEDEFAULT, 0),
                    HWND hWndParent = nullptr,
                    HMENU hMenu = nullptr,
                    DWORD dwExStyle = 0,
                    LPVOID lpParam = nullptr,
                    DWORD dwStyle = WS_OVERLAPPEDWINDOW);

        bool Create(LPCWSTR lpszWindowName,
                    DWORD dwExStyle = 0,
                    DWORD dwStyle = WS_OVERLAPPEDWINDOW);

        [[nodiscard]] bool IsCreated() const;

        [[nodiscard]] bool Show(int nCmdShow = SW_SHOWNORMAL) const;

        [[nodiscard]] bool ShowAsync(int nCmdShow = SW_SHOWNORMAL) const;

        [[nodiscard]] bool Update() const;

        [[nodiscard]] bool Redraw(UINT flags = RDW_INVALIDATE) const;

        [[nodiscard]] bool Redraw(const RECT& rcUpdate, UINT flags = RDW_INVALIDATE) const;

        bool Redraw(HRGN hrgnUpdate, UINT flags = RDW_INVALIDATE) const;

        [[nodiscard]] bool Invalidate(bool bErase = true) const;

        [[nodiscard]] bool InvalidateRect(const RECT& rc, bool bErase = true) const;

        bool InvalidateRgn(HRGN hrgn, bool bErase = true) const;

        [[nodiscard]] bool ValidateRect(const RECT& rc) const;

        bool ValidateRgn(HRGN hrgn) const;

        bool Destroy();

        [[nodiscard]] bool Close() const;

        [[nodiscard]] bool Enable(bool bEnable = true) const;

        [[nodiscard]] bool IsEnabled() const;

        bool GetClientRect(RECT* lpRect) const;

        [[nodiscard]] Rect GetClientRect() const;

        bool GetWindowRect(RECT* lpRect) const;

        [[nodiscard]] Rect GetWindowRect() const;

        bool IsChild(HWND hwndParent) const;

        [[nodiscard]] bool IsWindow() const;

        [[nodiscard]] bool IsVisible() const;

        [[nodiscard]] bool IsZoomed() const;

        bool GetPlacement(WINDOWPLACEMENT* lpwndpl) const;

        bool SetPlacement(const WINDOWPLACEMENT* lpwndpl) const;

        [[nodiscard]] std::string GetText() const;

        [[nodiscard]] bool Move(const POINT& pt, int width, int height, bool bRepaint = true) const;

        [[nodiscard]] bool Move(const RECT& rc, bool bRepaint = true) const;

        [[nodiscard]] bool SetPos(const POINT& pt) const;

        [[nodiscard]] bool SetPos(int width, int height) const;

        [[nodiscard]] bool SetPos(const RECT& rc) const;

        bool SetPos(HWND hwndAfter) const;

        bool SetPos(HWND hwndAfter, const RECT& rc, UINT uFlags) const;

        bool SetScrollPos(int nBar, int nPos, bool bRedraw = true) const;

        [[nodiscard]] int GetScrollPos(int nBar) const;

        bool PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0) const;

        int SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0) const;

        bool SendMessageTimeout(UINT uMsg, WPARAM wParam, LPARAM lParam, UINT uFlags,
                                UINT uTimeout, PDWORD_PTR lpdwResult) const;

        int MessageBox(LPCTSTR lpText, LPCTSTR lpCaption, UINT uType = MB_OK | MB_ICONASTERISK) const;

        void BeginPaint(LPPAINTSTRUCT lpPaint) const;

        void EndPaint(LPPAINTSTRUCT lpPaint) const;

        explicit operator HWND() const;

        [[nodiscard]] HWND GetHandle() const;

        enum MouseButtons
        {
            LeftButton = 0x01,
            RightButton = 0x02,
            MiddleButton = 0x04,
        };

        virtual int HandleMessage(unsigned uMsg, unsigned long long wParam, long long lParam);

        virtual bool OnCreate(LPCREATESTRUCT lpCreateStruct = nullptr);
        virtual void OnClose();
        virtual void OnDestroy();
        virtual void OnActivateApp(bool isActive);
        virtual void OnCommand(int nIdentifier, int nNotifyCode, HWND hwndControl);
        virtual int OnNotify(int nIdentifier, LPNMHDR pnmh);
        virtual void OnPaint();
        virtual void OnSize(int sizing, Size new_size);
        virtual void OnEnterSizeMove();
        virtual void OnExitSizeMove();
        virtual void OnMouseMove(Point point, int keys);
        virtual void OnMouseDown(Point point, int keys, MouseButtons button);
        virtual void OnMouseUp(Point point, int keys, MouseButtons button);
        virtual void OnMouseDoubleClick(Point point, int keys, MouseButtons button);
        virtual void OnMouseWheel(Point point, int keys, float delta);
        virtual void OnKeyDown(int key, int keyData);
        virtual void OnKeyUp(int key, int keyData);

    protected:
        HINSTANCE _hInstance;
        HWND _hWnd = nullptr;
        bool _isCreated = false;
    };
}
