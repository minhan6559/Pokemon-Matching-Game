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
				SetColor(WHITE, BLACK);
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
		if (key == UP && y > TOPB && i > 0) //UP
		{
			y -= 3;
			HighlightBox(x, yPrev, 30, 3, option[i], 0);
			HighlightBox(x, y, 30, 3, option[--i], 1);
			choose++;
		}
		else if (key == DOWN && y < BOTTOMB && i <= 2) //DOWN
		{
			y += 3;
			HighlightBox(x, yPrev, 30, 3, option[i], 0);
			HighlightBox(x, y, 30, 3, option[++i], 1);
			choose--;
		}
		else if (key == ENTER)
		{
			return choose;
		}
	}
}

void MainMenu()
{
	int choose;
	do
	{
		system("cls");
		for (int i = 1; i < 16; i++)
		{
			system("cls");
			SetColor(BLACK, i);
			cout << gameName;
			Sleep(70);
		}
		//SetColor(BLACK, WHITE);

		GoTo(44, 14);
		cout << "made by MINH AN & HO HIEU";

		choose = ShowMainMenu(42, 18);
		if (choose == 3)
		{
			GameInfo game(4);
			system("cls");
			DrawBoardGame(game.board);
			ShowMoves(game);
			system("pause");
			game.board.~Board();
		}
		if (choose == 2)
		{
			system("cls");
			cout << "LeaderBoard\n";
			system("pause");
		}
		if (choose == 1)
		{
			system("cls");
			cout << "Rules";
			system("pause");
		}
		if (choose == 0)
		{
			system("cls");
			cout << "Byee";
			system("pause");
		}
	} while (choose);

}