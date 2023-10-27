#include "TableWindow.h"

TableWindow::TableWindow(const HINSTANCE hInstance): Window(hInstance)
{
}

bool TableWindow::OnCreate(const LPCREATESTRUCT lpCreateStruct)
{
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &_d2dFactory);
    if (FAILED(hr))
        return false;

    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                             reinterpret_cast<IUnknown**>(&_dwriteFactory));
    if (FAILED(hr))
        return false;

    _tableView = std::make_unique<TableView>(_dwriteFactory);

    if (!_tableView->Initialize())
        return false;

    _tableView->SetSize(D2D1::SizeU(100, 100));
    _tableView->SetTable(_table);

    return Window::OnCreate(lpCreateStruct);
}

void TableWindow::OnDestroy()
{
    Window::OnDestroy();
    PostQuitMessage(0);
}

bool TableWindow::CreateDeviceResources()
{
    if (!_renderTarget)
    {
        const RECT rc = GetClientRect();

        const D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

        const HRESULT hr = _d2dFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(),
                                                               D2D1::HwndRenderTargetProperties(GetHandle(), size),
                                                               &_renderTarget);
        if (FAILED(hr))
            return false;
    }

    return true;
}

void TableWindow::OnPaint()
{
    Window::OnPaint();

    if (!CreateDeviceResources())
        return;

    PAINTSTRUCT ps;
    BeginPaint(&ps);

    _renderTarget->BeginDraw();
    _renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

    _tableView->Draw(_renderTarget);

    _renderTarget->EndDraw();

    EndPaint(&ps);
}

void TableWindow::OnSize(const int sizing, const WinApiWrapper::Size new_size)
{
    Window::OnSize(sizing, new_size);

    if (_renderTarget)
        _renderTarget->Resize(D2D1::SizeU(new_size.cx, new_size.cy));

    if (_tableView)
        _tableView->SetSize(D2D1::SizeU(new_size.cx, new_size.cy));
}

int TableWindow::HandleMessage(unsigned uMsg, unsigned long long wParam, long long lParam)
{
    if (uMsg == WM_VSCROLL)
    {
        if (LOWORD(wParam) == SB_THUMBTRACK)
        {
            const auto position = HIWORD(wParam);
            const auto [width, height] = _tableView->GetSize();
            const auto speed = height / 100;
            _tableView->SetPosition(D2D1::Point2F(_tableView->GetPosition().x, -position * speed));
            SetScrollPos(SB_VERT, position);
            Redraw();
            return 0;
        }
    }
    return Window::HandleMessage(uMsg, wParam, lParam);
}

void TableWindow::SetTable(const std::shared_ptr<Table>& table)
{
    assert(table);
    _table = table;
}
