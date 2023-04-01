#pragma once
#include "Board.h"
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
    
    void pushTail(Point data);
    Point front();
    void pop_front();
    int size();
};

struct GameInfo
{
    Board board;
    int score;
    int selectedBlocks;
    int remainBlocks;
    Point p1;
    Point p2;
    string* background;
    GameInfo(int _size);
};

Queue findPath(Board board, Point p1, Point p2);
int checkMatching(GameInfo& game, Queue& path);
bool moveSuggestion(GameInfo game, Point& p1, Point& p2);
void createBackground(string fileName, string*& background, const Board& board);

void releaseGame (GameInfo& game);
void releaseQueue(Queue& list);