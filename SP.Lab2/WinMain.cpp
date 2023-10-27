#include <ctime>
#include <memory>
#include <string>
#include <vector>
#include <windows.h>

#include "Table.h"
#include "TableApplication.h"

int WINAPI WinMain(const HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    int rows = 10;
    int columns = 10;
    std::vector<std::wstring> data(rows * columns);
    
    srand(time(nullptr));
    
    for (auto& cell : data)
    {
        cell = L"";
        for (int i = 0; i < rand() % 10; ++i)
            cell += L"Line " + std::to_wstring(i) + L"\n";
    }
    
    const auto table = std::make_shared<Table>(rows, columns);
    table->SetData(data);

    TableApplication app(hInstance, table);
    app.Run();
    return 0;
}
