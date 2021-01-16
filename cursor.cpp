#include "cursor.h"




BOOL Cursor::gotoxy(int x, int y)
{
	COORD c = { x, y };
	return SetConsoleCursorPosition(console, c);
}

void Cursor::hideCursor()
{
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(console, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(console, &cursorInfo);
}

void Cursor::generate(const Coordinate& c)
{
	hideCursor();
	gotoxy(c.x, c.y);
	SetConsoleTextAttribute(console, c.color);
	cout << c.symbol;
}

void Cursor::clear(int x, int y)
{
	hideCursor();
	gotoxy(x, y);
	SetConsoleTextAttribute(console, NULL_COLOR);
	cout << NULL_SYMBOL;
}

void Cursor::clear(const Coordinate& c)
{
	clear(c.x, c.y);
}

bool Coordinate::operator==(const Coordinate& c)
{
	if (x == c.x && y == c.y)
		return true;
	return false;
}