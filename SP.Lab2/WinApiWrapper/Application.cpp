#include "Application.h"

#include <chrono>
#include <iostream>

#include "MessageQueue.h"

using namespace WinApiWrapper;
using std::shared_ptr;

Application::Application(const shared_ptr<Window>& window) : _window(window)
{
}

Application::~Application() = default;

shared_ptr<Window> Application::GetWindow() const
{
    return _window;
}

bool Application::Initialize()
{
    return true;
}

void Application::OnQuit()
{
}

void Application::Run()
{
    if (Initialize() && CreateMainWindow())
    {
        MessageQueue messageQueue;
        while (messageQueue.GetMessage())
        {
            messageQueue.TranslateMessage();
            messageQueue.DispatchMessage();
        }
        OnQuit();
    }
}

bool Application::CreateMainWindow()
{
    if (!_window->IsCreated())
    {
        _window->Destroy();
        return false;
    }
    _window->Show();
    _window->Update();
    return true;
}
