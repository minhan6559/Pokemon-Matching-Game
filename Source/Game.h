#pragma once
#include "Board.h"
#include "Account.h"

using namespace std;

// Index of the pokemon in matrix
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

	int mode;			//0: Standard, 1: Insane, 2: Sliding

	GameInfo(int _size);
};
struct Account;

//Visual
void DrawBoardGame(GameInfo& game, bool isSlow, bool isFlip);
void drawBackground(GameInfo& game, Point pokeIndex);
void highlightBoxForBoard(GameInfo& game, Point pokeIndex, int mode);

//Display game and let user play. Return true if game is not done, false if not.
bool ShowMoves(GameInfo& game);

//Shuffle the poke list
void shufflePokeList(GameInfo& game);

//Choose a pokemon from the board.
void ChoosePoke(GameInfo& game, int rowPoke, int colPoke);

//Delete 2 cells that are matching
void DeleteMatching(GameInfo& game);

// Find the path from p1 to p2
Queue findPath(Board board, Point p1, Point p2);

//Check if the two selected blocks satisfy the conditions and return the path from p1 to p2 if they are matching
//-1: The same, 0: not matching, 1: matching
int checkMatching(GameInfo& game, Queue& path);

// Draw the connecting line between two blocks
void drawMatchingLine(const GameInfo& game, Queue path, bool isDraw);

// Check if there is any matching block and return a valid pair of blocks
bool moveSuggestion(GameInfo game, Point& p1, Point& p2);

// Show the suggested move
void showSuggestMove(GameInfo& game);

//Background
string* createBackground(string fileName, const Board& board);
GameInfo createGameFromAccount(Account account);

// Release
void releaseGame(GameInfo& game);
void releaseQueue(Queue& list);