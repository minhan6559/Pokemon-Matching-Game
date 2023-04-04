#include "Menu.h"
#include "Game.h"
#include <ctime>
#include <cstdlib>

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
int ShowMainMenu(int x, int y, bool isPlaying)
{
	if (isPlaying)
	{
		string option[5] = { "Continue", "New Game", "Leaderboard", "Rules", "Exit" };

		CreateTextBox(x, y, 30, 3, option[0]);
		CreateTextBox(x, y + 3, 30, 3, option[1]);
		CreateTextBox(x, y + 6, 30, 3, option[2]);
		CreateTextBox(x, y + 9, 30, 3, option[3]);
		CreateTextBox(x, y + 12, 30, 3, option[4]);
		//boundary
		const int TOPB = y, BOTTOMB = y + 12;

		char key;
		int i = 0;
		int choose = 4;
		HighlightBox(x, y, 30, 3, option[0], 1);
		while (true)
		{
			int xPrev = x, yPrev = y;
			key = _getch();
			if ((key == 'w' || key == 'W') && y > TOPB && i > 0) //UP
			{
				SelectingSound();
				y -= 3;
				HighlightBox(x, yPrev, 30, 3, option[i], 0);
				HighlightBox(x, y, 30, 3, option[--i], 1);
				choose++;
			}
			else if ((key == 's' || key == 'S') && y < BOTTOMB && i <= 3) //DOWN
			{
				SelectingSound();
				y += 3;
				HighlightBox(x, yPrev, 30, 3, option[i], 0);
				HighlightBox(x, y, 30, 3, option[++i], 1);
				choose--;
			}
			else if (key == ENTER || key == ' ')
			{
				ChoosedSound();
				return choose;
			}
		}
	}
	else
	{
		string option[4] = { "New Game", "Leaderboard", "Rules", "Exit" };

		CreateTextBox(x, y + 3, 30, 3, option[0]);
		CreateTextBox(x, y + 6, 30, 3, option[1]);
		CreateTextBox(x, y + 9, 30, 3, option[2]);
		CreateTextBox(x, y + 12, 30, 3, option[3]);
		//boundary
		const int TOPB = y + 3, BOTTOMB = y + 12;
		y = y + 3;
		char key;
		int i = 0;
		int choose = 3;
		HighlightBox(x, y, 30, 3, option[0], 1);
		while (true)
		{
			int xPrev = x, yPrev = y;
			key = _getch();
			if ((key == UP || key == 'w' || key == 'W') && y > TOPB && i > 0) //UP
			{
				SelectingSound();
				y -= 3;
				HighlightBox(x, yPrev, 30, 3, option[i], 0);
				HighlightBox(x, y, 30, 3, option[--i], 1);
				choose++;
			}
			else if ((key == DOWN || key == 's' || key == 'S') && y < BOTTOMB && i <= 2) //DOWN
			{
				SelectingSound();
				y += 3;
				HighlightBox(x, yPrev, 30, 3, option[i], 0);
				HighlightBox(x, y, 30, 3, option[++i], 1);
				choose--;
			}
			else if (key == ENTER || key == ' ')
			{
				ChoosedSound();
				return choose;
			}
		}
	}
}

void MainMenu(Account*& account, int totalAccounts, int& pos)
{
	BackgroundSong();
	srand((unsigned int)time(NULL));
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
		choose = ShowMainMenu(42, 15, account[pos].isPlaying);
		if (choose == 4)
		{
			GameInfo game = createGameFromAccount(account[pos]);
			system("cls");
			DrawBoardGame(game, 1, 1);
			if (game.isInsane == 1)
			{
				Sleep(1000);
				DrawBoardGame(game, 0, 0);
			}
			bool isPlaying = ShowMoves(game);
			updateAccountAfterGame(account[pos], game, isPlaying);
			system("pause");
		}
		else if (choose == 3)
		{
			system("cls");
			ChooseLevel(42, 18, account[pos]);

		}
		else if (choose == 2)
		{
			system("cls");
			ShowLeaderboard(account, totalAccounts, pos);
			_getch();
		}
		else if (choose == 1)
		{
			system("cls");
			ShowRules();
			_getch();
		}
		else if (choose == 0)
		{
			system("cls");
			cout << "Byee\n";
			_getch();
		}

		outputAccountList(account, totalAccounts);
	} while (choose);
}

