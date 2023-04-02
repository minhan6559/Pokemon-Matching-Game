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
    int** curPokeList;

    Account();
};
struct GameInfo;

void releaseAccountList(Account*& account, int totalAccounts);
void outputAccountList(Account* account, int totalAccounts);
void inputAccountList(Account*& account, int& totalAccounts);

void sortDescendingAccountList(Account*& account, int totalAccount);
void updateAccountAfterGame(Account& account, GameInfo& game, bool isPlaying);

int findAccountPos(Account* account, int totalAccounts, string username);
