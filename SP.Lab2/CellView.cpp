#include "CellView.h"

CellView::CellView(IDWriteFactory& dwriteFactory, const IDWriteTextFormatPtr& textFormat,
                              const std::wstring& value): _size(), _position()
{
    HRESULT hr = dwriteFactory.
        CreateTextLayout(value.c_str(), value.size(), textFormat, FLT_MAX, FLT_MAX, &_textLayout);
    assert(SUCCEEDED(hr));
}

void CellView::Draw(ID2D1RenderTarget& renderTarget, ID2D1SolidColorBrush& brush) const
{
    renderTarget.DrawTextLayout(_position, _textLayout, &brush);
}

void CellView::SetWidth(const float maxWidth)
{
    _textLayout->SetMaxWidth(maxWidth);
    const auto height = GetTextHeight();
    _size = D2D1::SizeF(maxWidth, height);
}

void CellView::SetHeight(const float maxHeight)
{
    _textLayout->SetMaxHeight(maxHeight);
    const auto width = GetTextWidth();
    _size = D2D1::SizeF(width, maxHeight);
}

void CellView::SetPosition(const D2D1_POINT_2F position)
{
    _position = position;
}

void CellView::SetSize(const D2D1_SIZE_F size)
{
    _size = size;
    _textLayout->SetMaxWidth(_size.width);
    _textLayout->SetMaxHeight(_size.height);
}

void CellView::SetSize(const float width, const float height)
{
    SetSize(D2D1::SizeF(width, height));
}

D2D1_POINT_2F CellView::GetPosition() const
{
    return _position;
}

D2D1_SIZE_F CellView::GetSize() const
{
    return _size;
}

float CellView::GetWidth() const
{
    return _size.width;
}

float CellView::GetHeight() const
{
    return _size.height;
}

float CellView::GetTextWidth() const
{
    DWRITE_TEXT_METRICS metrics;
    _textLayout->GetMetrics(&metrics);
    return metrics.width;
}

float CellView::GetTextHeight() const
{
    DWRITE_TEXT_METRICS metrics;
    _textLayout->GetMetrics(&metrics);
    return metrics.height;
}