#pragma once
#include <Windows.h>

//ref: louis and Khoi
void setAndCenterWindow();
void DisableResizeWindow();
void DisableCtrButton(bool Close, bool Min, bool Max);
void ShowScrollbar(BOOL Show);

//ref: https://codelearn.io/sharing/windowsh-ham-dinh-dang-noi-dung-console
void SetColor(int backgound_color, int text_color);
void GoTo(SHORT posX, SHORT posY);
void ShowCur(bool CursorVisibility);
void DisableSelection();

void SetUpConsole(bool isLogin);

//ref: https://www.youtube.com/watch?v=zOljIjBJvRI
//ref: https://learn.microsoft.com/en-us/previous-versions//dd757161(v=vs.85)
//https://learn.microsoft.com/en-us/windows/win32/multimedia/play
void BackgroundSong();
void SelectingSound();
void ChoosedSound();
void ErrorSound();
void CorrectSound();