#pragma once
#include "myVect.h"
#include <string>
#include "gameObjects.h"

using namespace std;
using namespace ConsoleForGame;
using namespace game;


Player player;

Monster enemy = Monster(Vector2());


//replace this to GameManager
void SendGameMessage(int r, int yL, string who)
{
	PrepareConsoleForGame::ChangeColorSymb(White);
	COORD b;
	b.X = 10;
	b.Y = yL;
	SetConsoleCursorPosition(hStdOut, b);
	cout << "score of\t " + who + " score:" << r;
}

class GameManager
{
public:
	static GameManager& Instance()
	{
		//ctrlC+ctrlV
		// согласно стандарту, этот код ленивый и потокобезопасный
		static GameManager s;
		return s;
	}

private:
	//int 	n = numberOfItem;

	GameObject * go[10][10];
int numberOfItem = 0;
	Item* items[3];
	string name;
	int length = sizeof(cellPositions) / sizeof(cellPositions[0]);
	GameManager() {
		name = " GM";
		cout << "\n GameManager created\n";
		Playing();
	}

	void InstantiateAllElements() {
		cout << "\n\tSo how did I ever end up here ?\n\tI've waited for a thousand years to break these chains apart\n\t and to finally break myself free.\n\nTo start press any key twice\n\n";

		Vector2 coordObj;

		for (int x = 0; x < length; x++) {
			for (int y = 0; y < length; y++) {
				coordObj = Vector2(x, y);
				switch (vectorAsIndex(coordObj))
				{
				case 1:
					go[x][y] = new Wall(Vector2(x, y), 1);
					break;
				case 2:
					items[numberOfItem] = new Item(Vector2(x, y));
					go[x][y] = items[numberOfItem];
					numberOfItem++;
					break;
				case 3:
					go[x][y] = &enemy;
					enemy._position = coordObj;
					break;
				case 4:
					go[x][y] = &player; player._position = coordObj;
					break;
				default:
					go[x][y] = new GameObject(Vector2(x, y));//this allocates mem and instantiate go
					go[x][y]->name += " floor";
					break;
				}
			}
		}

		system("pause");
		system("cls");
	}

	~GameManager() {
	
		for (int ii = 0; ii < 10; ii++) {
			for (int jj = 0; jj < 10; jj++) {
				try
				{
					go[ii][jj]->~GameObject();
				}
				catch (...) {
					cout << "\nOur journeys take us to foreign shores\n";
				}
			}
		}
		logGame += "\n deleted " + name + "\n";
		logGame += "\nGameManager deleted\n";
		cout << "\nOur journeys take us to foreign shores\n";
		cout << logGame;
		cout << "This may be our last quest\n";
	}

	GameManager(const GameManager& gmm) = delete; // Avoiding implicit generation of the copy constructor.
	GameManager& operator = (const GameManager&);  // no need of this

	void OpenCells(Vector2 v2) {
		for (int x = v2.x - 2; x < v2.x + 3; x++) {
			for (int y = v2.y - 2; y < v2.y + 3; y++) {
				/*if (((x) < 10) && ((y) < 10) && ((x) >= 0) && ((y) >= 0)) {*/
				if (cellPositions[x][y] == 1) {
					go[x][y]->Draw(Vector2(x, y), LightBlue);
				}
				else if (cellPositions[x][y] == 2)
				{
					go[x][y]->Draw(Vector2(x, y), Green);
				}
				else if (cellPositions[x][y] == 3)
				{
					go[x][y]->Draw(Vector2(x, y), Magenta);
				}

				/*}*/
			}
		}
	}

	void MovePl() {
		Vector2 v2;
		v2 = player._position;
		switch (buttonPressed) {
		case 27:
			cout << endl << "End" << endl;
			this->~GameManager();
			break;
		case 72:
			if ((v2.y >= 0)) {
				if (go[v2.x][v2.y - 1]->OnColliderEnter(player.score)) {
					player.Draw(v2, Black);
					v2.y -= 1;
				}
			}
			break;
		case 80:
			if ((v2.y + 1 < 10)) {
				if (go[v2.x][v2.y + 1]->OnColliderEnter(player.score)) {
					player.Draw(v2,Black);
					v2.y += 1;
				}
			}
			break;
		case 77:
			if ((v2.x + 1 < 10)) {
				if (go[v2.x + 1][v2.y]->OnColliderEnter(player.score)) {
					player.Draw(v2, Black);
					v2.x += 1;
				}
			}
			break;
		case 75:
			if ((v2.x - 1 > 0)) {
				if (go[v2.x - 1][v2.y]->OnColliderEnter(player.score)) {
					player.Draw(v2,Black);
					v2.x -= 1;
				}
			}
			break;
		}

		OpenCells(v2);
		player._position = v2;
		player.Draw(v2, White);

	}int rx = 1;
	int ry = 1; Vector2 randVect;
	void MoveEn() {


		randVect += Vector2(rx, ry);
		
		if (go[randVect.x][randVect.y]->OnColliderEnter(enemy.score)) {
			enemy.Draw(randVect, LightRed); enemy._position = randVect;
		}


	}
	void Update(int r) {

		while (buttonPressed != 27)
		{

			buttonPressed = _getch();
			MovePl();
			MoveEn();
			//	enemy.Move();/*
			//	go[enemy._position.x][enemy._position.y]->OnColliderEnter(enemy.score);*/
		//		SendGameMessage(enemy.score, 18, "monster");
			SendGameMessage(player.score, 13, "player");
			SendGameMessage(enemy.score, 15, "enemy");

			if (player._position == Vector2(9, 9)) {

				cout << endl << "End" << endl;
				break;
			}
		}
		system("cls");
		cout << "\ngame over\n\n";
	}

	void Playing() {

		ConsoleForGame::PrepareConsoleForGame::ShowConsoleCursor(false);
		InstantiateAllElements();
		Update(1);
	}
};
//