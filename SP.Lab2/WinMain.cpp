#include <ctime>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>

#include "CsvReader.h"
#include "Table.h"
#include "TableApplication.h"

int WINAPI WinMain(const HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    const auto reader = CsvReader("input.csv");
    auto data = std::vector<std::vector<std::wstring>>();

    if (!reader.Read(data))
        return 1;
    
    const auto table = std::make_shared<Table>(data.size(), data[0].size());
    table->SetData(data);

    TableApplication app(hInstance, table);
    app.Run();
    return 0;
}
