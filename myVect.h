#pragma once
#include "pch.h"
#include <iostream>
#include <fstream>
#include<windows.h> 
#include <conio.h>

#include <string>
////delete this!!!
//enum ColorGO {
//	blue=0,black=1, red,white, green
//};
//void ShowConsoleCursor(bool l) {}
/////end of deleted fragment



struct Vector2
{
	int x, y;
	Vector2(int sX, int sY)
	{
		x = sX; y = sY;
	}
	Vector2()
	{
		x = 0; y = 0;
	}

	friend Vector2 operator + (Vector2 v1, Vector2 v2) {
		return Vector2(v1.x + v2.x, v1.y + v2.y);
	}

	friend	Vector2 operator += (Vector2 v1, const Vector2 v2)
	{
		v1.x += v2.x; v1.y += v2.y;
		return v1;
	}
	friend	Vector2 operator + (const Vector2 v)
	{
		return v;
	}
	Vector2 operator - (const Vector2 v)
	{
		return Vector2(v.x * -1, v.y * -1);
	}
	Vector2 operator / (const int v)
	{
		return Vector2(this->x = this->x / v, this->y = this->y / v);
	}
	friend const bool operator == (const Vector2 v1, const Vector2 v2)
	{
		if ((v1.x == v2.x) && (v1.y == v2.y))
			return true;
		return false;
	}
	friend const bool operator != (const Vector2 v1, const Vector2 v2)
	{
		return !(v1 == v2);
	}


};


using namespace std;

//int idGO;
//string str = "";
//int	button1 = 0;
int cellPositions[10][10] = {
	{4,0,1,1,1,1,1,1,1,1},
	{1,0,1,1,0,0,0,0,3,1},
	{1,0,0,1,1,0,0,0,0,1},
	{1,0,2,0,0,0,0,0,0,1},
	{1,0,0,0,0,1,0,2,0,1},
	{1,1,1,1,2,1,0,0,0,1},
	{1,1,1,0,0,1,1,5,0,1},
	{1,0,1,0,1,1,1,0,0,1},
	{1,0,0,0,1,1,1,0,0,1},
	{1,1,1,1,1,1,1,1,0,0}
};



namespace ConsoleForGame {
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
CONSOLE_CURSOR_INFO     cursorInfo;

	enum ColorOfSymb
		{
			Black,
			Blue,
			Green,
			Cyan,
			Red,
			Magenta,
			Brown,
			LightGray,
			DarkGray,
			LightBlue,
			LightGreen,
			LightCyan,
			LightRed,
			LightMagenta,
			Yellow,
			White,
		};
	static class PrepareConsoleForGame {

	public:
		
		static	void ChangeColorSymb(ColorOfSymb ForgC) {

			WORD wColor;
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			GetConsoleScreenBufferInfo(hStdOut, &csbi);
			wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
			SetConsoleTextAttribute(hStdOut, wColor);
		}
		static void ShowConsoleCursor(bool showFlag)
		{

			GetConsoleCursorInfo(hStdOut, &cursorInfo);
			cursorInfo.bVisible = showFlag; // set the cursor visibility
			SetConsoleCursorInfo(hStdOut, &cursorInfo);
		}

	};
}
void readFile(string textfile) {
	ofstream Myfstream;
	Myfstream.open(textfile);
	Myfstream << "test";
	Myfstream.close();
}

int vectorAsIndex(Vector2 ind) {
	if ((ind.x < 9) && (ind.y < 9)) {
		return	cellPositions[ind.x][ind.y];
	}
	return 0;
}

