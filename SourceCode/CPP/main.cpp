#include "Console.h"
#include "Game.h"
#include "Menu.h"
using namespace std;

int main()
{
    /*int _size;
    cout << "Enter board size: ";
    cin >> _size;
    system("pause");
    system("cls");

	GameInfo game(_size);
    Queue path;
    int size = game.board.size;*/
    //DrawBoardGame(game.board);

    //ShowMoves(game);
    MainMenu();

  //  while(true)
  //  {
  //      cout << "  ";
  //      for (int i = 0; i < size; i++)
  //      {
  //          cout << i << " ";
  //      }

  //      cout << endl;
  //      for (int i = 0; i < size; i++)
  //      {
  //          cout << i << " ";
  //          for (int j = 0; j < size; j++)
  //          {
  //              if(game.board.pokeList[i][j] != -1)
  //              {
  //                  char temp = game.board.pokeList[i][j];
  //                  cout << temp << " ";
  //              }
  //              else
  //              {
		//			cout << "  ";
		//		}
  //          }
  //          cout << endl;
  //      }

  //      if (game.remainBlocks == 0)
  //      {
		//	cout << "\nYou win!" << endl;
		//	break;
		//}

  //      // Get user input for starting and ending positions
  //      Point p1;
  //      Point p2;
  //      int choice;
  //      cout << "Enter 0 to continue, -1 to exit, -2 for help:" << endl;
  //      cin >> choice;

  //      if (choice == -1)
  //          break;
  //      if (choice == -2)
  //      {
  //          Point suggestPoint1;
  //          Point suggestPoint2;
  //          if (moveSuggestion(game, suggestPoint1, suggestPoint2))
  //              cout << "Suggestion: (" << suggestPoint1.r << ", " << suggestPoint1.c << ") -> (" << suggestPoint2.r << ", " << suggestPoint2.c << ")" << endl;
  //          else
  //              break;
  //      }

  //      cout << "Enter starting position (r, c): ";
  //      cin >> p1.r >> p1.c;
  //      cout << "Enter ending position (r, c): ";
  //      cin >> p2.r >> p2.c;

  //      game.p1 = p1;
  //      game.p2 = p2;

  //      if (checkMatching(game, path) == 1)
  //      {
  //          game.board.pokeList[game.p1.r][game.p1.c] = -1;
  //          game.board.pokeList[game.p2.r][game.p2.c] = -1;
  //          game.remainBlocks -= 2;

  //          // Display shortest path between two blocks
  //          cout << "Path: \n";
  //          while (path.pHead)
  //          {
		//		Point p = path.front();
		//		cout << "(" << p.r << ", " << p.c << ")\n";
  //              path.pop_front();
		//	}

  //          cout << "Matching!" << endl;
  //      }
  //      else
  //      {
		//	cout << "Not matching!" << endl;
		//}

  //      system("pause");
  //      system("cls");

  //  }

  //  game.board.~Board();
  //  path.~Queue();
	return 0;
}