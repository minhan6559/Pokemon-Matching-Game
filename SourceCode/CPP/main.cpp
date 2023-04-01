#include "Console.h"
#include "Game.h"
#include "Menu.h"

using namespace std;

int main()
{
	SetUpConsole();
	//logInMenu();
	GameInfo game(6);
	DrawBoardGame(game, 0);
	//ShowMoves(game);
	//DrawDigit(114, 5, 7);
	//DrawDigit(120, 5, 3);
	DrawInfoBoard(90, 4, 36);
	_getch();
	return 0;
}