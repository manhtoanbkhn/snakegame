#include "cursor.h"






//Cursor::Cursor()
//{
//	x = y = 0;
//	symbol = NULL_SYMBOL;
//	color = DEFAULT_COLOR;
//	console = GetStdHandle(STD_OUTPUT_HANDLE);
//}

//BOOL Cursor::gotoxy()
//{
//	COORD c = { x, y };
//	return SetConsoleCursorPosition(console, c);
//}

BOOL Cursor::gotoxy(int x, int y)
{
	COORD c = { x, y };
	return SetConsoleCursorPosition(console, c);
}


//BOOL Cursor::gotoxy(Cursor* coor)
//{
//	COORD c = { coor->x, coor->y };
//	return SetConsoleCursorPosition(console, c);
//}

void Cursor::hideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(console, &cursorInfo);
}

//void Cursor::generate()
//{
//	hideCursor();
//	gotoxy();
//	SetConsoleTextAttribute(console, color);
//	cout << symbol;
//}

//template<typename T>
//void Cursor::generate(T data, COLOR cl)
//{
//	//clear();
//	//gotoxy();
//	hideCursor();
//	if (cl == DEFAULT_COLOR)
//	{
//		cl = color;
//	}
//	SetConsoleTextAttribute(console, cl);
//	cout << data;
//}

//void Cursor::generate(string text, COLOR cl)
//{
//	hideCursor();
//	SetConsoleTextAttribute(console, cl);
//	cout << text;
//}

void Cursor::generate(Coordinate c)
{
	hideCursor();
	gotoxy(c.x, c.y);
	SetConsoleTextAttribute(console, c.color);
	cout << c.symbol;
	//cin.clear();
}

void Cursor::clear(int x, int y)
{
	hideCursor();
	gotoxy(x, y);
	SetConsoleTextAttribute(console, NULL_COLOR);
	cout << NULL_SYMBOL;
	//cin.clear();
}

void Cursor::clear(Coordinate c)
{
	hideCursor();
	gotoxy(c.x, c.y);
	SetConsoleTextAttribute(console, NULL_COLOR);
	cout << NULL_SYMBOL;
	//cin.clear();
}

//
//void Cursor::setSymbol(SYMBOL sym)
//{
//	this->symbol = sym;
//}

bool Coordinate::operator==(const Coordinate& c)
{
	if (x == c.x && y == c.y)
		return true;
	return false;
}



//void Cursor::setColor(COLOR cl)
//{
//	color = cl;
//}