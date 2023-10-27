#include "MessageQueue.h"

using namespace WinApiWrapper;

MessageQueue::MessageQueue(const MSG& msg) : tagMSG()
{
    *static_cast<MSG*>(this) = msg;
}

bool MessageQueue::GetMessageW(const HWND hWnd, const UINT messageFilterMin, const UINT messageFilterMax)
{
    return ::GetMessage(this, hWnd, messageFilterMin, messageFilterMax) != FALSE;
}

bool MessageQueue::PeekMessageW(const HWND hWnd, const UINT messageFilterMin, const UINT messageFilterMax,
                                const UINT flags)
{
    return ::PeekMessage(this, hWnd, messageFilterMin, messageFilterMax, flags) != FALSE;
}

bool MessageQueue::TranslateMessage() const
{
    return ::TranslateMessage(this) != FALSE;
}

int MessageQueue::DispatchMessageW() const
{
    return static_cast<int>(::DispatchMessage(this));
}
