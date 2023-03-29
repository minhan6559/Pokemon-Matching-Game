#include "Menu.h"
#include "Board.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <cstdlib>

void releaseBoard(Board& board)
{
	for (int i = 0; i < board.size; i++)
		delete[] board.pokeList[i];
	delete[] board.pokeList;
	board.pokeList = nullptr;
}

//Ref: tu ham BoardView::buildBoardData() cua louis
void randomPokemons(Board& board) {
	srand((unsigned int)time(NULL));

	int size = board.size;

	board.pokeList = new int* [size];
	for (int i = 0; i < size; i++)
		board.pokeList[i] = new int[size];

	bool* checkDuplicate = new bool[size * size];
	int* pos = new int[size * size];

	// Random pokemons
	int** pokemons = new int* [size];
	for (int i = 0; i < size; i++)
	{
		pokemons[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			pokemons[i][j] = 0;
		}
	}

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j = j + 2) {
			pokemons[i][j] = rand() % 26 + 65;
			pokemons[i][j + 1] = pokemons[i][j];
		}
	}

	// Random pokemons position 
	for (int i = 0; i < size * size; i++)
		checkDuplicate[i] = 0;
	for (int i = 0; i < size * size; i++) {
		int tmp = 0;
		do {
			tmp = rand() % (size * size);
		} while (checkDuplicate[tmp]);
		checkDuplicate[tmp] = 1;
		pos[i] = tmp;
	}

	// Construct pokemons matrix
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int r = pos[size * i + j] / size;
			int c = pos[size * i + j] % size;
			board.pokeList[i][j] = pokemons[r][c];
		}
	}

	delete[] pos;
	pos = nullptr;
	delete[] checkDuplicate;
	checkDuplicate = nullptr;

	for (int i = 0; i < size; i++)
	{
		delete[] pokemons[i];
	}
	delete[] pokemons;
	pokemons = nullptr;
}

