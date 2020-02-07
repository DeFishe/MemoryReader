#include <iostream>
#include <Windows.h>


using namespace std;

void IntRead(HANDLE fProcess, int &intRead);
void RefRead(HANDLE fProcess, int &IntRead);
void StringRead(HANDLE fProcess, string &stringRead);
void CharArrayRead(HANDLE fProcess, char charArrayRead[]);
void IntWrite(HANDLE fProcess);

int main()
{
    int PID = 0;
    int intRead = 0;
    int intWritten;
    string stringRead;
    char charArrayRead[128];
    unsigned int menuSelection = 0;
    bool chSuccess;

    cout << "Write the Process ID of the application you want to read: ";
    cin >> PID;
    cout << endl;

    HANDLE fProcess = OpenProcess(PROCESS_ALL_ACCESS, false, PID);
    if (fProcess == NULL)
    {
        cout << "OpenProcess method failed with the following error: " << GetLastError() << endl;
        cin.get();
        return EXIT_FAILURE;
    }

    while (menuSelection != 8)
    {
        while (menuSelection < 1 || menuSelection > 7)
        {
            cout << "Choose an option:" << endl;
            cout << "1) Read the memory of an integer" << endl;
            cout << "2) Read the memory of a reference" << endl;
            cout << "3) Read the memory of a string" << endl;
            cout << "4) Read the memory of a character array" << endl;
            cout << "5) Overwrite the memory of an integer" << endl;
            cout << "6) Overwrite the memory of a string" << endl;
            cout << "7) Overwrite the memory of a character array" << endl;
            cout << "8) Quit" << endl;
            cin >> menuSelection;
            if (menuSelection < 1 || menuSelection > 7)
            {
                cout << "Invalid selection. Try again." << endl;
            }
        }
        switch (menuSelection)
        {
        case 1:
            IntRead(fProcess, intRead);
            cout << "\nThe memory read held the integer " << intRead << endl;
            menuSelection = 0;
            cin.get();
            break;
        case 2:
            RefRead(fProcess, intRead);
            cout << "\nThe memory the reference referenced held the integer " << intRead << endl;
            menuSelection = 0;
            cin.get();
        case 3:
            StringRead(fProcess, stringRead);
            cout << "\nThe memory read held the string \"" << stringRead << "\"" << endl;
            menuSelection = 0;
            break;
        case 4:
            CharArrayRead(fProcess, charArrayRead);
            cout << "\nThe memory read held the char array \"" << charArrayRead << "\"" << endl;
            menuSelection = 0;
            break;
        case 5:
            IntWrite(fProcess);
            cout << "\nThe memory was successfully overwritten." << endl;
            menuSelection = 0;
            break;
        case 6:
            //insert method
            cout << "\nThe memory was successfully overwritten." << endl;
            menuSelection = 0;
            break;
        case 7:
            //insert method
            cout << "\nThe memory was successfully overwritten." << endl;
            menuSelection = 0;
            break;
        default:
            break;
        }
    }

    chSuccess = CloseHandle(fProcess);
    if (chSuccess == NULL)
    {
        cout << "CloseHandle method failed with the following error: " << GetLastError() << endl;
        return EXIT_FAILURE;
    }
    else
    {
        return EXIT_SUCCESS;
    }
    
}

void IntRead(HANDLE fProcess, int &intRead)
{
    uintptr_t memoryAddress;
    bool RPMSuccess;

    cout << "Write the memory address of an integer that you want to read. Must hold an integer: 0x";
    cin >> hex >> memoryAddress;

    RPMSuccess = ReadProcessMemory(fProcess, (LPCVOID)memoryAddress, &intRead, sizeof(int), NULL);
    if (RPMSuccess == NULL)
    {
        cout << "ReadProcessMemory method failed with the following error: " << GetLastError() << endl;
        bool chSuccess = CloseHandle(fProcess);
        if (chSuccess == NULL)
        {
            cout << "CloseHandle method failed with the following error: " << GetLastError() << endl;
        }
        cin.get();
        exit(EXIT_FAILURE);

    }
}

