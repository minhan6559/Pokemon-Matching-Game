#pragma once
#include "Menu.h"
#include "Game.h"
#include <fstream>

struct Account
{
	char  username[20];
	char  password[20];

	int     curScore;
	int     bestScore;

	bool    isPlaying;

	int     size;
	int		mode;	//0: Standard, 1: Insane, 2: Sliding
	int** curPokeList;

	Account();
};
struct GameInfo;

void releaseAccountList(Account*& account, int totalAccounts);

//Write account list to binary file
void outputAccountList(Account* account, int totalAccounts);

//Read account list from binary file
void inputAccountList(Account*& account, int& totalAccounts);
 
void sortDescendingAccountList(Account*& account, int totalAccount);

// Update the info of account after a game
void updateAccountAfterGame(Account& account, GameInfo& game, bool isPlaying);

//Return the position of the account in the list
int findAccountPos(Account* account, int totalAccounts, string username);
