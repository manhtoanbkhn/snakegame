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
};

class Cursor
{
private:
	Cursor() {
		console = GetStdHandle(STD_OUTPUT_HANDLE);
	}
public:
	static Cursor& getInstance()
	{
		static Cursor instance;
		return instance;
	}
	Cursor(Cursor const&) = delete;
	void operator=(Cursor const&) = delete;

	BOOL gotoxy(int x, int y);
	void hideCursor();
	void generate(const Coordinate& c);
	template<typename T>
	void generate(const T& data, COLOR cl = DEFAULT_COLOR, bool hide = true);
	void clear(int x, int y);
	void clear(const Coordinate& c);
private:
	HANDLE console;
};

template<typename T>
void Cursor::generate(const T& data, COLOR cl, bool hide)
{
	if (hide)
		hideCursor();
	SetConsoleTextAttribute(console, cl);
	cout << data;
}
