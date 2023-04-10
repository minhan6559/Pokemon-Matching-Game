#include "Menu.h"
#include "Board.h"
#include "Game.h"
#include <Windows.h>
#include <ctime>
#include <cstdlib>
#include <conio.h>

void releaseBoard(Board& board)
{
	for (int i = 0; i < board.size; i++)
		delete[] board.pokeList[i];
	delete[] board.pokeList;
	board.pokeList = NULL;
}

void randomPokemons(Board& board) {
	// Seed the random number generator
	srand((unsigned int)time(NULL));

	// Get the size of the board
	int size = board.size;

	// Allocate memory for the pokeList
	board.pokeList = new int* [size];
	for (int i = 0; i < size; i++)
		board.pokeList[i] = new int[size];

	// Allocate memory for the checkDuplicate and pos arrays 
	bool* checkDuplicate = new bool[size * size];
	int* pos = new int[size * size];

	// Allocate memory for the pokemons array and initialize it to 0
	int** pokemons = new int* [size];
	for (int i = 0; i < size; i++)
	{
		pokemons[i] = new int[size];
		for (int j = 0; j < size; j++)
		{
			pokemons[i][j] = 0;
		}
	}

	// Generate random pokemons and put them next to each other
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j = j + 2) {
			pokemons[i][j] = rand() % 26 + 65;
			pokemons[i][j + 1] = pokemons[i][j];
		}
	}

	// Generate random positions for the pokemons
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

	// Construct the pokemons matrix from the pos array 
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int r = pos[size * i + j] / size;
			int c = pos[size * i + j] % size;
			board.pokeList[i][j] = pokemons[r][c];
		}
	}

	// Deallocate memory
	delete[] pos;
	pos = NULL;
	delete[] checkDuplicate;
	checkDuplicate = NULL;

	for (int i = 0; i < size; i++)
	{
		delete[] pokemons[i];
	}
	delete[] pokemons;
	pokemons = NULL;
}

void DrawBorder(Board board)
{
	int x = board.xBoardStart, y = board.yBoardStart;
	int size = board.size;
	int borderLength = (board.boxLength + 1) * board.size + 3;
	int borderWidth = (board.boxWidth) * board.size + 2;
	DrawBox(x - 2, y - 1, borderLength, borderWidth);
}

void DrawBoardGame(GameInfo& game, bool isSlow, bool isFlip)
{
	DrawBorder(game.board);

	if (game.board.size == 4)
	{
		SetColor(BLACK, LAQUA);
		DrawInfoBoard(90, 4, game.score, "Easy");
	}
	else
	{
		SetColor(BLACK, LRED);
		DrawInfoBoard(90, 4, game.score, "Hard");
	}

	if (game.mode == 0)
	{
		SetColor(BLACK, LAQUA);
		DrawMode(90, 4, "Standard");
	}
	else if (game.mode == 1)
	{
		SetColor(BLACK, LRED);
		DrawMode(90, 4, "Insane");
	}
	else
	{
		SetColor(BLACK, LYELLOW);
		DrawMode(90, 4, " Sliding");
	}

	SetColor(BLACK, WHITE);
	int boxLength = game.board.boxLength, boxWidth = game.board.boxWidth;
	int x = game.board.xBoardStart, y = game.board.yBoardStart;
	int size = game.board.size;
	for (int i = 0; i < size; i++)
	{

		if (i % 2 == 0)
		{
			for (int j = 0; j < size; j++)
			{
				if (game.board.pokeList[i][j] == 32)
				{
					Point pokeIndex = { i, j };
					drawBackground(game, pokeIndex);
					continue;
				}
				string pokemon = "|";
				int pokeColor = LRED;
				if (!(game.mode == 1 && isFlip == 0))
				{
					pokemon = char(game.board.pokeList[i][j]);
					pokeColor = game.board.pokeList[i][j] % 15 + 1;
				}
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
				if (game.board.pokeList[i][j] == 32)
				{
					Point pokeIndex = { i, j };
					drawBackground(game, pokeIndex);
					continue;
				}
				string pokemon = "|";
				int pokeColor = LRED;
				if (!(game.mode == 1 && isFlip == 0))
				{
					pokemon = char(game.board.pokeList[i][j]);
					pokeColor = game.board.pokeList[i][j] % 15 + 1;
				}
				SetColor(BLACK, pokeColor);
				CreateTextBox(x + (boxLength + 1) * j, y + boxWidth * i, 11, 5, pokemon);
				if (isSlow)
					Sleep(50);
			}
		}
	}
	SetColor(BLACK, WHITE);
}

