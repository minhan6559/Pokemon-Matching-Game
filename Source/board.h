#pragma once
#include <string>
const char ZERO[] = R"(  __
 /  \
| () |
 \__/)";
const char ONE[] = R"( _
/ |
| |
|_|)";
const char TWO[] = R"( ___
|_  )
 / /
/___|)";
const char THREE[] = R"( ____
|__ /
 |_ \
|___/)";
const char FOUR[] = R"( _ _
| | |
|_  _|
  |_|)";
const char FIVE[] = R"( ___
| __|
|__ \
|___/)";
const char SIX[] = R"(  __
 / /
/ _ \
\___/)";
const char SEVEN[] = R"( ____
|__  |
  / /
 /_/)";
const char EIGHT[] = R"( ___
( _ )
/ _ \
\___/)";
const char NINE[] = R"( ___
/ _ \
\_, /
 /_/)";

struct Board
{
	int xBoardStart, yBoardStart; // The coordination of top-left corner of the board
	int boxLength, boxWidth;	  // The length and width of each box
	int size;					  // The size of the board
	int** pokeList;				  //32 or " ": Deleted
};
struct Coor
{
	int x;
	int y;
};


void releaseBoard(Board& board);
void randomPokemons(Board& board);

void DrawBorder(Board board);
//Draw information board (include: score at x, y coordination
void DrawInfoBoard(int x, int y, short score, std::string level);
////Change digit to ascii art
void DrawDigit(int x, int y, short digit);
//Draw a score board
void DrawScore(int x, int y, short score);
//Draw a mode board with mode string
void DrawMode(int x, int y, std::string mode);
//Draw a status board with status string
void DrawStatus(int x, int y, std::string status);
//Draw win nofitication to the user
void DrawWinScreen();