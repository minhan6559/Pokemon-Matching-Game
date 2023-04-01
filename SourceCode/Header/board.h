#pragma once
using namespace std;

struct Board
{
	int xBoardStart, yBoardStart;
	int boxLength, boxWidth;
	int size;		
	int** pokeList;		//32 or " ": Deleted
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
void DrawBoardGame(GameInfo& game, bool isSlow);
void ShowMoves(GameInfo& game);
void ChoosePoke(GameInfo& game, int rowPoke, int colPoke);
void DeleteMatching(GameInfo& game);