void ChooseLevel(int x, int y, Account& account)
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

	string option[] = { "Easy", "Hard", "Insane", "Exit"};
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
		if ((key == UP || key == 'w' || key == 'W') && y > TOPB && i > 0) //UP
		{
			SelectingSound();
			y -= 3;
			HighlightBox(x, yPrev, 30, 3, option[i], 0);
			HighlightBox(x, y, 30, 3, option[--i], 1);
			choose++;
		}
		else if ((key == DOWN || key == 's' || key == 'S') && y < BOTTOMB && i <= 2) //DOWN
		{
			SelectingSound();
			y += 3;
			HighlightBox(x, yPrev, 30, 3, option[i], 0);
			HighlightBox(x, y, 30, 3, option[++i], 1);
			choose--;
		}
		else if (key == ENTER || key == ' ')
		{
			ChoosedSound();
			if (choose == 3)
			{
				GameInfo game(4);
				system("cls");
				DrawBoardGame(game, 1, 1);
				int isPlaying = ShowMoves(game);
				updateAccountAfterGame(account, game, isPlaying);
				system("pause");
				return;
			}
			if (choose == 2)
			{
				GameInfo game(6);
				system("cls");
				DrawBoardGame(game, 1, 1);
				int isPlaying = ShowMoves(game);
				updateAccountAfterGame(account, game, isPlaying);
				system("pause");
				return;
			}
			if (choose == 1)
			{
				GameInfo game(6);
				game.isInsane = 1;
				system("cls");
				DrawBoardGame(game, 1, 1);
				Sleep(1000);
				DrawBoardGame(game, 0, 0);
				int isPlaying = ShowMoves(game);
				updateAccountAfterGame(account, game, isPlaying);
				system("pause");
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

	DrawBox(14, 10, 130, 8);
	DrawBox(14, 17, 130, 8);
	DrawBox(14, 24, 130, 8);
	GoTo(14, 17);
	cout << char(195);
	GoTo(14, 24);
	cout << char(195);
	GoTo(143, 17);
	cout << char(180);
	GoTo(143, 24);
	cout << char(180);

	GoTo(75, 10);
	SetColor(LGREEN, BLACK);
	cout << " OVERALL ";
	SetColor(BLACK, WHITE);

	GoTo(17, 12);
	cout << char(175) << " The Matching Game(commonly known as Pikachu Puzzle Game) includes a board of \
multiple cells, each of whichpresents a figure.\n";
	GoTo(17, 13);
	cout << char(175) << " The player finds and matches a pair of cells that contain the same \
figure and connect each other in some particular pattern.\n";
	GoTo(17, 14);
	cout << char(175) << " A legal match will make the two cells disappear. The game ends when all matching\
pairs are found.\n";

	GoTo(75, 17);
	SetColor(LYELLOW, BLACK);
	cout << " MOVING ";
	SetColor(BLACK, WHITE);

	GoTo(20, 18);
	cout << char(175) << " Press W A S D or UP DOWN LEFT RIGHT arows to move.\n";
	GoTo(20, 20);
	cout << char(175) << " Press Enter or Space bar to select.\n";
	GoTo(20, 22);
	cout << char(175) << " Press X to leave the game.\n";
	GoTo(90, 18);
	cout << char(175) << " Press F to suggest moving.\n";
	GoTo(90, 20);
	cout << char(175) << " Press R to shuffle.\n";


	GoTo(75, 24);
	SetColor(LAQUA, BLACK);
	cout << " SCORING ";
	SetColor(BLACK, WHITE);

	GoTo(20, 26);
	cout << char(175) << " I matching: 1 point.\n";
	GoTo(20, 28);
	cout << char(175) << " L matching: 2 point.\n";
	GoTo(90, 26);
	cout << char(175) << " Z or U matching: 3 point.\n";
	GoTo(90, 28);
	cout << char(175) << " Suggest move or Shuffle: -2 point.\n";
}

void loginMenu(int x, int y)
{
	int		totalAccounts = 0;
	Account* account = NULL;

	inputAccountList(account, totalAccounts);

	string username;
	string password;

	SetColor(BLACK, LBLUE);
	DrawBox(x, y, 50, 10);
	GoTo(x + 18, y + 1);
	SetColor(BLACK, LYELLOW);
	cout << "LOGIN/REGISTER";
	SetColor(BLACK, WHITE);

	while (true)
	{
		GoTo(x + 2, y + 3);
		cout << "Input your username: ";
		getline(cin, username);
		if (username.empty())
		{
			GoTo(x + 15, y + 8);
			SetColor(BLACK, RED);
			cout << "This can't be empty!\n";
			SetColor(BLACK, WHITE);
			continue;
		}
		break;
	}

	int pos = findAccountPos(account, totalAccounts, username);
	if (pos == -1)
	{
		GoTo(x + 1, y + 8);
		cout << "                                                ";
		GoTo(x + 3, y + 8);
		SetColor(BLACK, RED);
		cout << "Your account didn't exist, start registering!\n";
		SetColor(BLACK, WHITE);
		totalAccounts++;
		while (true)
		{
			GoTo(x + 2, y + 4);
			cout << "Input your password: ";
			getline(cin, password);
			if (password.empty())
			{
				GoTo(x + 1, y + 8);
				cout << "                                                ";
				GoTo(x + 15, y + 8);
				SetColor(BLACK, RED);
				cout << "This can't be empty!\n";
				SetColor(BLACK, WHITE);
				continue;
			}
			break;
		}
		pos = totalAccounts - 1;
		strcpy(account[pos].username, username.c_str());
		strcpy(account[pos].password, password.c_str());
	}
	else
	{
		GoTo(x + 1, y + 8);
		cout << "                                                ";
		GoTo(x + 5, y + 8);
		SetColor(BLACK, AQUA);
		cout << "Your account existed, start logging in!\n";
		SetColor(BLACK, WHITE);
		while (true)
		{
			GoTo(x + 1, y + 4);
			cout << "                                                ";
			GoTo(x + 2, y + 4);
			cout << "Input your password: ";
			getline(cin, password);

			if (password.empty())
			{
				GoTo(x + 1, y + 8);
				cout << "                                                ";
				GoTo(x + 15, y + 8);
				SetColor(BLACK, RED);
				cout << "This can't be empty!\n";
				SetColor(BLACK, WHITE);
				continue;
			}
			if (password != account[pos].password)
			{
				GoTo(x + 1, y + 8);
				cout << "                                                ";
				GoTo(x + 20, y + 8);
				SetColor(BLACK, RED);
				cout << "Wrong pass\n";
				SetColor(BLACK, WHITE);
				continue;
			}
			break;
		}
	}

	SetUpConsole(0);
	MainMenu(account, totalAccounts, pos);
	releaseAccountList(account, totalAccounts);
}

void ShowLeaderboard(Account*& account, int totalAccounts, int& pos)
{
	string username = account[pos].username;
	sortDescendingAccountList(account, totalAccounts);
	pos = findAccountPos(account, totalAccounts, username);
	outputAccountList(account, totalAccounts);
	SetColor(BLACK, LBLUE);
	cout << R"(
					    __     ______ ___     ____   ______ ____   ____   ____   ___     ____   ____
					   / /    / ____//   |   / __ \ / ____// __ \ / __ ) / __ \ /   |   / __ \ / __ \
					  / /    / __/  / /| |  / / / // __/  / /_/ // __  |/ / / // /| |  / /_/ // / / /
					 / /___ / /___ / ___ | / /_/ // /___ / _, _// /_/ // /_/ // ___ | / _, _// /_/ /
					/_____//_____//_/  |_|/_____//_____//_/ |_|/_____/ \____//_/  |_|/_/ |_|/_____/)";

	DrawBox(40, 10, 80, 19);
	GoTo(41, 14);
	for (int i = 1; i <= 78; i++)
	{
		cout << char(196);
	}
	for (int i = 1; i <= 17; i++)
	{
		GoTo(46, 10 + i);
		cout << char(179);
	}
	for (int i = 1; i <= 17; i++)
	{
		GoTo(108, 10 + i);
		cout << char(179);
	}

	SetColor(BLACK, LBLUE);
	GoTo(52, 12);
	cout << "Username";
	GoTo(111, 12);
	cout << "Score";
	SetColor(BLACK, YELLOW);
	for (int i = 0, j = 0; i < totalAccounts && i <= 4; i++, j += 3)
	{
		GoTo(43, 10 + 5 + j);
		cout << i + 1;
		GoTo(50, 10 + 5 + j);
		cout << account[i].username;
		GoTo(113, 10 + 5 + j);
		cout << account[i].bestScore;
	}
	SetColor(BLACK, WHITE);

}
