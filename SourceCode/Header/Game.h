#pragma once
#include "Board.h"
#include <iostream>
using namespace std;

struct Board;
struct Point
{
    int r; //Row
    int c; //Col
};
struct Trace
{
    Point parent;
    bool visited;
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

    GameInfo(int _size);
};

int checkMatching(GameInfo& game, Queue& path);
bool moveSuggestion(GameInfo game, Point& p1, Point& p2);

void releaseQueue(Queue& list);
Queue findPath(Board board, Point p1, Point p2);