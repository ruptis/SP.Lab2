#pragma once
#include <memory>

#include "Window.h"

namespace WinApiWrapper
{
    class Application
    {
    public:
        explicit Application(const std::shared_ptr<Window>& window);
        virtual ~Application();

        void Run();

        [[nodiscard]] std::shared_ptr<Window> GetWindow() const;

    protected:
        virtual bool Initialize();
        virtual void OnQuit();
        virtual bool CreateMainWindow();

    private:
        std::shared_ptr<Window> _window{};
    };
}
