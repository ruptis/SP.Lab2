#pragma once
#include <memory>

#include "DWrite.h"

#include <vector>

#include "CellView.h"
#include "Table.h"

class TableView
{
public:
    explicit TableView(const IDWriteFactoryPtr& dwriteFactory);
    ~TableView() = default;

    bool Initialize();
    void Draw(ID2D1RenderTarget& renderTarget);

    void SetTable(const std::shared_ptr<Table>& table);
    void SetSize(D2D1_SIZE_U size);
    void SetPosition(D2D1_POINT_2F position);
    [[nodiscard]] D2D1_POINT_2F GetPosition() const;
    [[nodiscard]] D2D1_SIZE_F GetSize() const;

private:
    std::shared_ptr<Table> _table;

    IDWriteFactoryPtr _dwriteFactory;
    ID2D1SolidColorBrushPtr _brush;
    IDWriteTextFormatPtr _textFormat;

    D2D1_SIZE_F _size;
    D2D1_POINT_2F _position;
    int _rows;
    int _columns;
    float _columnsWidth;

    std::vector<CellView> _cells;

    void DrawLine(ID2D1RenderTarget& renderTarget, float startX, float startY, float endX, float endY) const;
    void DrawHorizontalLines(ID2D1RenderTarget& renderTarget) const;
    void DrawVerticalLines(ID2D1RenderTarget& renderTarget) const;

    void UpdateCells();
    void UpdateWidth();
    void UpdateCellsPositions();

    [[nodiscard]] bool IsPropertiesValid() const;
    float FillRow(int row);
    void SetupRow(int row, float rowHeight);
    [[nodiscard]] float CalculateRowPosition(int row) const;
    [[nodiscard]] float CalculateRowHeight(int row) const;
    void UpdateCellPosition(int row, int column);
    void UpdateCellPosition(int row, int column, CellView& cellView) const;

    CellView& GetCell(int row, int column);
    [[nodiscard]] CellView GetCell(int row, int column) const;
    [[nodiscard]] D2D1_SIZE_U GetCellSize(int row, int column) const;
    void SetColumnWidth(int column, float width);
    void SetRowHeight(int row, float height);
    [[nodiscard]] float GetColumnWidth(int column) const;
    [[nodiscard]] float GetRowHeight(int row) const;
    [[nodiscard]] float GetRowPosition(int row) const;
    [[nodiscard]] float GetColumnPosition(int column) const;
};
