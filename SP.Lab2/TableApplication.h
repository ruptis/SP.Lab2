#pragma once
#include "Table.h"
#include "WinApiWrapper/Application.h"

class TableApplication final : public WinApiWrapper::Application
{
public:
    explicit TableApplication(HINSTANCE hinstance, const std::shared_ptr<Table>& table);
    ~TableApplication() override = default;

    bool Initialize() override;
    bool CreateMainWindow() override;

private:
    std::shared_ptr<Table> _table;
};
