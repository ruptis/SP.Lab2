#include "TableView.h"

TableView::TableView(const IDWriteFactoryPtr& dwriteFactory): _size(), _position(), _rows(0), _columns(0), _columnsWidth(0)
{
    _dwriteFactory = dwriteFactory;
}

bool TableView::Initialize()
{
    HRESULT hr = _dwriteFactory->CreateTextFormat(L"Arial", nullptr, DWRITE_FONT_WEIGHT_NORMAL,
                                                  DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 16.0f,
                                                  L"en-us", &_textFormat);
    if (FAILED(hr))
        return false;

    hr = _textFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    if (FAILED(hr))
        return false;

    hr = _textFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    if (FAILED(hr))
        return false;

    return true;
}

void TableView::Draw(ID2D1RenderTarget& renderTarget)
{
    if (!_brush)
        renderTarget.CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::Black), &_brush);
    
    for (auto& cell : _cells)
        cell.Draw(renderTarget, *_brush);

    DrawHorizontalLines(renderTarget);
    DrawVerticalLines(renderTarget);
}

void TableView::SetTable(const std::shared_ptr<Table>& table)
{
    _table = table;
    _rows = _table->GetRows();
    _columns = _table->GetColumns();
    UpdateCells();
}

void TableView::SetSize(const D2D1_SIZE_U size)
{
    _size = D2D1::SizeF(static_cast<float>(size.width), static_cast<float>(size.height));
    UpdateWidth();
    UpdateCellsPositions();
}

void TableView::SetPosition(const D2D1_POINT_2F position)
{
    _position = position;
    UpdateCellsPositions();
}

D2D1_POINT_2F TableView::GetPosition() const
{
    return _position;
}

D2D1_SIZE_F TableView::GetSize() const
{
    return _size;
}

void TableView::DrawLine(ID2D1RenderTarget& renderTarget, const float startX, const float startY, const float endX, const float endY) const
{
    renderTarget.DrawLine(D2D1::Point2F(startX, startY), D2D1::Point2F(endX, endY), _brush);
}

void TableView::DrawHorizontalLines(ID2D1RenderTarget& renderTarget) const
{
    const auto startX = GetColumnPosition(0);
    const auto endX = GetColumnPosition(_columns - 1) + GetColumnWidth(_columns - 1);
    for (int row = 0; row < _rows; ++row)
    {
        const auto y = GetRowPosition(row);
        DrawLine(renderTarget, startX, y, endX, y);
    }
    const auto y = GetRowPosition(_rows - 1) + GetRowHeight(_rows - 1);
    DrawLine(renderTarget, startX, y, endX, y);
}

void TableView::DrawVerticalLines(ID2D1RenderTarget& renderTarget) const
{
    const auto startY = GetRowPosition(0);
    const auto endY = GetRowPosition(_rows - 1) + GetRowHeight(_rows - 1);
    for (int column = 0; column < _columns; ++column)
    {
        const auto x = GetColumnPosition(column);
        DrawLine(renderTarget, x, startY, x, endY);
    }
    const auto x = GetColumnPosition(_columns - 1) + GetColumnWidth(_columns - 1);
    DrawLine(renderTarget, x, startY, x, endY);
}

void TableView::UpdateCells()
{
    if (!IsPropertiesValid())
        return;
    
    _cells.clear();
    _cells.reserve(_rows * _columns);
    _columnsWidth = _size.width / static_cast<float>(_columns);
    
    for (int row = 0; row < _rows; ++row)
    {
        const float rowHeight = FillRow(row);
        SetupRow(row, rowHeight);
    }

    _size.height = CalculateRowPosition(_rows) + GetRowHeight(_rows - 1);
}

void TableView::UpdateWidth()
{
    if (!IsPropertiesValid())
        return;

    _columnsWidth = _size.width / static_cast<float>(_columns);
    
    for (int collumn = 0; collumn < _columns; ++collumn)
        SetColumnWidth(collumn, _columnsWidth);

    for (int row = 0; row < _rows; ++row)
    {
        const auto rowHeight = CalculateRowHeight(row);
        SetupRow(row, rowHeight);
    }

    _size.height = CalculateRowPosition(_rows) + GetRowHeight(_rows - 1);
}

void TableView::UpdateCellsPositions()
{
    for (int row = 0; row < _rows; ++row)
        for (int column = 0; column < _columns; ++column)
            UpdateCellPosition(row, column);
}

bool TableView::IsPropertiesValid() const
{
    return _table != nullptr && _rows > 0 && _columns > 0 && _size.width > 0 && _size.height > 0;
}

float TableView::FillRow(const int row)
{
    auto rowHeight = 0.0f;
    for (int column = 0; column < _columns; ++column)
    {
        std::wstring cellText = _table->GetCell(row, column);
        auto cellView = CellView(*_dwriteFactory, _textFormat, cellText);
        cellView.SetWidth(_columnsWidth);
        rowHeight = max(rowHeight, cellView.GetHeight());
        _cells.push_back(cellView);
    }
    return rowHeight;
}

void TableView::SetupRow(const int row, const float rowHeight)
{
    for (int column = 0; column < _columns; ++column)
    {
        auto& cellView = GetCell(row, column);
        cellView.SetSize(_columnsWidth, rowHeight);
        UpdateCellPosition(row, column, cellView);
    }
}

float TableView::CalculateRowPosition(const int row) const
{
    auto y = 0.0f;
    for (int i = 0; i < row; ++i)
        y += GetRowHeight(i);
    return y;
}

float TableView::CalculateRowHeight(const int row) const
{
    auto rowHeight = 0.0f;
    for (int column = 0; column < _columns; ++column)
        rowHeight = max(rowHeight, GetCell(row, column).GetHeight());

    return rowHeight;
}

void TableView::UpdateCellPosition(const int row, const int column)
{
    auto& cellView = GetCell(row, column);
    UpdateCellPosition(row, column, cellView);
}

void TableView::UpdateCellPosition(const int row, const int column, CellView& cellView) const
{
    const float y = _position.y + CalculateRowPosition(row);
    const float x = _position.x + _columnsWidth * static_cast<float>(column);
    cellView.SetPosition(D2D1::Point2F(x, y));
}

CellView& TableView::GetCell(const int row, const int column)
{
    return _cells[row * _columns + column];
}

CellView TableView::GetCell(const int row, const int column) const
{
    return _cells[row * _columns + column];
}

D2D1_SIZE_U TableView::GetCellSize(const int row, const int column) const
{
    const auto cellView = GetCell(row, column);
    return D2D1::SizeU(static_cast<UINT32>(cellView.GetWidth()), static_cast<UINT32>(cellView.GetHeight()));
}

void TableView::SetColumnWidth(const int column, const float width)
{
    for (int row = 0; row < _rows; ++row)
    {
        auto& cellView = GetCell(row, column);
        cellView.SetWidth(width);
    }
}

void TableView::SetRowHeight(const int row, const float height)
{
    for (int column = 0; column < _columns; ++column)
    {
        auto& cellView = GetCell(row, column);
        cellView.SetHeight(height);
    }
}

float TableView::GetColumnWidth(const int column) const
{
    return GetCell(0, column).GetWidth();
}

float TableView::GetRowHeight(const int row) const
{
    return GetCell(row, 0).GetHeight();
}

float TableView::GetRowPosition(const int row) const
{
    return GetCell(row, 0).GetPosition().y;
}

float TableView::GetColumnPosition(const int column) const
{
    return GetCell(0, column).GetPosition().x;
}
