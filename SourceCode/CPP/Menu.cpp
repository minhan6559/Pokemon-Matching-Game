#include "menu.h"
#include "Game.h"


void DrawBox(int xStart, int yStart, int length, int width)
{
	if (length <= 1 || width <= 1) return;

	GoTo(xStart, yStart);
	for (int iX = 1; iX <= length; iX++)
	{
		cout << char(196);
	}
	GoTo(xStart, yStart + width - 1);
	for (int iX = 1; iX <= length; iX++)
	{
		cout << char(196);
	}
	for (int iY = 0; iY < width; iY++)
	{
		GoTo(xStart, yStart + iY);
		cout << char(179);
	}
	for (int iY = 0; iY < width; iY++)
	{
		GoTo(xStart + length - 1, yStart + iY);
		cout << char(179);
	}
	GoTo(xStart, yStart);
	cout << char(218);
	GoTo(xStart + length - 1, yStart);
	cout << char(191);
	GoTo(xStart, yStart + width - 1);
	cout << char(192);
	GoTo(xStart + length - 1, yStart + width - 1);
	cout << char(217);
}

void CreateTextBox(int xStart, int yStart, int length, int width, string text)
{
	DrawBox(xStart, yStart, length, width);
	int xText = xStart + static_cast<int>((length - text.length()) / 2);
	int yText = yStart + (width / 2);
	SetColor(BLACK, WHITE);
	GoTo(xText, yText);
	cout << text;
}

void HighlightBox(int xStart, int yStart, int length, int width, string text, int mode)
{
	if (mode == 1)
	{
		for (int iY = yStart + 1; iY < yStart + width - 1; iY++)
		{
			for (int iX = xStart + 1; iX < xStart + length - 1; iX++)
			{
				GoTo(iX, iY);
				//SetColor(WHITE, BLACK);
				SetColor(LAQUA, BLACK);
				cout << " ";
			}
		}
		int xText = xStart + static_cast<int>((length - text.length()) / 2);
		int yText = yStart + (width / 2);
		GoTo(xText, yText);
		cout << text;
	}
	else if (mode == 0)
	{
		for (int iY = yStart + 1; iY < yStart + width - 1; iY++)
		{
			for (int iX = xStart + 1; iX < xStart + length - 1; iX++)
			{
				GoTo(iX, iY);
				SetColor(BLACK, WHITE);
				cout << " ";
			}
		}
		int xText = xStart + static_cast<int>((length - text.length()) / 2);
		int yText = yStart + (width / 2);
		GoTo(xText, yText);
		cout << text;
	}
	else if (mode == 2)
	{
		for (int iY = yStart + 1; iY < yStart + width - 1; iY++)
		{
			for (int iX = xStart + 1; iX < xStart + length - 1; iX++)
			{
				GoTo(iX, iY);
				SetColor(LAQUA, WHITE);
				cout << " ";
			}
		}
		int xText = xStart + static_cast<int>((length - text.length()) / 2);
		int yText = yStart + (width / 2);
		GoTo(xText, yText);
		cout << text;
	}

	SetColor(BLACK, WHITE);
}


//References: https://www.youtube.com/watch?v=oDh046cT_Q0&t=1474s
int ShowMainMenu(int x, int y)
{
	string option[4] = { "Start", "Leaderboard", "Rules", "Exit" };
	CreateTextBox(x, y, 30, 3, option[0]);
	CreateTextBox(x, y + 3, 30, 3, option[1]);
	CreateTextBox(x, y + 6, 30, 3, option[2]);
	CreateTextBox(x, y + 9, 30, 3, option[3]);
	//boundary
	const int TOPB = y, BOTTOMB = y + 9;

	char key;
	int i = 0;
	int choose = 3;
	HighlightBox(x, y, 30, 3, option[0], 1);
	while (true)
	{
		int xPrev = x, yPrev = y;
		key = _getch();
		if ((key == UP || key == 'w') && y > TOPB && i > 0) //UP
		{
			SelectingSound();
			y -= 3;
			HighlightBox(x, yPrev, 30, 3, option[i], 0);
			HighlightBox(x, y, 30, 3, option[--i], 1);
			choose++;
		}
		else if ((key == DOWN || key == 's') && y < BOTTOMB && i <= 2) //DOWN
		{
			SelectingSound();
			y += 3;
			HighlightBox(x, yPrev, 30, 3, option[i], 0);
			HighlightBox(x, y, 30, 3, option[++i], 1);
			choose--;
		}
		else if (key == ENTER)
		{
			ChoosedSound();
			return choose;
		}
	}
}

void MainMenu()
{
	srand((unsigned int)time(NULL));
	SetUpConsole();
	bool isBegin = 1;
	int choose;
	do
	{	
		system("cls");

		for (int i = 1; i < 10; i++)
		{
			int color = rand() % 14 + 1;
			system("cls");
			SetColor(BLACK, color);
			cout << gameName;
			if (!isBegin)
			{
				break;
			}
			Sleep(100);
		}
		SetColor(BLACK, WHITE);

		GoTo(44, 14);
		cout << "made by ";
		SetColor(BLACK, LAQUA);
		cout << "MINH AN ";
		SetColor(BLACK, WHITE);
		cout << "& ";
		SetColor(BLACK, LGREEN);
		cout << "HO HIEU";
		SetColor(BLACK, WHITE);

		isBegin = 0;
		choose = ShowMainMenu(42, 18);
		if (choose == 3)
		{
			system("cls");
			ChooseLevel(42, 18);
		}
		if (choose == 2)
		{
			system("cls");
			cout << "Not Updated\n";
			system("pause");
		}
		if (choose == 1)
		{
			system("cls");
			ShowRules();
			_getch();
		}
		if (choose == 0)
		{
			system("cls");
			cout << "Byee\n";
			system("pause");
		}
	} while (choose);
}

