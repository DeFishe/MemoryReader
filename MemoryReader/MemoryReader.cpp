#include <iostream>
#include <Windows.h>


using namespace std;

void IntRead(HANDLE fProcess, int &intRead);
void RefRead(HANDLE fProcess, int &IntRead);

int main()
{
    int intRead = 0;
    int PID = 0;
    unsigned int menuSelection = 0;

    cout << "Write the Process ID of the application you want to read: ";
    cin >> PID;
    cout << endl;

    HANDLE fProcess = OpenProcess(PROCESS_VM_READ, false, PID);
    if (fProcess == NULL)
    {
        cout << "OpenProcess method failed with the following error: " << GetLastError() << endl;
        cin.get();
        return EXIT_FAILURE;
    }

    while (menuSelection != 3)
    {
        while (menuSelection < 1 || menuSelection > 3)
        {
            cout << "Choose an option:" << endl;
            cout << "1) Read the memory of an integer" << endl;
            cout << "2) Read the memory of a reference" << endl;
            cout << "3> Quit" << endl;
            cin >> menuSelection;
            if (menuSelection < 1 || menuSelection > 3)
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
            cout << "\nThe memory read held the integer " << intRead << endl;
            menuSelection = 0;
            cin.get();
            break;
        default:
            break;
        }
    }

    return EXIT_SUCCESS;
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
        cin.get();
        exit(EXIT_FAILURE);
    }
    RPMSuccess = ReadProcessMemory(fProcess, (LPCVOID)pointerToInt, &intRead, 8, NULL);
    if (RPMSuccess == NULL)
    {
        cout << "ReadProcessMemory method failed with the following error: " << GetLastError() << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }
}
