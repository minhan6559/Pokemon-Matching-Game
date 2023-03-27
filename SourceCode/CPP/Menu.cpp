#include "menu.h"


char gameName[] = R"(
                                  ,'\
    _.----.        ____         ,'  _\   ___    ___     ____
_,-'       `.     |    |  /`.   \,-'    |   \  /   |   |    \  |`.
\      __    \    '-.  | /   `.  ___    |    \/    |   '-.   \ |  |
 \.    \ \   |  __  |  |/    ,','_  `.  |          | __  |    \|  |
   \    \/   /,' _`.|      ,' / / / /   |          ,' _`.|     |  |
    \     ,-'/  /   \    ,'   | \/ / ,`.|         /  /   \  |     |
     \    \ |   \_/  |   `-.  \    `'  /|  |    ||   \_/  | |\    |
      \    \ \      /       `-.`.___,-' |  |\  /| \      /  | |   |
       \    \ `.__,'|  |`-._    `|      |__| \/ |  `.__,'|  | |   |
        \_.-'       |__|    `-._ |              '-.|     '-.| |   |
                                `'                            '-._|
)";

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
	int xText = xStart + (length - text.length()) / 2;
	int yText = yStart + (width / 2);
	GoTo(xText, yText);
	cout << text;
}

void HighlightBox(int xStart, int yStart, int length, int width, string text, bool check)
{
	if (check)
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
		int xText = xStart + (length - text.length()) / 2;
		int yText = yStart + (width / 2);
		GoTo(xText, yText);
		cout << text;
	}
	else
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
		int xText = xStart + (length - text.length()) / 2;
		int yText = yStart + (width / 2);
		GoTo(xText, yText);
		cout << text;
	}
	SetColor(BLACK, WHITE);
}


//References: https://www.youtube.com/watch?v=oDh046cT_Q0&t=1474s
int ShowMainMenu()
{
	string option[] = { "Start", "Leaderboard", "Rules", "Exit" };
	CreateTextBox(5, 5, 30, 3, option[0]);
	CreateTextBox(5, 8, 30, 3, option[1]);
	CreateTextBox(5, 11, 30, 3, option[2]);
	CreateTextBox(5, 14, 30, 3, option[3]);

	char key;
	int x = 5, y = 5;
	int i = 0;
	int choose = 2;
	HighlightBox(x, y, 30, 3, option[0], 1);
	while (true)
	{
		int xPrev = x, yPrev = y;
		key = _getch();
		if (key == UP && y > 5 && i > 0) //UP
		{
			y -= 3;
			HighlightBox(x, yPrev, 30, 3, option[i], 0);
			HighlightBox(x, y, 30, 3, option[--i], 1);
			choose++;
		}
		else if (key == DOWN && y < 14 && i < 3) //DOWN
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

