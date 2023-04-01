#pragma once
#include "Menu.h"
#include <fstream>

struct Account
{
    string  username;
    string  password;

    int     curScore;
    int     bestScore;

    bool    isContinue;

    int     size;
    int** curPokeList;

    Account();
};

void outputAccountList(Account* account, int totalAccounts);
void inputAccountList(Account*& account, int& totalAccounts);

int findAccountPos(Account* account, int totalAccounts, string username);