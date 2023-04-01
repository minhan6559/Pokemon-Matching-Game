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
	if(isPlaying)
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
			if ((key == UP || key == 'w') && y > TOPB && i > 0) //UP
			{
				SelectingSound();
				y -= 3;
				HighlightBox(x, yPrev, 30, 3, option[i], 0);
				HighlightBox(x, y, 30, 3, option[--i], 1);
				choose++;
			}
			else if ((key == DOWN || key == 's') && y < BOTTOMB && i <= 3) //DOWN
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
	else
	{
		string option[4] = {"New Game", "Leaderboard", "Rules", "Exit" };
		
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
}

void MainMenu(Account*& account, int totalAccounts, int &pos)
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
			DrawBoardGame(game, 1);
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
			ShowLeaderboard(account, totalAccounts);
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

		string username = account[pos].username;
		sortDescendingAccountList(account, totalAccounts);
		pos = findAccountPos(account, totalAccounts, username);
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
				DrawBoardGame(game, 1);
				int isPlaying = ShowMoves(game);
				updateAccountAfterGame(account, game, isPlaying);
				system("pause");
				return;
			}
			if (choose == 1)
			{
				GameInfo game(6);
				system("cls");
				DrawBoardGame(game, 1);
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

void loginMenu(int x, int y)
{
	int		totalAccounts = 0;
	Account* account = NULL;

	inputAccountList(account, totalAccounts);

	string username;
	string password;

	DrawBox(x, y, 50, 10);
	GoTo(x + 18, y + 1);
	cout << "LOGIN/REGISTER";

	while(true)
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
		cout << "Your account don't exist, start registering!\n";
		SetColor(BLACK, WHITE);
		totalAccounts++;
		while(true)
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
		account[pos].username = username;
		account[pos].password = password;		
	}
	else
	{
		GoTo(x + 1, y + 8);
		cout << "                                                ";
		GoTo(x + 7, y + 8);
		SetColor(BLACK, RED);
		cout << "Your account exist, start logging in!\n";
		SetColor(BLACK, WHITE);
		while(true)
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

void ShowLeaderboard(Account* account, int totalAccounts)
{
	SetColor(BLACK, GREEN);
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