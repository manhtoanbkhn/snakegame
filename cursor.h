#pragma once

#include "common.h"


struct Coordinate
{
	int x;
	int y;
	SYMBOL symbol;
	COLOR color;
	Coordinate()
	{
		x = y = 0;
		symbol = NULL_SYMBOL;
		color = NULL_COLOR;
	}
	Coordinate(int x, int y) : Coordinate()
	{
		this->x = x;
		this->y = y;
	}
	bool operator==(const Coordinate& c);
	//void setColor(COLOR cl);
};

class Cursor
{
private:
	Cursor() {
		console = GetStdHandle(STD_OUTPUT_HANDLE);
		//current.setDefault();
	}
public:
	static Cursor& getInstance()
	{
		static Cursor instance;
		return instance;
	}
	Cursor(Cursor const&) = delete;
	void operator=(Cursor const&) = delete;

	//Cursor(int x, int y, SYMBOL symbol= DEFAULT_SYMBOL, COLOR color = DEFAULT_COLOR)
	//	: x(x), y(y), symbol(symbol), color(color) {console = GetStdHandle(STD_OUTPUT_HANDLE);}
	//BOOL gotoxy();
	BOOL gotoxy(int x, int y);
	//BOOL gotoxy(Cursor* coor);
	void hideCursor();
	void generate(Coordinate c);
	template<typename T>
	void generate(T data, COLOR cl = DEFAULT_COLOR, bool hide = true);
	//void generate(string text, COLOR cl = DEFAULT_COLOR);
	void clear(int x, int y);
	void clear(Coordinate c);
	//void setSymbol(SYMBOL sym);
	/*bool operator==(Cursor coor);*/
	/*void setColor(COLOR cl);*/
private:
	HANDLE console;
	//Coordinate* current;
};

template<typename T>
void Cursor::generate(T data, COLOR cl, bool hide)
{
	//clear();
	//gotoxy();
	if (hide)
		hideCursor();
	//if (cl == DEFAULT_COLOR)
	//{
	//	cl = color;
	//}
	SetConsoleTextAttribute(console, cl);
	cout << data;
	//cin.clear();
}
