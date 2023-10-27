#include "TableApplication.h"

#include "TableWindow.h"

TableApplication::TableApplication(HINSTANCE hinstance, const std::shared_ptr<Table>& table): Application(
    std::make_shared<TableWindow>(hinstance))
{
    _table = table;
}

bool TableApplication::Initialize()
{
    const auto tableWindow = std::dynamic_pointer_cast<TableWindow>(GetWindow());
    tableWindow->SetTable(_table);
    return Application::Initialize();
}

bool TableApplication::CreateMainWindow()
{
    return GetWindow()->Create(L"Table", 0, WS_OVERLAPPEDWINDOW | WS_VSCROLL) && Application::CreateMainWindow();
}
