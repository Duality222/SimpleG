#include <iostream>
#include <windows.h>

using namespace std;

void tactic (char answer [])
{
    DWORD dwcount;
    OFSTRUCT ofstruct;
    HANDLE logfile;
    HFILE hFile = OpenFile("1.log", &ofstruct, OF_READWRITE);
    if (hFile == -1)
    {
        DWORD distr=CREATE_ALWAYS;
        logfile=CreateFile("1.log",GENERIC_WRITE,FILE_SHARE_READ,NULL,distr,NULL,NULL);
    }

    if ( logfile != INVALID_HANDLE_VALUE || hFile != -1)
    {
        DWORD dwPtrLow = SetFilePointer( logfile, 0, NULL, FILE_END);
        WriteFile(logfile, answer, strlen(answer), &dwcount, NULL);
    }

    //CloseHandle(logfile);
}

void screenshot(POINT a, POINT b)
{
    COLORREF cl_green = 0;
    COLORREF clPix = 0;
    byte RColor;
    byte GColor;
    byte BColor;
    bool Check_Start = false;
    char Ans;

    const byte Const_Red = 171;
    const byte Const_Dark = 31;
    const byte Const_Green = 23;

    HDC     hScreen = GetDC(NULL);
    HDC     hDC     = CreateCompatibleDC(hScreen);
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreen, abs(b.x-a.x), abs(b.y-a.y));
    HGDIOBJ old_obj = SelectObject(hDC, hBitmap);

    do
    {
        cl_green = GetPixel(hScreen, 1600, 132);
        GColor = GetGValue(cl_green);
    }
    while (GColor < 20);

    Check_Start = false;

    do
    {
        cl_green = GetPixel(hScreen, 1600, 132);
        GColor = GetGValue(cl_green);
        if (GColor < 20)
        {
            Check_Start = true;
        }
    }
    while (Check_Start == false);

    if (Check_Start == true)
    {
        clPix = GetPixel(hScreen, 1199, 295);
        RColor = GetRValue(clPix);

        if (RColor == Const_Dark)
        {
            cout << "Dark ";
            Ans = '1';
        }
        if (RColor == Const_Green)
        {
            cout << "Green ";
            Ans = '0';
        }
        if (RColor == Const_Red)
        {
            cout << "Red ";
            Ans = '2';
        }
        tactic(&Ans);
    }
}


int main()
{
    POINT a,b;
    a.x=0;
    a.y=0;

    b.x=1920;
    b.y=1080;

    while (true)
    {
        screenshot(a,b);

    }
}
