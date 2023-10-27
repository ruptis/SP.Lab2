#pragma once
#include "DWrite.h"

#include <string>

class CellView
{
public:
    CellView(IDWriteFactory& dwriteFactory, const IDWriteTextFormatPtr& textFormat, const std::wstring& value);
    ~CellView() = default;
        
    void Draw(ID2D1RenderTarget& renderTarget,ID2D1SolidColorBrush& brush) const;
    void SetWidth(float maxWidth);
    void SetHeight(float maxHeight);
    void SetPosition(D2D1_POINT_2F position);
    void SetSize(D2D1_SIZE_F size);
    void SetSize(float width, float height);
    [[nodiscard]] D2D1_POINT_2F GetPosition() const;
    [[nodiscard]] D2D1_SIZE_F GetSize() const;
    [[nodiscard]] float GetWidth() const;
    [[nodiscard]] float GetHeight() const;
private:
    IDWriteTextLayoutPtr _textLayout;

    D2D1_SIZE_F _size;
    D2D1_POINT_2F _position;
    
    [[nodiscard]] float GetTextWidth() const;
    [[nodiscard]] float GetTextHeight() const;
};