#pragma once
using namespace std;

struct Board
{
	int xBoardStart, yBoardStart;
	int boxLength, boxWidth;
	int size;		//Kich thuoc bang
	int** pokeList;		//Mang pokemon. 32 or " ": Deleted
};
struct Queue;
struct GameInfo;

void releaseBoard(Board& board);
void randomPokemons(Board& board);
void drawMatchingLine(GameInfo& game, Queue& path, bool isDraw);
void showSuggestMove(GameInfo& game);
void shufflePokeList(GameInfo& game);

//Hieu --------------------------------------
void DrawBoardGame(Board board, bool isSlow);
void ShowMoves(GameInfo& game);
void ChoosePoke(GameInfo& game, int rowPoke, int colPoke);
void DeleteMatching(GameInfo& game);