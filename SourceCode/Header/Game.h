#pragma once
#include "Board.h"
#include "Account.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Board;
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

Queue findPath(Board board, Point p1, Point p2);
int checkMatching(GameInfo& game, Queue& path);
bool moveSuggestion(GameInfo game, Point& p1, Point& p2);
string* createBackground(string fileName, const Board& board);
GameInfo createGameFromAccount(Account account);

void releaseGame(GameInfo& game);
void releaseQueue(Queue& list);