#include "Game.h"

Queue::Queue()
{
	pHead = NULL;
	pTail = NULL;
}
void releaseQueue(Queue& list)
{
	while (list.pHead)
		list.pop();
}

Node* createNode(Point data)
{
	Node* temp = new Node;
	temp->p = data;
	temp->pNext = NULL;
	return temp;
}
void Queue::addTail(Point data)
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
Point Queue::getFront()
{
	return pHead->p;
}
void Queue::pop()
{
	if (pHead == NULL) // If the list is already empty
	{
		return;
	}

	Node* nodeToDelete = pHead;
	pHead = pHead->pNext;

	if (pHead == NULL) // If the list is now empty
	{
		pTail = NULL;
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
		for (int j = 0; j < size + 2; ++j) {
			trace[i][j] = { -1, -1 };
		}
	}

	q.addTail(t);
	trace[t.r][t.c] = { -2, -2 };
	e[s.r][s.c] = 0;
	e[t.r][t.c] = 0;

	while (q.pHead != NULL) {
		Point u = q.getFront();
		q.pop();
		if (u.r == s.r && u.c == s.c) break;
		for (int i = 0; i < 4; ++i) {
			int x = u.r + dx[i];
			int y = u.c + dy[i];
			while (x >= 0 && x < size + 2 && y >= 0 && y < size + 2 && e[x][y] == 0) {
				if (trace[x][y].r == -1) {
					trace[x][y] = u;
					Point data = { x, y };
					q.addTail(data);
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
			res.addTail(data);
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
	mode = 0;
	randomPokemons(board);
	score = 0;
	selectedBlocks = 0;
	remainBlocks = _size * _size;
	p1 = { -1, -1 };
	p2 = { -1, -1 };

	if (_size == 6)
		background = createBackground("Background\\Hard.txt", board);
	else if (_size == 4)
		background = createBackground("Background\\Easy.txt", board);
}

//Check if the two selected blocks satisfy the conditions and return the path from p1 to p2 if they are matching
//-1: The same, 0: not matching, 1: matching
int checkMatching(GameInfo& game, Queue& path)
{
	//2 blocks are the same
	if (game.p1.r == game.p2.r && game.p1.c == game.p2.c)
		return -1;

	if (game.board.pokeList[game.p1.r][game.p1.c] == 32 || game.board.pokeList[game.p2.r][game.p2.c] == 32)
	{
		return 0;
	}

	//2 blocks have the same pokemon
	if (game.board.pokeList[game.p1.r][game.p1.c] == game.board.pokeList[game.p2.r][game.p2.c])
	{
		path = findPath(game.board, game.p1, game.p2);
		int pathSize = path.size();
		//Acceptable path
		if (pathSize >= 2 && pathSize <= 4)
		{
			return 1;
		}
		//Unacceptable path
		else
		{
			return 0;
		}
	}
	//2 blocks has different pokemon
	else
	{
		return 0;
	}
}

// Check if there is any matching block and return a valid pair of blocks
bool moveSuggestion(GameInfo game, Point& p1, Point& p2)
{
	int size = game.board.size;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			game.p1 = { i, j };
			if (game.board.pokeList[i][j] == 32)
				continue;

			for (int k = 0; k < size; k++)
			{
				for (int l = 0; l < size; l++)
				{
					game.p2 = { k, l };
					if (game.board.pokeList[k][l] == 32)
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


void drawMatchingLine(const GameInfo& game, Queue path, bool isDraw)
{
	int boxLength = game.board.boxLength;
	int boxWidth = game.board.boxWidth;

	int topBoundary = game.board.yBoardStart - 1;
	int bottomBoundary = game.board.yBoardStart + game.board.boxWidth * game.board.size;
	int leftBoundary = game.board.xBoardStart - 2;
	int rightBoundary = game.board.xBoardStart + (game.board.boxLength + 1) * game.board.size;


	Node* pCur = path.pHead->pNext;
	Node* pPrev = path.pHead;

	while (pCur)
	{
		Coor start = { (boxLength + 1) * (pPrev->p.c + 1) + (boxLength - 1) / 2,
						boxWidth * (pPrev->p.r + 1) + (boxWidth / 2) };
		Coor end = { (boxLength + 1) * (pCur->p.c + 1) + (boxLength - 1) / 2,
						boxWidth * (pCur->p.r + 1) + (boxWidth / 2) };

		bool isStart = 1;
		int fromDirection = 0; //1: up, 2: down, 3: left, 4: right
		SetColor(0, 11);

		while (!(start.x == end.x && start.y == end.y))
		{
			if (start.x == end.x)
			{
				if (isStart == 0)
				{
					GoTo(start.x, start.y);
					if (isDraw)
						cout << char(186);
					else
					{
						if (start.y == topBoundary || start.y == bottomBoundary)
						{
							SetColor(BLACK, WHITE);
							cout << char(196);
							SetColor(BLACK, 11);
						}
						else
						{
							cout << " ";
						}
					}
				}
				if (start.y < end.y)
				{
					start.y++;
					fromDirection = 1;
				}
				else if (start.y > end.y)
				{
					start.y--;
					fromDirection = 2;
				}
				isStart = 0;
			}
			else if (start.y == end.y)
			{
				if (isStart == 0)
				{
					GoTo(start.x, start.y);
					if (isDraw)
						cout << char(205);
					else
					{
						if (start.x == leftBoundary || start.x == rightBoundary)
						{
							SetColor(BLACK, WHITE);
							cout << char(179);
							SetColor(0, 11);
						}
						else
						{
							cout << " ";
						}
					}
				}
				if (start.x < end.x)
				{
					start.x++;
					fromDirection = 3;
				}
				else if (start.x > end.x)
				{
					start.x--;
					fromDirection = 4;
				}
				isStart = 0;
			}
		}
		if (!(end.x == (boxLength + 1) * (game.p2.c + 1) + (boxLength - 1) / 2
			&& end.y == boxWidth * (game.p2.r + 1) + (boxWidth / 2)))
		{
			GoTo(end.x, end.y);
			if (isDraw)
			{
				Coor nextEnd = { (boxLength + 1) * (pCur->pNext->p.c + 1) + (boxLength - 1) / 2,
										boxWidth * (pCur->pNext->p.r + 1) + (boxWidth / 2) };

				if (fromDirection == 1)
				{
					if (end.x < nextEnd.x)
						cout << char(200);
					else
						cout << char(188);
				}
				else if (fromDirection == 2)
				{
					if (end.x < nextEnd.x)
						cout << char(201);
					else
						cout << char(187);
				}
				else if (fromDirection == 3)
				{
					if (end.y > nextEnd.y)
						cout << char(188);
					else
						cout << char(187);
				}
				else
				{
					if (end.y > nextEnd.y)
						cout << char(200);
					else
						cout << char(201);
				}
			}
			else
				cout << " ";
		}
		pPrev = pCur;
		pCur = pCur->pNext;

		SetColor(0, 7);
	}
}

void showSuggestMove(GameInfo& game)
{
	Point suggestPoint1;
	Point suggestPoint2;
	if (moveSuggestion(game, suggestPoint1, suggestPoint2))
	{
		for (int i = 1; i <= 4; i++)
		{
			highlightBoxForBoard(game, suggestPoint1, i % 2);
			highlightBoxForBoard(game, suggestPoint2, i % 2);
			Sleep(200);
		}
	}
}

void shufflePokeList(GameInfo& game)
{
	srand((unsigned int)time(NULL));
	// Create a list of indices of non-deleted Pokemon
	int numNonDeleted = 0;
	int* nonDeletedIndices = new int[game.board.size * game.board.size];
	for (int i = 0; i < game.board.size; i++) {
		for (int j = 0; j < game.board.size; j++) {
			if (game.board.pokeList[i][j] != 32) {
				nonDeletedIndices[numNonDeleted] = i * game.board.size + j;
				numNonDeleted++;
			}
		}
	}

	// Shuffle the list of non-deleted indices
	for (int i = numNonDeleted - 1; i > 0; i--) {
		int j = rand() % (i + 1);
		int temp = nonDeletedIndices[i];
		nonDeletedIndices[i] = nonDeletedIndices[j];
		nonDeletedIndices[j] = temp;
	}

	// Update the pokeList array with the shuffled indices
	int index = 0;
	for (int i = 0; i < game.board.size; i++) {
		for (int j = 0; j < game.board.size; j++) {
			if (game.board.pokeList[i][j] != 32) {
				int newIndex = nonDeletedIndices[index];
				int newI = newIndex / game.board.size;
				int newJ = newIndex % game.board.size;
				int temp = game.board.pokeList[i][j];
				game.board.pokeList[i][j] = game.board.pokeList[newI][newJ];
				game.board.pokeList[newI][newJ] = temp;
				index++;
			}
		}
	}

	delete[] nonDeletedIndices;
}

void drawBackground(GameInfo& game, Point pokeIndex)
{
	int boxLength = game.board.boxLength, boxWidth = game.board.boxWidth;

	//Coordinate of the start point to draw on screen
	Coor startDraw = { (boxLength + 1) * (pokeIndex.c + 1),
						boxWidth * (pokeIndex.r + 1) };

	//Index of background
	Point startBackground = { boxWidth * pokeIndex.r,
								(boxLength + 1) * pokeIndex.c };

	GoTo(startDraw.x, startDraw.y);

	for (int i = 0; i < boxWidth; i++)
	{
		GoTo(startDraw.x, startDraw.y + i);
		for (int j = 0; j < boxLength + 1; j++)
		{
			cout << game.background[startBackground.r + i][startBackground.c + j];
		}
	}
}

void highlightBoxForBoard(GameInfo& game, Point pokeIndex, int mode)
{
	int width = game.board.boxWidth, length = game.board.boxLength;

	Coor start = { (length + 1) * (pokeIndex.c + 1),
						width * (pokeIndex.r + 1) };

	if (mode == 1)
	{
		for (int iY = start.y + 1; iY < start.y + width - 1; iY++)
		{
			for (int iX = start.x + 1; iX < start.x + length - 1; iX++)
			{
				GoTo(iX, iY);
				SetColor(LAQUA, BLACK);
				cout << " ";
			}
		}
	}
	else if (mode == 0)
	{
		for (int iY = start.y + 1; iY < start.y + width - 1; iY++)
		{
			for (int iX = start.x + 1; iX < start.x + length - 1; iX++)
			{
				GoTo(iX, iY);
				SetColor(BLACK, WHITE);
				cout << " ";
			}
		}
	}

	if (game.board.pokeList[pokeIndex.r][pokeIndex.c] != 32)
	{
		string text = "|";
		if (game.mode == 0 || game.mode == 2)
			text = char(game.board.pokeList[pokeIndex.r][pokeIndex.c]);
		int xText = start.x + static_cast<int>((length - text.length()) / 2);
		int yText = start.y + (width / 2);
		GoTo(xText, yText);
		cout << text;
	}
	else
	{
		drawBackground(game, pokeIndex);
	}
	SetColor(BLACK, WHITE);
}

//This function creates a background for a game board.
string* createBackground(string fileName, const Board& board)
{
	//Open the file with the given name
	ifstream fin(fileName);
	//Create a new string array with the size of the board
	string* background = new string[board.size * board.boxWidth];

	//Loop through the file until the end of the file is reached
	int i = 0;
	while (!fin.eof())
	{
		//Read a line from the file and store it in the background array
		getline(fin, background[i]);
		i++;
	}

	//Close the file
	fin.close();

	return background;
}


GameInfo createGameFromAccount(Account account)
{
	GameInfo game(account.size);

	releaseBoard(game.board);
	game.board.pokeList = account.curPokeList;
	game.score = account.curScore;

	game.mode = account.mode;

	for (int i = 0; i < account.size; i++)
	{
		for (int j = 0; j < account.size; j++)
		{
			if (game.board.pokeList[i][j] == ' ')
				game.remainBlocks--;
		}
	}

	return game;
}

//This function releases the game by deleting the background and releasing the board
void releaseGame(GameInfo& game)
{
	//Delete the background
	delete[] game.background;
	//Set the background to NULL
	game.background = NULL;
	//Release the board
	releaseBoard(game.board);
}