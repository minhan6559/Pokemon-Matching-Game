#include "Console.h"
#include "Game.h"
#include "Menu.h"
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
using namespace std;

int main()
{
	PlaySound(TEXT("sound\\theme.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
    MainMenu();
	return 0;
}