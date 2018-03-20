#include <iostream>
#include <windows.h>

using namespace std;

int main()
{
    char answer[] = "a\r\n";
    DWORD dwcount;
    OFSTRUCT ofstruct;
    HANDLE logfile;

    DWORD distr=OPEN_ALWAYS;
    logfile=CreateFile("1.log",GENERIC_WRITE,FILE_SHARE_READ,NULL,distr,NULL,NULL);

    if ( logfile != INVALID_HANDLE_VALUE)
    {
        DWORD dwPtrLow = SetFilePointer( logfile, 0, NULL, FILE_END);
        WriteFile(logfile, answer, strlen(answer), &dwcount, NULL);
    }

    CloseHandle(logfile);
}
