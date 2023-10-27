#include "CsvReader.h"

#include <fstream>
#include <sstream>

CsvReader::CsvReader(std::string filePath, const char delimiter) : _filePath(std::move(filePath)), _delimiter(delimiter)
{
}

std::vector<std::wstring> CsvReader::ParseCsvLine(const std::string& line) const
{
    std::vector<std::wstring> row;
    std::stringstream lineStream(line);
    std::string cell;
    bool isInsideQuotedCell = false;
    std::string currentCell;

    while (std::getline(lineStream, cell, _delimiter))
    {
        if (!isInsideQuotedCell)
        {
            if (cell.empty())
            {
                row.emplace_back(L"");
            }
            else if (cell.front() == '"')
            {
                if (cell.back() == '"')
                {
                    row.emplace_back(cell.begin() + 1, cell.end() - 1);
                }
                else
                {
                    isInsideQuotedCell = true;
                    currentCell = cell.substr(1);
                }
            }
            else
            {
                row.emplace_back(cell.begin(), cell.end());
            }
        }
        else
        {
            if (cell.back() == '"')
            {
                isInsideQuotedCell = false;
                currentCell += _delimiter + cell.substr(0, cell.size() - 1);
                row.emplace_back(currentCell.begin(), currentCell.end());
            }
            else
            {
                currentCell += _delimiter + cell;
            }
        }
    }

    return row;
}

bool CsvReader::Read(std::vector<std::vector<std::wstring>>& data) const
{
    std::ifstream file(_filePath);
    if (!file.is_open())
        return false;

    std::string line;
    while (std::getline(file, line))
        data.emplace_back(ParseCsvLine(line));

    file.close();
    return true;
}
