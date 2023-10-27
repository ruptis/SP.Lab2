#pragma once
#include <windows.h>

namespace WinApiWrapper
{
    class MessageQueue : public MSG
    {
    public:
        MessageQueue() = default;
        explicit MessageQueue(const MSG& msg);

        bool GetMessage(HWND hWnd = nullptr, UINT messageFilterMin = 0, UINT messageFilterMax = 0);

        bool PeekMessage(HWND hWnd = nullptr, UINT messageFilterMin = 0, UINT messageFilterMax = 0,
                         UINT flags = PM_NOREMOVE);

        bool TranslateMessage() const;

        int DispatchMessage() const;
    };
}