void drawMatchingLine(GameInfo& game, Queue& path, bool isDraw)
{
	int boxLength = game.board.boxLength;
	int boxWidth = game.board.boxWidth;

	int topBoudary = game.board.yBoardStart - 1;
	int bottomBoudary = game.board.yBoardStart + game.board.boxWidth * game.board.size;
	int leftBoudary = game.board.xBoardStart - 2;
	int rightBoudary = game.board.xBoardStart + (game.board.boxLength + 1) * game.board.size;


	Node* pCur = path.pHead->pNext;
	Node* pPrev = path.pHead;

	while (pCur)
	{
		//Start and end are coordinate. R: x, C: y
		Point start = { (boxLength + 1) * (pPrev->p.c + 1) + (boxLength - 1) / 2,
						boxWidth * (pPrev->p.r + 1) + (boxWidth / 2) };
		Point end = { (boxLength + 1) * (pCur->p.c + 1) + (boxLength - 1) / 2,
						boxWidth * (pCur->p.r + 1) + (boxWidth / 2) };

		bool isStart = 1;
		int fromDirection = 0; //1: up, 2: down, 3: left, 4: right
		SetColor(0, 11);

		while (!(start.r == end.r && start.c == end.c))
		{
			if (start.r == end.r)
			{
				if (isStart == 0)
				{
					GoTo(start.r, start.c);
					if (isDraw)
						cout << char(186);
					else
					{
						if (start.c == topBoudary || start.c == bottomBoudary)
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
				if (start.c < end.c)
				{
					start.c++;
					fromDirection = 1;
				}
				else if (start.c > end.c)
				{
					start.c--;
					fromDirection = 2;
				}
				isStart = 0;
			}
			else if (start.c == end.c)
			{
				if (isStart == 0)
				{
					GoTo(start.r, start.c);
					if (isDraw)
						cout << char(205);
					else
					{
						if (start.r == leftBoudary || start.r == rightBoudary)
						{
							SetColor(BLACK, WHITE);
							cout << char (179);
							SetColor(0, 11);
						}
						else
						{
							cout << " ";
						}
					}
				}
				if (start.r < end.r)
				{
					start.r++;
					fromDirection = 3;
				}
				else if (start.r > end.r)
				{
					start.r--;
					fromDirection = 4;
				}
				isStart = 0;
			}
		}
		if (!(end.r == (boxLength + 1) * (game.p2.c + 1) + (boxLength - 1) / 2
			&& end.c == boxWidth * (game.p2.r + 1) + (boxWidth / 2)))
		{
			GoTo(end.r, end.c);
			if (isDraw)
			{
				Point nextEnd = { (boxLength + 1) * (pCur->pNext->p.c + 1) + (boxLength - 1) / 2,
										boxWidth * (pCur->pNext->p.r + 1) + (boxWidth / 2) };

				if (fromDirection == 1)
				{
					if (end.r < nextEnd.r)
						cout << char(200);
					else
						cout << char(188);
				}
				else if (fromDirection == 2)
				{
					if (end.r < nextEnd.r)
						cout << char(201);
					else
						cout << char(187);
				}
				else if (fromDirection == 3)
				{
					if (end.c > nextEnd.c)
						cout << char(188);
					else
						cout << char(187);
				}
				else
				{
					if (end.c > nextEnd.c)
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

	int boxLength = game.board.boxLength;
	int boxWidth = game.board.boxWidth;

	if (moveSuggestion(game, suggestPoint1, suggestPoint2))
	{
		for (int i = 1; i <= 4; i++)
		{
			string pokemon;
			pokemon = char(game.board.pokeList[suggestPoint1.r][suggestPoint1.c]);
			int x = (game.board.boxLength + 1) * (suggestPoint1.c + 1);
			int y = game.board.boxWidth * (suggestPoint1.r + 1);
			HighlightBox(x, y, boxLength, boxWidth, pokemon, i % 2);

			pokemon = char(game.board.pokeList[suggestPoint2.r][suggestPoint2.c]);
			x = (game.board.boxLength + 1) * (suggestPoint2.c + 1);
			y = game.board.boxWidth * (suggestPoint2.r + 1);
			HighlightBox(x, y, boxLength, boxWidth, pokemon, i % 2);
			Sleep(200);
		}
	}
	else
	{
		do
		{
			shufflePokeList(game);
		}while(moveSuggestion(game, suggestPoint1, suggestPoint2) == 0);
		system("cls");
		const char outMove1[] = R"(

      ____        _              __     __  __                        
     / __ \      | |            / _|   |  \/  |                       
    | |  | |_   _| |_      ___ | |_    | \  / | _____   _____  ___    
    | |  | | | | | __|    / _ \|  _|   | |\/| |/ _ \ \ / / _ \/ __|   
    | |__| | |_| | |_    | (_) | |     | |  | | (_) \ V /  __/\__ \   
     \____/ \__,_|\__|    \___/|_|     |_|  |_|\___/ \_/ \___||___/   
        _____ _            __  __ _      _                         
       / ____| |          / _|/ _| |    (_)                        
      | (___ | |__  _   _| |_| |_| | ___ _ _ __   __ _             
       \___ \| '_ \| | | |  _|  _| |/ _ \ | '_ \ / _` |            
       ____) | | | | |_| | | | | | |  __/ | | | | (_| |  _  
      |_____/|_| |_|\__,_|_| |_| |_|\___|_|_| |_|\__, | (_) 
                                                  __/ |            
                                                 |___/             

)";
		cout << outMove1;
		Sleep(700);

		const char outMove2[] = R"(

      ____        _              __     __  __                        
     / __ \      | |            / _|   |  \/  |                       
    | |  | |_   _| |_      ___ | |_    | \  / | _____   _____  ___    
    | |  | | | | | __|    / _ \|  _|   | |\/| |/ _ \ \ / / _ \/ __|   
    | |__| | |_| | |_    | (_) | |     | |  | | (_) \ V /  __/\__ \   
     \____/ \__,_|\__|    \___/|_|     |_|  |_|\___/ \_/ \___||___/   
        _____ _            __  __ _      _                         
       / ____| |          / _|/ _| |    (_)                        
      | (___ | |__  _   _| |_| |_| | ___ _ _ __   __ _             
       \___ \| '_ \| | | |  _|  _| |/ _ \ | '_ \ / _` |            
       ____) | | | | |_| | | | | | |  __/ | | | | (_| |  _   _ 
      |_____/|_| |_|\__,_|_| |_| |_|\___|_|_| |_|\__, | (_) (_)
                                                  __/ |            
                                                 |___/             

)";
		system("cls");
		cout << outMove2;
		Sleep(700);

		const char outMove3[] = R"(

      ____        _              __     __  __                        
     / __ \      | |            / _|   |  \/  |                       
    | |  | |_   _| |_      ___ | |_    | \  / | _____   _____  ___    
    | |  | | | | | __|    / _ \|  _|   | |\/| |/ _ \ \ / / _ \/ __|   
    | |__| | |_| | |_    | (_) | |     | |  | | (_) \ V /  __/\__ \   
     \____/ \__,_|\__|    \___/|_|     |_|  |_|\___/ \_/ \___||___/   
        _____ _            __  __ _      _                         
       / ____| |          / _|/ _| |    (_)                        
      | (___ | |__  _   _| |_| |_| | ___ _ _ __   __ _             
       \___ \| '_ \| | | |  _|  _| |/ _ \ | '_ \ / _` |            
       ____) | | | | |_| | | | | | |  __/ | | | | (_| |  _   _ 	 _ 
      |_____/|_| |_|\__,_|_| |_| |_|\___|_|_| |_|\__, | (_) (_) (_)
                                                  __/ |            
                                                 |___/             

)";
		system("cls");
		cout << outMove3;
		Sleep(700);
		system("cls");
		DrawBoardGame(game.board, 0);

		for (int i = 1; i <= 4; i++)
		{
			string pokemon;
			pokemon = char(game.board.pokeList[suggestPoint1.r][suggestPoint1.c]);
			int x = (game.board.boxLength + 1) * (suggestPoint1.c + 1);
			int y = game.board.boxWidth * (suggestPoint1.r + 1);
			HighlightBox(x, y, boxLength, boxWidth, pokemon, i % 2);

			pokemon = char(game.board.pokeList[suggestPoint2.r][suggestPoint2.c]);
			x = (game.board.boxLength + 1) * (suggestPoint2.c + 1);
			y = game.board.boxWidth * (suggestPoint2.r + 1);
			HighlightBox(x, y, boxLength, boxWidth, pokemon, i % 2);
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



//Hieu----------------------------------------
void DrawBorder(Board board)
{
	int boxLength = board.boxLength, boxWidth = board.boxWidth;
	int x = board.xBoardStart, y = board.yBoardStart;
	int size = board.size;
	int borderLength = (board.boxLength + 1) * board.size + 3;
	int borderWidth = (board.boxWidth) * board.size + 2;
	DrawBox(x - 2, y - 1, borderLength, borderWidth);
}

void DrawBoardGame(Board board, bool isSlow)
{
	DrawBorder(board);
	int boxLength = board.boxLength, boxWidth = board.boxWidth;
	int x = board.xBoardStart, y = board.yBoardStart;
	int size = board.size;
	for (int i = 0; i < size; i++)
	{

		if (i % 2 == 0)
		{
			for (int j = 0; j < size; j++)
			{
				if (board.pokeList[i][j] == 32)
					continue;
				string pokemon;
				pokemon = char(board.pokeList[i][j]);
				int pokeColor = char(board.pokeList[i][j]) % 15 + 1;
				SetColor(BLACK, pokeColor);
				CreateTextBox(x + (boxLength + 1) * j, y + boxWidth * i, 11, 5, pokemon);
				if (isSlow)
					Sleep(50);
			}
		}
		else
		{

			for (int j = size - 1; j >= 0; j--)
			{
				if (board.pokeList[i][j] == 32)
					continue;
				string pokemon;
				pokemon = char(board.pokeList[i][j]);
				int pokeColor = char(board.pokeList[i][j]) % 15 + 1;
				SetColor(BLACK, pokeColor);
				CreateTextBox(x + (boxLength + 1) * j, y + boxWidth * i, 11, 5, pokemon);
				if (isSlow)
					Sleep(50);
			}
		}
	}
	SetColor(BLACK, WHITE);
}

void ShowMoves(GameInfo& game)
{
	int x = game.board.xBoardStart, y = game.board.yBoardStart;

	int boxLength = game.board.boxLength, boxWidth = game.board.boxWidth;

	//boundary
	const int TOPB = y, BOTTOMB = y + boxWidth * (game.board.size - 1),
		LEFTB = x, RIGHTB = x + (boxLength + 1) * (game.board.size - 1);

	char key;
	int rowPoke = 0, colPoke = 0;
	string pokemon;

	int countEnter = 0;

	while (true)
	{
		pokemon = char(game.board.pokeList[rowPoke][colPoke]);
		HighlightBox(x, y, boxLength, boxWidth, pokemon, 1);

		int xPrev = x, yPrev = y;
		int rowPokePrev = rowPoke, colPokePrev = colPoke;

		key = _getch();
		if ((key == UP || key == 'w') && y > TOPB)
		{
			SelectingSound();
			y -= boxWidth;
			rowPoke--;
			if (!(rowPokePrev == game.p1.r && colPokePrev == game.p1.c) &&
				!(rowPokePrev == game.p2.r && colPokePrev == game.p2.c))
			{
				pokemon = char(game.board.pokeList[rowPokePrev][colPokePrev]);
				HighlightBox(xPrev, yPrev, boxLength, boxWidth, pokemon, 0);
			}
			pokemon = char(game.board.pokeList[rowPoke][colPoke]);
			HighlightBox(x, y, boxLength, boxWidth, pokemon, 1);
		}
		else if ((key == DOWN || key == 's') && y < BOTTOMB)
		{
			SelectingSound();
			y += boxWidth;
			rowPoke++;
			if (!(rowPokePrev == game.p1.r && colPokePrev == game.p1.c) &&
				!(rowPokePrev == game.p2.r && colPokePrev == game.p2.c))
			{
				pokemon = char(game.board.pokeList[rowPokePrev][colPokePrev]);
				HighlightBox(xPrev, yPrev, boxLength, boxWidth, pokemon, 0);
			}
			pokemon = char(game.board.pokeList[rowPoke][colPoke]);
			HighlightBox(x, y, boxLength, boxWidth, pokemon, 1);
		}
		else if ((key == LEFT || key == 'a') && x > LEFTB)
		{
			SelectingSound();
			x -= (boxLength + 1);
			colPoke--;
			if (!(rowPokePrev == game.p1.r && colPokePrev == game.p1.c) &&
				!(rowPokePrev == game.p2.r && colPokePrev == game.p2.c))
			{
				pokemon = char(game.board.pokeList[rowPokePrev][colPokePrev]);
				HighlightBox(xPrev, yPrev, boxLength, boxWidth, pokemon, 0);
			}
			pokemon = char(game.board.pokeList[rowPoke][colPoke]);
			HighlightBox(x, y, boxLength, boxWidth, pokemon, 1);
		}
		else if ((key == RIGHT || key == 'd') && x < RIGHTB)
		{
			SelectingSound();
			x += (boxLength + 1);
			colPoke++;
			if (!(rowPokePrev == game.p1.r && colPokePrev == game.p1.c) &&
				!(rowPokePrev == game.p2.r && colPokePrev == game.p2.c))
			{
				pokemon = char(game.board.pokeList[rowPokePrev][colPokePrev]);
				HighlightBox(xPrev, yPrev, boxLength, boxWidth, pokemon, 0);
			}
			pokemon = char(game.board.pokeList[rowPoke][colPoke]);
			HighlightBox(x, y, boxLength, boxWidth, pokemon, 1);
		}
		else if (key == ENTER)
		{
			ChoosePoke(game, rowPoke, colPoke);
		}
		else if (key == H_Key)
		{
			SelectingSound();
			showSuggestMove(game);
			game.score -= 2;
		}
		else if (key == P_key)
		{
			SelectingSound();
			shufflePokeList(game);
			DrawBoardGame(game.board, 0);
			game.score -= 2;
		}
		if (game.remainBlocks == 0)
		{
			break;
		}
		GoTo(0, 0);
		cout << "                                          ";
		GoTo(0, 0);
		cout << "Score: " << game.score;
	}
}

void ChoosePoke(GameInfo& game, int rowPoke, int colPoke)
{
	if (game.board.pokeList[rowPoke][colPoke] == ' ')
	{
		ErrorSound();
		return;
	}
	if (game.selectedBlocks == 0)
	{
		ChoosedSound();
		game.p1.r = rowPoke;
		game.p1.c = colPoke;
		game.selectedBlocks++;
	}
	else if (game.selectedBlocks == 1)
	{
		game.p2.r = rowPoke;
		game.p2.c = colPoke;
		game.selectedBlocks++;
	}
	if (game.selectedBlocks == 2)
	{
		Queue path;

		int checkMove = checkMatching(game, path);
		if (checkMove == 1)
		{
			int xP1 = game.board.xBoardStart + (game.board.boxLength + 1) * game.p1.c;
			int yP1 = game.board.yBoardStart + game.board.boxWidth * game.p1.r;
			string pokemon;
			pokemon = char(game.board.pokeList[game.p1.r][game.p1.c]);
			HighlightBox(xP1, yP1, game.board.boxLength, game.board.boxWidth, pokemon, 0);

			int xP2 = game.board.xBoardStart + (game.board.boxLength + 1) * game.p2.c;
			int yP2 = game.board.yBoardStart + game.board.boxWidth * game.p2.r;
			pokemon = char(game.board.pokeList[game.p2.r][game.p2.c]);
			HighlightBox(xP2, yP2, game.board.boxLength, game.board.boxWidth, pokemon, 0);
			drawMatchingLine(game, path, 1);
			CorrectSound();
			Sleep(500);
			drawMatchingLine(game, path, 0);
			DeleteMatching(game);

			int sizePath = path.size();

			if (sizePath == 2)
				game.score++;
			else if (sizePath == 3)
				game.score += 2;
			else if (sizePath == 4)
				game.score += 3;
		}
		else
		{
			ErrorSound();
			int xP1 = game.board.xBoardStart + (game.board.boxLength + 1) * game.p1.c;
			int yP1 = game.board.yBoardStart + game.board.boxWidth * game.p1.r;
			string pokemon;
			pokemon = char(game.board.pokeList[game.p1.r][game.p1.c]);
			HighlightBox(xP1, yP1, game.board.boxLength, game.board.boxWidth, pokemon, 0);
			
			if (checkMove == 0)
			{
				game.score--;
			}
		}
		path.~Queue();
		game.selectedBlocks = 0;
		game.p1.r = -1;
		game.p1.c = -1;
		game.p2.r = -1;
		game.p2.c = -1;
	}
}

void DeleteMatching(GameInfo& game)
{
	int x = game.board.xBoardStart, y = game.board.yBoardStart;
	int boxLength = game.board.boxLength, boxWidth = game.board.boxWidth;

	int xP1 = x + (boxLength + 1) * game.p1.c;
	int yP1 = y + boxWidth * game.p1.r;
	int xP2 = x + (boxLength + 1) * game.p2.c;
	int yP2 = y + boxWidth * game.p2.r;

	for (int j = yP1; j < yP1 + boxWidth; j++)
	{
		GoTo(xP1, j);
		cout << "           "; //boxLength
	}
	for (int j = yP2; j < yP2 + boxWidth; j++)
	{
		GoTo(xP2, j);
		cout << "           "; //boxLength
	}
	game.board.pokeList[game.p1.r][game.p1.c] = 32;
	game.board.pokeList[game.p2.r][game.p2.c] = 32;

	game.p1.r = -1;
	game.p1.c = -1;
	game.p2.r = -1;
	game.p2.c = -1;

	game.remainBlocks -= 2;
}