bool ShowMoves(GameInfo& game)
{
	char key;
	Point pokeCur = { 0, 0 };

	while (true)
	{
		// 2 temp points are used to check if there are any moves left
		Point checkMove1;
		Point checkMove2;

		//check if there are no moves left, then shuffle
		if (moveSuggestion(game, checkMove1, checkMove2) == 0)
		{
			do
			{
				shufflePokeList(game);
			} while (moveSuggestion(game, checkMove1, checkMove2) == 0);


			system("cls");
			DrawBoardGame(game, 1, 1);
			if (game.mode == 1)
			{
				Sleep(1000);
				DrawBoardGame(game, 0, 0);
			}
			DrawStatus(90, 4, "Out of Moves. Shuffled!");
		}

		highlightBoxForBoard(game, pokeCur, 1);

		Point pokePrev = pokeCur;

		key = _getch();
		//check if the user presses up, down, left, or right
		if ((key == UP || key == 'w' || key == 'W') && pokeCur.r > 0)
		{
			SelectingSound();
			pokeCur.r--;
			//check if the previous position is not the same as the current position of the two pokemons
			if (!(pokePrev.r == game.p1.r && pokePrev.c == game.p1.c) &&
				!(pokePrev.r == game.p2.r && pokePrev.c == game.p2.c))
			{
				highlightBoxForBoard(game, pokePrev, 0);
			}
			highlightBoxForBoard(game, pokeCur, 1);
		}
		else if ((key == DOWN || key == 's' || key == 'S') && pokeCur.r < game.board.size - 1)
		{
			SelectingSound();
			pokeCur.r++;
			if (!(pokePrev.r == game.p1.r && pokePrev.c == game.p1.c) &&
				!(pokePrev.r == game.p2.r && pokePrev.c == game.p2.c))
			{
				highlightBoxForBoard(game, pokePrev, 0);
			}
			highlightBoxForBoard(game, pokeCur, 1);
		}
		else if ((key == LEFT || key == 'a' || key == 'A') && pokeCur.c > 0)
		{
			SelectingSound();
			pokeCur.c--;
			if (!(pokePrev.r == game.p1.r && pokePrev.c == game.p1.c) &&
				!(pokePrev.r == game.p2.r && pokePrev.c == game.p2.c))
			{
				highlightBoxForBoard(game, pokePrev, 0);
			}
			highlightBoxForBoard(game, pokeCur, 1);
		}
		else if ((key == RIGHT || key == 'd' || key == 'D') && pokeCur.c < game.board.size - 1)
		{
			SelectingSound();
			pokeCur.c++;
			if (!(pokePrev.r == game.p1.r && pokePrev.c == game.p1.c) &&
				!(pokePrev.r == game.p2.r && pokePrev.c == game.p2.c))
			{
				highlightBoxForBoard(game, pokePrev, 0);
			}
			highlightBoxForBoard(game, pokeCur, 1);
		}
		//check if the user presses enter or space
		else if (key == ENTER || key == ' ')
		{
			ChoosePoke(game, pokeCur.r, pokeCur.c);
		}
		//check if the user presses F or f
		else if (key == 'F' || key == 'f')
		{
			SelectingSound();
			showSuggestMove(game);
			game.score -= 2;
			if (game.score < 0)
			{
				game.score = 0;
			}
			DrawStatus(90, 4, "Suggest Move!");
			DrawScore(90, 4, game.score);
		}
		//check if the user presses r or R
		else if (key == 'r' || key == 'R')
		{
			SelectingSound();
			shufflePokeList(game);
			DrawBoardGame(game, 0, 1);
			if (game.mode == 1)
			{
				Sleep(1000);
				DrawBoardGame(game, 0, 0);
			}
			game.score -= 2;
			if (game.score < 0)
			{
				game.score = 0;
			}
			DrawStatus(90, 4, "Shuffled!");
			DrawScore(90, 4, game.score);
		}
		//check if the user presses x or X
		else if (key == 'x' || key == 'X')
		{
			DrawStatus(90, 4, "Saved! Press any key!");
			return true;
		}
		//check if there are no remaining blocks
		if (game.remainBlocks == 0)
		{
			DrawStatus(90, 4, "You win! Press any key!");
			DrawWinScreen();
			return false;
		}
	}
}

