#include <iostream>
#include <stdexcept>
#include <cstdlib>  // For system function
#include <string>   // For string manipulation
#include <windows.h> // For Windows-specific process handling
#include "menu.h"
#include "PDFGenerator.h" // Include the header, not the implementation

using namespace std;

// Function to check if file exists
bool fileExists(const string& path) {
    DWORD fileAttributes = GetFileAttributes(path.c_str());
    return (fileAttributes != INVALID_FILE_ATTRIBUTES && 
           !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY));
}

// Function to run an external executable
bool runExternalProgram(const string& path) {
    // First check if the file exists
    if (!fileExists(path)) {
        cout << "Warning: " << path << " not found. Skipping..." << endl;
        Sleep(1500); // Wait a moment so the user can see the message
        return false;
    }
    
    // Create a process to run the executable
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    
    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));
    
    // Create the process
    bool success = CreateProcess(
        NULL,                   // No module name (use command line)
        const_cast<char*>(path.c_str()),  // Command line
        NULL,                   // Process handle not inheritable
        NULL,                   // Thread handle not inheritable
        FALSE,                  // Set handle inheritance to FALSE
        0,                      // No creation flags
        NULL,                   // Use parent's environment block
        NULL,                   // Use parent's starting directory
        &si,                    // Pointer to STARTUPINFO structure
        &pi                     // Pointer to PROCESS_INFORMATION structure
    );
    
    if (success) {
        // Wait for the process to complete
        WaitForSingleObject(pi.hProcess, INFINITE);
        
        // Close the handles
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return true;
    } else {
        cout << "Failed to launch " << path << endl;
        cout << "Error code: " << GetLastError() << endl;
        Sleep(1500); // Wait a moment so the user can see the message
        return false;
    }
}

int main() {
    try {
        // Create the output directory if it doesn't exist
        system("mkdir output 2> nul");
        
        // Run the welcome window first
        string ventanaPath = "output\\ventana.exe";
        runExternalProgram(ventanaPath);
        
        // Then start the main program
        Menu menu;
        menu.run();
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 1;
    }
    return 0;
}