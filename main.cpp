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

bool check_start_game (HDC Scr, int x, int y)
{
	COLORREF Ncolor_fin;
	COLORREF Ncolor_str;
	bool check = false;

	byte 	 GreenC_fin;
	byte 	 GreenC_str;

    do
    {
        Ncolor_fin = GetPixel  (Scr, x, y);
        GreenC_fin = GetGValue (Ncolor_fin);
    }
    while (GreenC_fin < 20);

	do
    {
        Ncolor_str = GetPixel  (Scr, x, y);
        GreenC_str = GetGValue (Ncolor_str);

        if (GreenC_str < 20){ check = true; }
    }
    while (check == false);

    return check;
}

void screenshot(POINT a, POINT b)
{
	// constants determining the color in the red range
	const byte Const_Red    = 171;
    const byte Const_Dark   = 31;
    const byte Const_Green  = 23;

    //coordinates of the inspection the start of the game
    const int gline_coor_x  = 1850;
    const int gline_coor_y  = 130;

    //coordinates of the winning color check
    const int vict_coor_x   = 1199;
    const int vict_coor_y   = 295;

	COLORREF cl_green = 0;
    COLORREF clPix    = 0;

    bool     Check_Start = false;

    char red   = '1';
    char black = '2';
    char green = '0';

    HDC      hScreen = GetDC(NULL);
    HDC      hDC     = CreateCompatibleDC(hScreen);
    HBITMAP  hBitmap = CreateCompatibleBitmap(hScreen, abs(b.x-a.x), abs(b.y-a.y));
    HGDIOBJ  old_obj = SelectObject(hDC, hBitmap);

    byte RColor  = 0;
    byte GColor  = 0;
    byte BColor  = 0;

    Check_Start = check_start_game(hScreen, gline_coor_x, gline_coor_y);

    if (Check_Start == true)
    {
        clPix = GetPixel(hScreen, vict_coor_x, vict_coor_y);
        RColor = GetRValue(clPix);

        if (RColor == Const_Dark)
        {
            load_to_file(&black);
        }
        if (RColor == Const_Green)
        {
            load_to_file(&green);
        }
        if (RColor == Const_Red)
        {
            load_to_file(&red);
        }
    }
}

int main()
{
    POINT a,b;

    //a.x=0;
    //a.y=0;
    //b.x=1920;
    //b.y=1080;

    while (true)
    {
        screenshot(a,b);
    }
}
