#pragma once
#include <string>
#include <vector>

class Table
{
public:
    Table(int rows, int columns);
    ~Table() = default;

    void SetCell(int row, int column, const std::wstring& value);
    void SetCell(int row, int column, std::wstring&& value);

    void SetData(const std::vector<std::wstring>& data);
    void SetData(std::vector<std::wstring>&& data);
    void SetData(const std::wstring& data);

    [[nodiscard]] std::wstring GetCell(int row, int column) const;

    [[nodiscard]] int GetRows() const;
    [[nodiscard]] int GetColumns() const;

private:
    int _rows;
    int _columns;

    std::vector<std::wstring> _data;
};
