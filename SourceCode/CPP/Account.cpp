#include "Account.h"

Account::Account()
{
	username = "";
	password = "";
	curScore = 0;
	bestScore = 0;
	isContinue = false;
	size = 0;
	curPokeList = NULL;
}

void outputAccountList(Account* account, int totalAccounts)
{
	ofstream fp("saveGame\\saveGame.bin", ios::binary);

	fp.write((char*)&totalAccounts, sizeof(int));

	for (int i = 0; i < totalAccounts; i++)
	{
		fp.write((char*) &account[i], sizeof(Account));
		
		if(account[i].curPokeList != NULL)
			for (int m = 0; m < account[i].size; m++)
			{
				for (int n = 0; n < account[i].size; n++)
					fp.write((char*)&account[i].curPokeList[m][n], sizeof(int));
			}
	}

	fp.close();
}
void inputAccountList(Account*& account, int& totalAccounts)
{
	ifstream fp ("saveGame\\saveGame.bin", ios::binary);

	fp.read((char*)&totalAccounts, sizeof(int));

	for (int i = 0; i < totalAccounts; i++)
	{
		fp.read((char*) &account[i], sizeof(Account));
		if (account[i].curPokeList != NULL)
		{
			account[i].curPokeList = new int* [account[i].size];
			for (int m = 0; m < account[i].size; m++)
			{
				account[i].curPokeList[m] = new int [account[i].size];
				for (int n = 0; n < account[i].size; n++)
					fp.read((char*)&account[i].curPokeList[m][n], sizeof(int));
			}
		}
	}

	fp.close();
}

int findAccountPos(Account* account, int totalAccounts, string username)
{
	for (int i = 0; i < totalAccounts; i++)
	{
		if (account[i].username == username)
			return i;
	}
	return -1;
}