void RefRead(HANDLE fProcess, int &intRead)
{
    uintptr_t addressOfPointer;
    int* pointerToInt;
    bool RPMSuccess;

    cout << "Write the memory address of a pointer that you want to read: 0x";
    cin >> hex >> addressOfPointer;

    RPMSuccess = ReadProcessMemory(fProcess, (LPCVOID)addressOfPointer, &pointerToInt, 8, NULL);
    if (RPMSuccess == NULL)
    {
        cout << "ReadProcessMemory method failed with the following error: " << GetLastError() << endl;
        bool chSuccess = CloseHandle(fProcess);
        if (chSuccess == NULL)
        {
            cout << "CloseHandle method failed with the following error: " << GetLastError() << endl;
        }
        cin.get();
        exit(EXIT_FAILURE);
    }
    RPMSuccess = ReadProcessMemory(fProcess, (LPCVOID)pointerToInt, &intRead, 8, NULL);
    if (RPMSuccess == NULL)
    {
        cout << "ReadProcessMemory method failed with the following error: " << GetLastError() << endl;
        bool chSuccess = CloseHandle(fProcess);
        if (chSuccess == NULL)
        {
            cout << "CloseHandle method failed with the following error: " << GetLastError() << endl;
        }
        cin.get();
        exit(EXIT_FAILURE);
    }
}

void StringRead(HANDLE fProcess, string &stringRead)
{
    uintptr_t memoryAddress;
    bool RPMSuccess;

    cout << "Write the memory address of a string you want to read. Must hold a string: 0x";
    cin >> hex >> memoryAddress;

    RPMSuccess = ReadProcessMemory(fProcess, (LPCVOID)memoryAddress, &stringRead, sizeof(string), NULL);
    if (RPMSuccess == NULL)
    {
        cout << "ReadProcessMemory method failed with the following error: " << GetLastError() << endl;
        bool chSuccess = CloseHandle(fProcess);
        if (chSuccess == NULL)
        {
            cout << "CloseHandle method failed with the following error: " << GetLastError() << endl;
        }
        cin.get();
        exit(EXIT_FAILURE);
    }
}

void CharArrayRead(HANDLE fProcess, char charArrayRead[])
{
    uintptr_t memoryAddress;
    bool RPMSuccess;
    cout << "Write the memory addres of the character array you want to read. Must hold a character array: 0x";
    cin >> hex >> memoryAddress;

    RPMSuccess = ReadProcessMemory(fProcess, (LPCVOID)memoryAddress, (LPVOID)charArrayRead, 128, NULL);
    if (RPMSuccess == NULL)
    {
        cout << "ReadProcessMemory method failed with the following error: " << GetLastError() << endl;
        bool chSuccess = CloseHandle(fProcess);
        if (chSuccess == NULL)
        {
            cout << "CloseHandle method failed with the following error: " << GetLastError() << endl;
        }
        cin.get();
        exit(EXIT_FAILURE);
    }
}

void IntWrite(HANDLE fProcess)
{
    uintptr_t memoryAddress;
    bool WPMSuccess;
    int intWritten;
    cout << "Write the memory address of an integer that you want to overwrite. Must hold an integer: 0x";
    cin >> hex >> memoryAddress;
    cout << "\nWrite the number you want to write into the memory address." << endl;
    cin >> dec >> intWritten;
    WPMSuccess = WriteProcessMemory(fProcess, (LPVOID)memoryAddress, &intWritten, sizeof(int), NULL);
    if (WPMSuccess == NULL)
    {
        cout << "WriteProcessMemory method failed with the following error: " << GetLastError() << endl;
        bool chSuccess = CloseHandle(fProcess);
        if (chSuccess == NULL)
        {
            cout << "CloseHandle method failed with the following error: " << GetLastError() << endl;
        }
        cin.get();
        exit(EXIT_FAILURE);
    }
}
