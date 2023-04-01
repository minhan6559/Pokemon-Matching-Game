#include "Account.h"

Account::Account()
{
	username = "";
	password = "";
	curScore = 0;
	bestScore = 0;
	isPlaying = false;
	size = 0;
	curPokeList = NULL;
}

void releaseAccountList(Account*& account, int totalAccounts)
{
	// first, check if the account list is not NULL
	if (account != NULL)
	{
		// deallocate each curPokeList array inside each Account object
		for (int i = 0; i < totalAccounts; i++)
		{
			if (account[i].curPokeList != NULL)
			{
				for (int m = 0; m < account[i].size; m++) {
					if (account[i].curPokeList[m] != NULL) {
						delete[] account[i].curPokeList[m];
					}
				}
				delete[] account[i].curPokeList;
			}
		}
		account = NULL;
	}
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

	account = new Account[totalAccounts + 1];

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

void sortDescendingAccountList(Account*& account, int totalAccount)
{
	bool haveSwap = false;
	for (int i = 0; i < totalAccount - 1; i++) 
	{
		haveSwap = false;
		for (int j = 0; j < totalAccount - i - 1; j++) 
		{
			if (account[j].bestScore < account[j + 1].bestScore) 
			{
				Account temp = account[j];
				account[j] = account[j + 1];
				account[j + 1] = temp;
				haveSwap = true;
			}
		}
		if (haveSwap == false) {
			break;
		}
	}
}

void updateAccountAfterGame(Account& account, GameInfo& game, bool isPlaying)
{
	if (isPlaying == 1)
	{
		account.isPlaying = 1;
		account.curScore = game.score;
		account.curPokeList = game.board.pokeList;
		account.size = game.board.size;
	}
	else
	{
		account.isPlaying = 0;

		if (account.bestScore < game.score)
		{
			account.bestScore = game.score;
		}

		account.curScore = 0;
		
		releaseGame(game);

		account.curPokeList = NULL;
	}
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