#include <iostream>
#include <Windows.h>


using namespace std;

int main()
{
    int intRead = 0;
    int PID = 0;
    int *pointerToInt;
    bool RPMSuccess;
    uintptr_t memoryAddress;
    uintptr_t addressOfPointer;

    cout << "Write the PID of the application you want to read: ";
    cin >> PID;

    HANDLE fProccess = OpenProcess(PROCESS_ALL_ACCESS, false, PID); //Last argument is PID. ALWAYS GET CURRENT PID (PROCESS ID).
    if (fProccess == NULL)
    {
        cout << "OpenProcess method failed with the following error: " << GetLastError() << endl;
        getchar();
        return EXIT_FAILURE;
    }

    cout << "Write the memory address of an integer that you want to read. Must hold an integer: 0x";
    cin >> hex >> memoryAddress;

    RPMSuccess = ReadProcessMemory(fProccess, (LPCVOID)memoryAddress, &intRead, sizeof(int), NULL);
    if (RPMSuccess == NULL)
    {
        cout << "ReadProcessMemory method failed with the following error: " << GetLastError() << endl;
        getchar();
        return EXIT_FAILURE;
    }

    cout << "Write the memory address of a pointer that you want to read: 0x";
    cin >> hex >> addressOfPointer;

    ReadProcessMemory(fProccess, (LPCVOID)addressOfPointer, &pointerToInt, 8 , NULL);
    ReadProcessMemory(fProccess, (LPCVOID)pointerToInt, &intRead, 8, NULL);
    
    cout << "\nThe memory read held the integer " << intRead << endl;
    cout << "\nPRESS ANY KEY TO EXIT.";
    getchar();

    return EXIT_SUCCESS;
}
