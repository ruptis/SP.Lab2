#include "Table.h"

Table::Table(const int rows, const int columns)
{
    _rows = rows;
    _columns = columns;
    _data.resize(rows * columns);
}

void Table::SetCell(const int row, const int column, const std::wstring& value)
{
    _data[row * _columns + column] = value;
}

void Table::SetCell(const int row, const int column, std::wstring&& value)
{
    _data[row * _columns + column] = std::move(value);
}

void Table::SetData(const std::vector<std::wstring>& data)
{
    _data = data;
}

void Table::SetData(std::vector<std::wstring>&& data)
{
    _data = std::move(data);
}

void Table::SetData(const std::wstring& data)
{
    for (int i = 0; i < _rows * _columns; ++i)
        _data[i] = data;
}

void Table::SetData(const std::vector<std::vector<std::wstring>>& data)
{
    for (int row = 0; row < _rows; ++row)
        for (int column = 0; column < _columns; ++column)
            _data[row * _columns + column] = data[row][column];
}

void Table::SetData(std::vector<std::vector<std::wstring>>&& data)
{
    for (int row = 0; row < _rows; ++row)
        for (int column = 0; column < _columns; ++column)
            _data[row * _columns + column] = std::move(data[row][column]);
}

int Table::GetRows() const
{ return _rows; }

int Table::GetColumns() const
{ return _columns; }

std::wstring Table::GetCell(const int row, const int column) const
{
    return _data[row * _columns + column];
}
