#include <iostream>
#include <windows.h>
#include <winioctl.h>
#include <stdio.h>

using namespace std;

int main()
{
    string filePath;
    //Attempt to get some sort of location for files
    cout << "Type file path or name of file in this directory:" << endl;
    cin >> filePath;

    cout << "You have entered: " << filePath << endl << endl;

    HANDLE fileHandle;

    STARTING_VCN_INPUT_BUFFER inputVcn;
    RETRIEVAL_POINTERS_BUFFER rpBuf;
    inputVcn.StartingVcn.QuadPart = 0; // start at the beginning

    DWORD dwBytesReturned;

    bool result = DeviceIoControl(fileHandle,
            FSCTL_GET_RETRIEVAL_POINTERS,
            &inputVcn,
            sizeof(STARTING_VCN_INPUT_BUFFER),
            &rpBuf,
            sizeof(RETRIEVAL_POINTERS_BUFFER),
            &dwBytesReturned,
            NULL);

    cout << "input VCN: " << &inputVcn << endl;
    cout << "rpBuf: " << &rpBuf << endl;
    cout << "dwBytesReturned: " << dwBytesReturned << endl;
}
