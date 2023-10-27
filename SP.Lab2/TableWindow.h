#pragma once
#include "DWrite.h"

#include <memory>

#include "Table.h"
#include "TableView.h"
#include "WinApiWrapper/Window.h"

class TableWindow final : public WinApiWrapper::Window
{
public:
    explicit TableWindow(HINSTANCE hInstance);
    ~TableWindow() override = default;

    bool OnCreate(LPCREATESTRUCT lpCreateStruct) override;
    void OnDestroy() override;
    void OnPaint() override;
    void OnSize(int sizing, WinApiWrapper::Size new_size) override;
    int HandleMessage(unsigned uMsg, unsigned long long wParam, long long lParam) override;
    
    void SetTable(const std::shared_ptr<Table>& table);

private:
    std::unique_ptr<TableView> _tableView;
    std::shared_ptr<Table> _table;

    ID2D1FactoryPtr _d2dFactory;
    ID2D1HwndRenderTargetPtr _renderTarget;

    IDWriteFactoryPtr _dwriteFactory;

    std::wstring _text;
    
    bool CreateDeviceResources();
};
