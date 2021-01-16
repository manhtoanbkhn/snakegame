#pragma once

#include "common.h"
#include "cursor.h"
#include "score.h"


class Box
{
protected:
	int left;
	int top;
	int width;	// not include border
	int height;	// not include border
	Cursor* cursor;
	Coordinate border;
public:
	Box(int left, int top, int width, int height)
	{
		this->left = left;
		this->top = top;
		this->width = width;
		this->height = height;
		cursor = &Cursor::getInstance();
		border.color = BORDER_COLOR;
	}
	virtual void draw() = 0;
	virtual void initialize() = 0;
	virtual void clear() = 0;
	int Left() { return left; }
	int Top() { return top; }
	int Width() { return width; }
	int Height() { return height; }
	void clearBorder();
};


class SnakeBox : public Box
{
public:
	SnakeBox(int left, int top, int width, int height) 
		: Box(left, top, width, height)
	{
		food.symbol = FOOD_SYMBOL;
		food.color = FOOD_COLOR;
	}
	void generateFood(Coordinate* head = nullptr, vector<Coordinate> body = {});
	bool contains(const Coordinate& point);
	void initialize();
	void draw();
	void clear();
	Coordinate Food() { return food; }
private:
	Coordinate food;
};

class MenuBox : public Box
{
public:
	MenuBox(int left, int top, int width, int height, Score* score)
		: Box(left, top, width, height)
	{ this->score = score; }
	void draw();
	void initialize();
	void clear();
private:
	Score* score;
};