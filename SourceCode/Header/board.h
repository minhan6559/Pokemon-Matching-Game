#pragma once
#include "Menu.h"
#include <iostream>
#include <ctime>
using namespace std;

struct Board
{
	int xBoardStart, yBoardStart;
	int boxLength, boxWidth;
	int size;		//Kich thuoc bang
	int** pokeList;		//Mang pokemon. -1: Deleted
};
struct GameInfo;

void releaseBoard(Board& board);
void randomPokemons(Board& board);

//Hieu --------------------------------------
void DrawBoardGame(Board board);
void ShowMoves(GameInfo& game);
void ChoosePoke(GameInfo& game, int rowPoke, int colPoke);
void DeleteMatching(GameInfo& game);