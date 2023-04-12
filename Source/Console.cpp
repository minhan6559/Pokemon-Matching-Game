#include "console.h"
#pragma comment (lib, "winmm.lib")

void setAndCenterWindow()
{
	HWND consoleWindow = GetConsoleWindow();
	RECT rectClient, rectWindow;
	GetClientRect(consoleWindow, &rectClient), GetWindowRect(consoleWindow, &rectWindow);
	int windowsWidth = GetSystemMetrics(SM_CXSCREEN);
	int windowsHeight = GetSystemMetrics(SM_CYSCREEN);
	MoveWindow(consoleWindow, 10, 10, windowsWidth - 100, windowsHeight - 50, TRUE);
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
	mciSendString("play \"sound\\Background.mp3\" repeat", NULL, 0, 0);
}

void SelectingSound()
{
	PlaySound(TEXT("sound\\Selecting.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void ChoosedSound()
{
	mciSendString("play \"sound\\Choosed.mp3\"", NULL, 0, 0);
}

void ErrorSound()
{
	mciSendString("play \"sound\\Error.mp3\"", NULL, 0, 0);
}

void CorrectSound()
{
	mciSendString("play \"sound\\Correct.mp3\"", NULL, 0, 0);
}


void SetUpConsole(bool isLogin)
{
	if (isLogin)
	{
		SetConsoleOutputCP(437); //Display extended ASCII
		SetConsoleTitle("Pukachi");
		setAndCenterWindow();
		ShowWindow(GetConsoleWindow(), 3);
		DisableResizeWindow();
		DisableCtrButton(1, 1, 0);
	}
	else
	{
		ShowCur(0);
		DisableSelection();
	}
}