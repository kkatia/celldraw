#pragma once

//#include "pch.h"
//#include <iostream>
//#include <fstream>
//#include<windows.h> 
//#include <conio.h>
//
//#include <string>
#include "myVect.h"
using namespace std;

using namespace ConsoleForGame;

namespace game {
	int idGO;
	string logGame = "";
	int	buttonPressed = 0;


	class GameObject
	{
	public:Vector2 _position;
		   string name;// = "GO" + to_string(idGO);

		   ConsoleForGame::ColorOfSymb clrGO;
		   char CellSymbol = char(219);
		   //virtual  Vector2 position() const { return _position; }
		   //	virtual   void position(Vector2 value) { _position = value; }
		   GameObject() {
			   name = "GO " + to_string(idGO);
			   _position = Vector2(0, 0);
			   clrGO = Black;
			   idGO++;
		   }
		   GameObject(Vector2 pos) {
			   name = "GO " + to_string(idGO);
			   _position = pos;
			   clrGO = White;
			   idGO++;
		   }
		   GameObject(const GameObject &) {
			   logGame += "\n created copy of" + name + "\n";
		   }
		   ~GameObject() {
			   logGame += "\n deleted " + name + "\n";
		   }

		   virtual void Draw(Vector2 pos, ConsoleForGame::ColorOfSymb  col)
		   {

			   _position = pos;
			   clrGO = col;
			   PrepareConsoleForGame::ChangeColorSymb(col);
			   COORD b = { _position.x,_position.y };
			   /*  b.X = _position.x;
				 b.Y = _position.y;*/
			   SetConsoleCursorPosition(hStdOut, b);
			   cout << char(219) << endl;
		   }
		   virtual	 bool OnColliderEnter(int& u) {

			   /*Draw(_position, PrepareConsoleForGame::Black);*/
			   return true;
		   }
	};


	class StaticGameObject :public GameObject
	{
	public:	enum TypeOfStatic {
			Block, Item
		};
		enum Blocks {
			Wall, Floor, Finish
		};
	
		StaticGameObject() {}
		~StaticGameObject() {}
		//virtual void PrintA() = 0;
	private:

	};

	class Item :public GameObject {
	public:	enum TypeOfItems {
			Health, Armour, Weapon, Key
		};		
		
			Item(Vector2 v) {
			name = " go" + to_string(idGO) + " - item";
			idGO++;
			_position = v;
		}
		Item(const Item &) {
			logGame += "\n created copy of" + name + "\n";
		}
		~Item() {
			logGame += "\n deleted " + name + "\n";
		}
		bool OnColliderEnter(int& u) override {
			OnCollect(u);
			return true;
		}
	private:
		bool isCollectable = true;
		virtual	void OnCollect(int& u) {
			if (isCollectable) {
				Draw(_position, Black);
				u++;
				isCollectable = false;
				cellPositions[_position.x][_position.y] = 0;
			}
		}
	};
	///
	class Character : public GameObject {
	public:
		virtual	void Move() = 0;
	};
	//npc
	class Monster : public Character
	{
	public:
		
		void Move(){}

		int ft = 0;
		int score;
		Monster(Vector2 mv) {
			name = " go" + to_string(idGO) + " - monster";
			idGO++;
			_position = mv;
		}
		Monster(const Monster &) {
			logGame += "\n created copy of" + name + "\n";
		}
		~Monster() {
			logGame += "\n deleted " + name + "\n";
		}
		bool OnColliderEnter(int& q) override {
			Attack(q);
			if (score > 0) {
				/*Move();*/ return false;
			}
			else
			{
				Draw(_position, Black);	return true;
			}


		}
		void Attack(int& o) {
			o--;
		}
	private:

	};

	class Player :public Character
	{
	public:
		
		void Move() {}

		int score = 0;
		Player() {
			name = " go" + to_string(idGO) + " - player";
			idGO++;
			_position = Vector2(0, 0);
			Draw(_position,White);
		}
		Player(Vector2 vp) {
			name = " go" + to_string(idGO) + " - player";
			idGO++;
			_position = vp;
			Draw(_position, White);
		}
		Player(const Player &) {
			logGame += "\n created copy of" + name + "\n";
		}
		~Player() {
			logGame += "\n deleted " + name + "\n";
		}
	private:

	};


class Wall :public GameObject
{

public:

	Wall(Vector2 position) {
		name = " go" + to_string(idGO) + " - wall";
		idGO++;
		_position = position;
		Draw(position,LightBlue);
	}
	Wall(Vector2 position, int k) {
		name = " go" + to_string(idGO) + " - wall";

		_position = position; idGO++;
	}
	Wall(const Wall &) {
		logGame += "\n created copy of" + name + "\n";
	}
	~Wall() {
		logGame += "\n deleted " + name + "\n";
	}

	bool OnColliderEnter(int& u) override {
		return false;
	}
};
}
