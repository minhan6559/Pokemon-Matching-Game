#pragma once
#include "Menu.h"
#include <iostream>
#include <ctime>
using namespace std;

struct Board
{
	int size;		//Kich thuoc bang
	int** pokeList;		//Mang pokemon. -1: Deleted
};
struct GameInfo;

void releaseBoard(Board& board);
void randomPokemons(Board& board);

//Hieu --------------------------------------
void DrawBoardGame(Board board, int x, int y, int boxLength = 11, int boxWidth = 5);
void ShowBoardGame(GameInfo& game, int x, int y);