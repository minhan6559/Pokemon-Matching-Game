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
struct Point;
struct Queue;
struct GameInfo;

void releaseBoard(Board& board);
void randomPokemons(Board& board);
void drawMatchingLine(GameInfo& game, Queue& path, bool isDraw);
void showSuggestMove(GameInfo& game);
void shufflePokeList(GameInfo& game);
void drawBackground(GameInfo& game, Point pokeIndex);
void highlightBoxForBoard(GameInfo& game, Point pokeIndex, int mode);

//Hieu --------------------------------------
void DrawBorder(Board board);
void DrawBoardGame(GameInfo& game, bool isSlow, bool isFlip);
bool ShowMoves(GameInfo& game);
void ChoosePoke(GameInfo& game, int rowPoke, int colPoke);
void DeleteMatching(GameInfo& game);
void DrawDigit(int x, int y, short digit);
void DrawInfoBoard(int x, int y, short score, std::string level);
void DrawScore(int x, int y, short score);
void DrawStatus(int x, int y, std::string status);
void DrawWinScreen();