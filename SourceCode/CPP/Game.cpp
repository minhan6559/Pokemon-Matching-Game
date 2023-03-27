#include "Game.h"

Queue::Queue()
{
	pHead = nullptr;
	pTail = nullptr;
}
void releaseQueue(Queue& list)
{
	while (!list.pHead)
		list.pop_front();
}
Node* createNode(Point data)
{
	Node* temp = new Node;
	temp->p = data;
	temp->pNext = nullptr;
	return temp;
}
void Queue::pushTail(Point data)
{
	Node* temp = createNode(data);
	if (!pHead)
	{
		pHead = temp;
		pTail = temp;
		return;
	}

	pTail->pNext = temp;
	pTail = temp;
}
Point Queue::front()
{
	return pHead->p;
}
void Queue::pop_front()
{
	if (pHead == nullptr) // If the list is already empty
	{
		return;
	}

	Node* nodeToDelete = pHead;
	pHead = pHead->pNext;

	if (pHead == nullptr) // If the list is now empty
	{
		pTail = nullptr;
	}

	delete nodeToDelete;
}
int Queue::size()
{
	int count = 0;

	Node* pCur = pHead;
	while (pCur)
	{
		count++;
		pCur = pCur->pNext;
	}
	return count;
}

//Ref: https://codelearn.io/sharing/huong-dan-lam-game-bang-cocos2d-x-phan-2
Queue findPath(Board board, Point p1, Point p2)
{
	//INIT Graph
	const int size = board.size;
	int** e = new int* [size + 2];
	for (int i = 0; i < size + 2; ++i) {
		e[i] = new int[size + 2];
		for (int j = 0; j < size + 2; ++j)
		{
			e[i][j] = 0;
		}
	}
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			e[i + 1][j + 1] = board.pokeList[i][j] != 32;
		}
	}
	Point s = { p1.r + 1, p1.c + 1 };
	Point t = { p2.r + 1, p2.c + 1 };

	//BFS
	const int dx[4] = { -1, 0, 1, 0 };
	const int dy[4] = { 0, 1, 0, -1 };

	Queue q;
	Point** trace = new Point * [size + 2];
	for (int i = 0; i < size + 2; ++i) {
		trace[i] = new Point[size + 2];
	}
	for (int i = 0; i < size + 2; ++i) {
		for (int j = 0; j < size + 2; ++j) {
			trace[i][j] = { -1, -1 };
		}
	}
	q.pushTail(t);
	trace[t.r][t.c] = { -2, -2 };
	e[s.r][s.c] = 0;
	e[t.r][t.c] = 0;

	while (q.pHead != nullptr) {
		Point u = q.front();
		q.pop_front();
		if (u.r == s.r && u.c == s.c) break;
		for (int i = 0; i < 4; ++i) {
			int x = u.r + dx[i];
			int y = u.c + dy[i];
			while (x >= 0 && x < size + 2 && y >= 0 && y < size + 2 && e[x][y] == 0) {
				if (trace[x][y].r == -1) {
					trace[x][y] = u;
					Point data = { x, y };
					q.pushTail(data);
				}
				x += dx[i];
				y += dy[i];
			}
		}
	}

	//trace back
	Queue res;
	if (trace[s.r][s.c].r != -1) {
		while (s.r != -2) {
			Point data = { s.r - 1, s.c - 1 };
			res.pushTail(data);
			s = trace[s.r][s.c];
		}
	}

	// Free dynamically allocated memory
	for (int i = 0; i < size + 2; ++i) {
		delete[] e[i];
		delete[] trace[i];
	}
	delete[] e;
	delete[] trace;

	return res;
}

GameInfo::GameInfo(int _size)
{
	board.xBoardStart = 12;
	board.yBoardStart = 5;
	board.boxLength = 11;
	board.boxWidth = 5;
	board.size = _size;
	randomPokemons(board);
	score = 0;               
	selectedBlocks = 0;	       
	remainBlocks = _size * _size;
	p1 = { -1, -1 };
	p2 = { -1, -1 };
}

//Check if the two selected blocks are matching and return the path from p1 to p2
//-2: The same, -1: not selected, 0: not matching, 1: matching
int checkMatching(GameInfo& game, Queue& path)
{
	//1 trong 2 block chua duoc chon
	if (game.p1.r == -1 || game.p2.r == -1)
		return -1;

	//2 block duoc chon la 1 block
	if (game.p1.r == game.p2.r && game.p1.c == game.p2.c)
		return -2;

    if (game.board.pokeList[game.p1.r][game.p1.c] == 32 || game.board.pokeList[game.p2.r][game.p2.c] == 32)
    {
        return 0;
    }

    //2 block duoc chon co Poke giong nhau
    if (game.board.pokeList[game.p1.r][game.p1.c] == game.board.pokeList[game.p2.r][game.p2.c])
    {
        path = findPath(game.board, game.p1, game.p2);
        int pathSize = path.size();
        //Co duong di thoa man
        if (pathSize >= 2 && pathSize <= 4)
        {
            return 1;
        }
        //Khong co duong di thoa man
        else
        {
            return 0;
        }
    }
    //2 block duoc chon co Poke khac nhau
    else
    {
        return 0;
    }
}

// Check if there is any matching block
bool moveSuggestion(GameInfo game, Point& p1, Point& p2)
{
    int size = game.board.size;

    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            game.p1 = { i, j };
            if (game.board.pokeList[i][j] == -1)
                continue;
            
            for (int k = 0; k < size; k++)
            {
                for (int l = 0; l < size; l++)
                {
					game.p2 = { k, l };
                    if (game.board.pokeList[k][l] == -1)
                        continue;
					Queue path;
                    if (checkMatching(game, path) == 1)
                    {
						p1 = { i, j };
						p2 = { k, l };
						return 1;
					}
				}
			}
		}
	}
    return 0;
}