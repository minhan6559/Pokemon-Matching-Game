#pragma once
#include "Menu.h"
#include "Game.h"
#include <fstream>

struct Account
{
    string  username;
    string  password;

    int     curScore;
    int     bestScore;

    bool    isPlaying;

    int     size;
    int** curPokeList;

    Account();
};
struct GameInfo;

void outputAccountList(Account* account, int totalAccounts);
void inputAccountList(Account*& account, int& totalAccounts);

void updateAccountAfterGame(Account& account, GameInfo& game, bool isPlaying);

int findAccountPos(Account* account, int totalAccounts, string username);