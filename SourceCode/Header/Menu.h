#pragma once
#include "Board.h"
#include "console.h"
#include "Account.h"
#include <conio.h>
#include <iostream>
#include <string>
using namespace std;

struct board;
struct Account;

#define BLACK 0
#define BLUE 1
#define GREEN 2
#define AQUA 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define WHITE 7
#define GRAY 8
#define LBLUE 9
#define LGREEN 10
#define LAQUA 11
#define LRED 12
#define LPURPLE 13
#define LYELLOW 14
#define BRWHITE 15

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13
#define H_Key 104
#define P_key 112
#define ESC_key 27
const char gameName[] = R"(
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

void DrawBox(int xStart, int yStart, int width, int length);
void CreateTextBox(int xStart, int yStart, int length, int width, string text);
void HighlightBox(int xStart, int yStart, int length, int width, string text, int mode);
int ShowMainMenu(int x, int y, bool isPlaying);
void MainMenu(Account*& account, int totalAccounts, int& pos);
void ChooseLevel(int x, int y, Account& account);
void ShowRules();

void loginMenu(int x, int y);
void ShowLeaderboard(Account* account, int totalAccounts);