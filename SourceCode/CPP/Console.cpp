#include "console.h"

//Ref: Luis
void setAndCenterWindow()
{
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

void SelectingSound()
{
    Beep(830, 40);
    Beep(1109, 40);
}

void ChoosedSound()
{
    Beep(1760, 40);
    Beep(1318, 40);
}

void ErrorSound()
{
    Beep(250, 100);
    Beep(200, 100);
}

void CorrectSound()
{
    Beep(1046, 150);
    Beep(2093, 150);
}


void SetUpConsole()
{
    SetConsoleTitle(L"Pukachi");
    setAndCenterWindow();
    DisableResizeWindow();
    DisableCtrButton(1, 1, 1);
    ShowCur(0);
    //DisableSelection();
}