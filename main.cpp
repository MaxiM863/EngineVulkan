#include <cstdlib>
#include <string>
#include <windows.h>
#include <processthreadsapi.h>
#include <iostream>
#include <handleapi.h>
#include <errhandlingapi.h>
#include <filesystem>

int main()
{
    STARTUPINFO si = { sizeof(STARTUPINFO) };
    PROCESS_INFORMATION pi;
    
    std::filesystem::path programPath = std::filesystem::current_path();

    std::string tmp = programPath.string() + "\\build\\Serveur\\Debug\\Server.exe";

    LPCSTR path = tmp.c_str();

    std::cout << tmp;

    if (CreateProcessA(path, NULL, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {

        std::cout << "Program launched successfully!" << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        
        std::cerr << "Failed to launch program. Error: " << GetLastError() << std::endl;
    }

    tmp = programPath.string() + "\\build\\MaximEngine\\Debug\\EngineMaxim.exe";

    path = tmp.c_str();

    std::cout << tmp;

    if (CreateProcessA(path, "1 1", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {

        std::cout << "Program launched successfully!" << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        
        std::cerr << "Failed to launch program. Error: " << GetLastError() << std::endl;
    }


    if (CreateProcessA(path, "", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {

        std::cout << "Program launched successfully!" << std::endl;
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    } else {
        
        std::cerr << "Failed to launch program. Error: " << GetLastError() << std::endl;
    }

    return 0;
}