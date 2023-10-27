#pragma once
#include <string>

#include "Table.h"

class CsvReader
{
public:
    CsvReader(std::string filePath, char delimiter = ',');
    std::vector<std::wstring> ParseCsvLine(const std::string& line) const;
    ~CsvReader() = default;

    bool Read(std::vector<std::vector<std::wstring>>& data) const;
private:
    std::string _filePath;
    char _delimiter;
};
