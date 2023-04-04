#include "Account.h"

Account::Account()
{
	strcpy(username, "");
	strcpy(password, "");
	curScore = 0;
	bestScore = 0;
	isPlaying = false;
	size = 0;
	isInsane = 0;
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
		delete[] account;
		account = NULL;
	}
}

void outputAccountList(Account* account, int totalAccounts)
{
	ofstream fp("SaveGame\\saveGame.bin", ios::binary | ios::trunc);

	char mask1 = 't';
	char mask2 = 'l';

	fp.write((char*)&totalAccounts, sizeof(int));

	for (int i = 0; i < totalAccounts; i++)
	{
		Account _account = account[i];
		// XOR encode account data
		for (int j = 0; j < sizeof(Account); j++) 
		{
			((char*)& _account)[j] ^= mask1;
			((char*)& _account)[j] ^= mask2;
		}
		fp.write((char*)& _account, sizeof(Account));

		// XOR encode current pokemon list data
		if (account[i].isPlaying == 1)
			for (int m = 0; m < account[i].size; m++)
			{
				for (int n = 0; n < account[i].size; n++) 
				{
					int _poke = account[i].curPokeList[m][n];
					for(int k = 0; k < 4; k++)
					{
						((char*)&_poke)[k] ^= mask1;
						((char*)&_poke)[k] ^= mask2;	
					}
					fp.write((char*)& _poke, sizeof(int));
				}
			}
	}

	fp.close();
}

void inputAccountList(Account*& account, int& totalAccounts)
{
    ifstream fp("SaveGame\\saveGame.bin", ios::binary);

    char mask1 = 'l';
    char mask2 = 't';

    fp.read((char*)&totalAccounts, sizeof(int));

    account = new Account[totalAccounts + 1];

    for (int i = 0; i < totalAccounts; i++)
    {
        fp.read((char*)&account[i], sizeof(Account));
        // XOR decode account data
        for (int j = 0; j < sizeof(Account); j++) {
            ((char*)&account[i])[j] ^= mask1;
			((char*)&account[i])[j] ^= mask2;
        }
        if (account[i].isPlaying == 1)
        {
            account[i].curPokeList = new int*[account[i].size];
            for (int m = 0; m < account[i].size; m++)
            {
                account[i].curPokeList[m] = new int[account[i].size];
                for (int n = 0; n < account[i].size; n++) {
                    fp.read((char*)&account[i].curPokeList[m][n], sizeof(int));
                    // XOR decode current pokemon list data
					for(int k = 0; k < 4; k++)
					{
						((char*)& account[i].curPokeList[m][n])[k] ^= mask1;
						((char*)& account[i].curPokeList[m][n])[k] ^= mask2;
					}
                }
            }
        }
        else
            account[i].curPokeList = NULL;
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
		account.isInsane = game.isInsane;
	}
	else
	{
		account.isPlaying = 0;
		account.isInsane = 0;
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
		if (strcmp(account[i].username, username.c_str()) == 0)
			return i;
	}
	return -1;
}
