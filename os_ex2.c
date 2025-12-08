#include <stdio.h>
#include <windows.h>

int main() {
    HANDLE hSource, hDest;
    DWORD bytesRead, bytesWritten;
    char buffer[1024];

    // Open source file
    hSource = CreateFile(
        "input.txt",          // source file
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hSource == INVALID_HANDLE_VALUE) {
        printf("Cannot open source file!\n");
        return 1;
    }

    // Create destination file
    hDest = CreateFile(
        "output.txt",         // destination file
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (hDest == INVALID_HANDLE_VALUE) {
        printf("Cannot create destination file!\n");
        CloseHandle(hSource);
        return 1;
    }

    // Copy contents
    while (ReadFile(hSource, buffer, sizeof(buffer), &bytesRead, NULL) && bytesRead > 0) {
        WriteFile(hDest, buffer, bytesRead, &bytesWritten, NULL);
    }

    printf("File copied successfully!\n");

    CloseHandle(hSource);
    CloseHandle(hDest);

    return 0;
}

