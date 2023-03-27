#pragma once
#include <Windows.h>


void SetWindowSize(SHORT width, SHORT height);
void SetScreenBufferSize(SHORT width, SHORT height);
void DisableResizeWindow();
void DisableCtrButton(bool Close, bool Min, bool Max);
void ShowScrollbar(BOOL Show);
void SetColor(int backgound_color, int text_color);
void GoTo(SHORT posX, SHORT posY);
void SetUpConsole();