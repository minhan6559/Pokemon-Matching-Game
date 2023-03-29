#include "console.h"
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")

//Ref: Luis
void setAndCenterWindow()
{
    /*system("mode 650");
    HWND hwnd = GetConsoleWindow();
    SetWindowPos(hwnd, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_NOACTIVATE);
    */
    HWND consoleWindow = GetConsoleWindow();
    RECT rectClient, rectWindow;
    GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
    int width = 1500;
    int height = 768;
    int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2,
        posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;
    MoveWindow(consoleWindow, posX, posY, width, height, TRUE);
    
}


void DisableResizeWindow()
{
    HWND hWnd = GetConsoleWindow();
    SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
}

void DisableCtrButton(bool Close, bool Min, bool Max)
{
    HWND hWnd = GetConsoleWindow();
    HMENU hMenu = GetSystemMenu(hWnd, false);

    if (Close == 1)
    {
        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
    }
    if (Min == 1)
    {
        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
    }
    if (Max == 1)
    {
        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
    }
}

void ShowScrollbar(BOOL Show)
{
    HWND hWnd = GetConsoleWindow();
    ShowScrollBar(hWnd, SB_BOTH, Show);
}

void SetColor(int backgound_color, int text_color)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    int color_code = backgound_color * 16 + text_color;
    SetConsoleTextAttribute(hStdout, color_code);
}

void GoTo(SHORT posX, SHORT posY)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD Position;
    Position.X = posX;
    Position.Y = posY;

    SetConsoleCursorPosition(hStdout, Position);
}

void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO ConCurInf;

    ConCurInf.dwSize = 10;
    ConCurInf.bVisible = CursorVisibility;

    SetConsoleCursorInfo(handle, &ConCurInf);
}

void DisableSelection()
{
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

    SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
}

void BackgroundSong()
{
    mciSendString(L"play \"sound\\Background.mp3\" repeat", NULL, 0, 0);
}

void SelectingSound()
{
    PlaySound(TEXT("sound\\Selecting.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void ChoosedSound()
{
    mciSendString(L"play \"sound\\Choosed.mp3\"", NULL, 0, 0);
}

void ErrorSound()
{
    mciSendString(L"play \"sound\\Error.mp3\"", NULL, 0, 0);
}

void CorrectSound()
{
    mciSendString(L"play \"sound\\Correct.mp3\"", NULL, 0, 0);
}

void setFontInfo()
{
    CONSOLE_FONT_INFOEX info;
    info.cbSize = sizeof(info);
    GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &info);
    info.dwFontSize.X = 6;
    info.dwFontSize.Y = 18;
    wcscpy_s(info.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &info);
}

void SetUpConsole()
{
    SetConsoleTitle(L"Pukachi");
    setFontInfo();
    setAndCenterWindow();
    DisableResizeWindow();
    DisableCtrButton(1, 1, 1);
    //ShowCur(0);
    DisableSelection();
}