void ChooseLevel(int x, int y)
{
	SetColor(BLACK, rand() % 14 + 1);
	cout << gameName;
	SetColor(BLACK, WHITE);

	GoTo(44, 14);
	cout << "made by ";
	SetColor(BLACK, LAQUA);
	cout << "MINH AN ";
	SetColor(BLACK, WHITE);
	cout << "& ";
	SetColor(BLACK, LGREEN);
	cout << "HO HIEU";
	SetColor(BLACK, WHITE);

	string option[] = { "Easy", "Hard", "Exit" };
	CreateTextBox(x, y, 30, 3, option[0]);
	CreateTextBox(x, y + 3, 30, 3, option[1]);
	CreateTextBox(x, y + 6, 30, 3, option[2]);
	//boundary
	const int TOPB = y, BOTTOMB = y + 6;

	char key;
	int i = 0;
	int choose = 2;
	HighlightBox(x, y, 30, 3, option[0], 1);
	while (true)
	{
		int xPrev = x, yPrev = y;
		key = _getch();
		if ((key == UP || key == 'w') && y > TOPB && i > 0) //UP
		{
			SelectingSound();
			y -= 3;
			HighlightBox(x, yPrev, 30, 3, option[i], 0);
			HighlightBox(x, y, 30, 3, option[--i], 1);
			choose++;
		}
		else if ((key == DOWN || key == 's') && y < BOTTOMB && i <= 1) //DOWN
		{
			SelectingSound();
			y += 3;
			HighlightBox(x, yPrev, 30, 3, option[i], 0);
			HighlightBox(x, y, 30, 3, option[++i], 1);
			choose--;
		}
		else if (key == ENTER)
		{
			ChoosedSound();
			if (choose == 2)
			{
				GameInfo game(4);
				system("cls");
				DrawBoardGame(game.board, 1);
				ShowMoves(game);
				system("pause");
				game.board.~Board();
				return;
			}
			if (choose == 1)
			{
				GameInfo game(6);
				system("cls");
				DrawBoardGame(game.board, 1);
				ShowMoves(game);
				system("pause");
				game.board.~Board();
				return;
			}
			if (choose == 0)
			{
				ChoosedSound();
				return;
			}
		}
	}
}

void ShowRules()
{
	SetColor(BLACK, LAQUA);
	cout << R"(
                                                                            ____  __  ____    ___________
                                                                           / __ \/ / / / /   / ____/ ___/
                                                                          / /_/ / / / / /   / __/  \__ \ 
                                                                         / _, _/ /_/ / /___/ /___ ___/ / 
                                                                        /_/ |_|\____/_____/_____//____/  
                                 
)";

	DrawBox(24, 10, 130, 8);
	DrawBox(24, 17, 130, 8);
	DrawBox(24, 24, 130, 8);
	GoTo(24, 17);
	cout << char(195);
	GoTo(24, 24);
	cout << char(195);
	GoTo(153, 17);
	cout << char(180);
	GoTo(153, 24);
	cout << char(180);

	GoTo(85, 10);
	SetColor(LGREEN, BLACK);
	cout << " OVERALL ";
	SetColor(BLACK ,WHITE);

	GoTo(27, 12);
	cout << char(175) <<  " The Matching Game(commonly known as Pikachu Puzzle Game) includes a board of \
multiple cells, each of whichpresents a figure.\n";
	GoTo(27, 13);
	cout << char(175) << " The player finds and matches a pair of cells that contain the same \
figure and connect each other in some particular pattern.\n";
	GoTo(27, 14);
	cout << char(175) << " A legal match will make the two cells disappear. The game ends when all matching\
pairs are found.\n";

	GoTo(85, 17);
	SetColor(LYELLOW, BLACK);
	cout << " MOVING ";
	SetColor(BLACK, WHITE);

	GoTo(30, 19);
	cout << char(175) << " Press W A S D or UP DOWN LEFT RIGHT arows to move.\n";
	GoTo(30, 21);
	cout << char(175) << " Press Enter to select.\n";
	GoTo(100, 19);
	cout << char(175) << " Press H to suggest moving.\n";
	GoTo(100, 21);
	cout << char(175) << " Press P to shuffle.\n";


	GoTo(85, 24);
	SetColor(LAQUA, BLACK);
	cout << " SCORING ";
	SetColor(BLACK, WHITE);

	GoTo(30, 26);
	cout << char(175) << " I matching: 1 point.\n";
	GoTo(30, 28);
	cout << char(175) << " L matching: 2 point.\n";
	GoTo(100, 26);
	cout << char(175) << " Z or U matching: 3 point.\n";
	GoTo(100, 28);
	cout << char(175) << " Suggest move or Shuffle: -2 point.\n";
}