void ChoosePoke(GameInfo& game, int rowPoke, int colPoke)
{
	//Check if the pokemon is empty
	if (game.board.pokeList[rowPoke][colPoke] == ' ')
	{
		ErrorSound();
		return;
	}
	//If no pokemon has been selected yet
	if (game.selectedBlocks == 0)
	{
		ChoosedSound();
		game.p1.r = rowPoke;
		game.p1.c = colPoke;
		game.selectedBlocks++;
	}
	//If one pokemon has been selected
	else if (game.selectedBlocks == 1)
	{
		game.p2.r = rowPoke;
		game.p2.c = colPoke;
		game.selectedBlocks++;
	}
	//If two pokemon have been selected
	if (game.selectedBlocks == 2)
	{
		Queue path; //Create a queue containing the connecting path

		int checkMove = checkMatching(game, path); //Check if the pokemon match
		//If the pokemon match
		if (checkMove == 1)
		{
			highlightBoxForBoard(game, game.p1, 0); //Highlight pokemon 1
			highlightBoxForBoard(game, game.p2, 0); //Highlight pokemon 2
			drawMatchingLine(game, path, 1); //Draw matching line
			CorrectSound();
			Sleep(500);
			drawMatchingLine(game, path, 0); //Erase matching line
			DeleteMatching(game); //Delete matching pokemon

			//If the game is in insane mode
			if (game.mode == 1)
			{
				DrawBoardGame(game, 0, 1);
				Sleep(1000);
				DrawBoardGame(game, 0, 0);
			}

			int sizePath = path.size(); //Get size of queue

			//If the size of queue is 2
			if (sizePath == 2)
			{
				game.score++; //Increase score
				DrawStatus(90, 4, "I Matching"); //Draw status
			}
			//If the size of queue is 3
			else if (sizePath == 3)
			{
				game.score += 2; //Increase score
				DrawStatus(90, 4, "L Matching"); //Draw status
			}
			//If the size of queue is 4
			else if (sizePath == 4)
			{
				game.score += 3; //Increase score
				DrawStatus(90, 4, "U or Z Matching"); //Draw status
			}
		}
		//If the pokemon don't match
		else
		{
			ErrorSound(); //Play error sound
			highlightBoxForBoard(game, game.p1, 0); //Highlight pokemon 1

			//If the pokemon don't match
			if (checkMove == 0)
			{
				game.score--;
				//If the score is less than 0
				if (game.score < 0)
				{
					game.score = 0; //Set score to 0
				}
				//If the game is in insane mode
				if (game.mode == 1)
				{
					DrawBoardGame(game, 0, 1);
					Sleep(1000);
					DrawBoardGame(game, 0, 0);
				}
				DrawStatus(90, 4, "Not Matching !"); //Draw status
			}

		}
		DrawScore(90, 4, game.score);
		releaseQueue(path);
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

	game.remainBlocks -= 2;

	if(game.mode != 2)
	{
		drawBackground(game, game.p1);
		drawBackground(game, game.p2);
		game.board.pokeList[game.p1.r][game.p1.c] = 32;
		game.board.pokeList[game.p2.r][game.p2.c] = 32;
	}
	else
	{
		if (game.p1.c < game.p2.c && game.p1.r == game.p2.r)
		{
			int temp = game.p1.c;
			game.p1.c = game.p2.c;
			game.p2.c = temp;
		}

		int size = game.board.size;

		for (int j = game.p1.c; j < size - 1; j++)
		{
			game.board.pokeList[game.p1.r][j] = game.board.pokeList[game.p1.r][j + 1];
		}
		game.board.pokeList[game.p1.r][size - 1] = 32;

		for (int j = game.p2.c; j < size - 1; j++)
		{
			game.board.pokeList[game.p2.r][j] = game.board.pokeList[game.p2.r][j + 1];
		}
		game.board.pokeList[game.p2.r][size - 1] = 32;

		DrawBoardGame(game, 0, 1);
	}
}

void DrawDigit(int x, int y, short digit)
{
	string str;
	if (digit == 0)
	{
		str = ZERO;
	}
	else if (digit == 1)
	{
		str = ONE;
	}
	else if (digit == 2)
	{
		str = TWO;
	}
	else if (digit == 3)
	{
		str = THREE;
	}
	else if (digit == 4)
	{
		str = FOUR;
	}
	else if (digit == 5)
	{
		str = FIVE;
	}
	else if (digit == 6)
	{
		str = SIX;
	}
	else if (digit == 7)
	{
		str = SEVEN;
	}
	else if (digit == 8)
	{
		str = EIGHT;
	}
	else if (digit == 9)
	{
		str = NINE;
	}
	int pos = 0;
	string line;
	GoTo(x, y);
	while ((pos = static_cast<int>(str.find('\n'))) != string::npos) {
		line = str.substr(0, pos);
		cout << line << endl;
		str.erase(0, pos + 1);

		// Set the console cursor position to the next line
		y++;
		GoTo(x, y);
	}
	cout << str;
}

void DrawMode(int x, int y, string mode)
{
	int xStart = x + 31;
	DrawBox(xStart, y, 14, 3);
	int xText = xStart + static_cast<int>((15 - mode.length()) / 2);
	int yText = y + (3 / 2);
	GoTo(xText, yText);
	cout << mode;
	GoTo(x + 35, y);
	SetColor(AQUA, BLACK);
	cout << " MODE ";
	SetColor(BLACK, WHITE);
}

void DrawScore(int x, int y, short score)
{
	for (int i = y + 1; i <= y + 4; i++)
	{
		GoTo(x + 1, i);
		cout << "              "; //14
	}
	int firstDigit = score / 10;
	int secondDigit = score % 10;
	SetColor(BLACK, RED);
	DrawDigit(x + 2, y + 1, firstDigit);
	DrawDigit(x + 8, y + 1, secondDigit);
	SetColor(BLACK, WHITE);
}
void DrawStatus(int x, int y, string status)
{
	GoTo(x + 17, y + 4);
	cout << "                           "; //27
	CreateTextBox(x + 16, y + 3, 29, 3, status);
	GoTo(x + 26, y + 3);
	SetColor(LYELLOW, BLACK);
	cout << " STATUS ";
	SetColor(BLACK, WHITE);
}

void DrawInfoBoard(int x, int y, short score, string level)
{
	//Level
	int xStart = x + 16;
	DrawBox(xStart, y, 14, 3);
	int xText = xStart + static_cast<int>((15 - level.length()) / 2);
	int yText = y + (3 / 2);
	GoTo(xText, yText);
	cout << level;
	GoTo(x + 20, y);
	SetColor(LGREEN, BLACK);
	cout << " LEVEL ";
	SetColor(BLACK, WHITE);

	//status
	DrawStatus(x, y, "");


	//Draw score board
	DrawBox(x, y, 16, 6);
	GoTo(x + 5, y);
	SetColor(LAQUA, BLACK);
	cout << " SCORE ";
	SetColor(BLACK, WHITE);
	DrawScore(x, y, score);

	//Draw Shortcut
	DrawBox(x, y + 7, 26, 5);
	GoTo(x + 8, y + 7);
	SetColor(YELLOW, BLACK);
	cout << " SHORTCUT ";
	SetColor(BLACK, WHITE);
	GoTo(x + 2, y + 8);
	cout << "R";
	cout << ": Shuffle";
	GoTo(x + 2, y + 9);
	cout << "F";
	cout << ": Suggest move";
	GoTo(x + 2, y + 10);
	cout << "X";
	cout << ": Exit and save game";

}


void DrawWinScreen()
{
	const char banner[] = R"(
											 __ __   ___   __ __      __    __  ____  ____       __ 
											|  T  T /   \ |  T  T    |  T__T  Tl    j|    \     |  T
											|  |  |Y     Y|  |  |    |  |  |  | |  T |  _  Y    |  |
											|  ~  ||  O  ||  |  |    |  |  |  | |  | |  |  |    |__j
											l___, ||     ||  :  |    l  `  '  ! |  | |  |  |     __ 
											|     !l     !l     |     \      /  j  l |  |  |    |  T
											l____/  \___/  \__,_j      \_/\_/  |____jl__j__j    l__j)";

	for (int i = 1; i <= 5; i++)
	{
		SetColor(BLACK, LRED);
		GoTo(0, 16);
		cout << banner;
		Sleep(200);
		SetColor(BLACK, LYELLOW);
		GoTo(0, 16);
		cout << banner;
		Sleep(200);
	}
	SetColor(BLACK, WHITE);

}
