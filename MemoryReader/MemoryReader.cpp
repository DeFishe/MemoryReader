#include <iostream>
#include <Windows.h>


using namespace std;

int main()
{
    int intRead = 0;

    HANDLE fProccess = OpenProcess(PROCESS_ALL_ACCESS, false, 12028); //Last argument is PID. ALWAYS GET CURRENT PID (PROCESS ID).
    if (fProccess == NULL)
    {
        cout << "OpenProcess method failed with the following error: " << GetLastError() << endl;
        getchar();
        return EXIT_FAILURE;
    }
    ReadProcessMemory(fProccess, (LPCVOID)0x008FFD18, &intRead, sizeof(int), NULL);
    
    cout << "The memory read stored the integer " << intRead << endl;
    cout << "PRESS ANY KEY TO EXIT.";
    getchar();

    return EXIT_SUCCESS;
}
