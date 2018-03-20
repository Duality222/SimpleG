#include <iostream>
#include <windows.h>

using namespace std;

int load_to_file(char answer[])
{
    DWORD dwcount;
    HANDLE logfile;

    DWORD distr=OPEN_ALWAYS;
    logfile=CreateFile("1.log",GENERIC_WRITE,FILE_SHARE_READ,NULL,distr,NULL,NULL);

    if ( logfile != INVALID_HANDLE_VALUE)
    {
        SetFilePointer( logfile, 0, NULL, FILE_END);
        WriteFile(logfile, answer, strlen(answer), &dwcount, NULL);
    }
    else return 0;
    
    CloseHandle(logfile);
    return 1;
}
