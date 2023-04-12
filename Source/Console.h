#pragma once
#include <Windows.h>
//ref: louis and Khoi
void setAndCenterWindow();
void DisableResizeWindow();
void DisableCtrButton(bool Close, bool Min, bool Max);
void ShowScrollbar(BOOL Show);

void SetColor(int backgound_color, int text_color);
void GoTo(SHORT posX, SHORT posY);
void ShowCur(bool CursorVisibility);
void DisableSelection();

void SetUpConsole(bool isLogin);

void BackgroundSong();
void SelectingSound();
void ChoosedSound();
void ErrorSound();
void CorrectSound();