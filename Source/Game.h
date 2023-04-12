#pragma once
#include "Board.h"
#include "Account.h"

using namespace std;

struct Point
{
	int r; //Row
	int c; //Col
};
struct Node
{
	Point p;
	Node* pNext;
};
struct Queue
{
	Node* pHead;
	Node* pTail;
	Queue();

	void addTail(Point data);
	Point getFront();
	void pop();
	int size();
};

struct GameInfo
{
	Board board; 

	int score; 
	int selectedBlocks;
	int remainBlocks; 

	Point p1;			//The first point that has been chosen
	Point p2;			//The second point that has been chosen

	string* background; 

	int mode;		//0: Standard, 1: Insane, 2: Sliding

	GameInfo(int _size);
};
struct Account;

//Visual
void DrawBoardGame(GameInfo& game, bool isSlow, bool isFlip);
void drawBackground(GameInfo& game, Point pokeIndex);
void highlightBoxForBoard(GameInfo& game, Point pokeIndex, int mode);

//Display game and let user play. Return true if game is not done, false if not.
bool ShowMoves(GameInfo& game);

//Change the poke list
void shufflePokeList(GameInfo& game);

//Choose a pokemon from the board.
void ChoosePoke(GameInfo& game, int rowPoke, int colPoke);

//Delete 2 cells that are matching
void DeleteMatching(GameInfo& game);

//Check matching
Queue findPath(Board board, Point p1, Point p2);
int checkMatching(GameInfo& game, Queue& path);
void drawMatchingLine(const GameInfo& game, Queue path, bool isDraw);

//Move suggestion
bool moveSuggestion(GameInfo game, Point& p1, Point& p2);
void showSuggestMove(GameInfo& game);

//Background
string* createBackground(string fileName, const Board& board);
GameInfo createGameFromAccount(Account account);

// Release
void releaseGame(GameInfo& game);
void releaseQueue(Queue& list);