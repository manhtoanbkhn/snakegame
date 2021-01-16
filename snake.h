#pragma once


#include "common.h"
#include "cursor.h"
#include "box.h"
#include "score.h"

class Snake
{
	Cursor* cursor;
	vector<Coordinate> body;
	Coordinate head;
	atomic<int> direction;
	int length;
	SnakeBox* box;
	bool initialized;
	int speed;
	queue<int> movement;
	mutex moveMutex;
	Score* score;
	atomic<bool> gameOver;
public:
	Snake(const Coordinate& head,
		SnakeBox* box,
		Score* score,
		int speed,
		int len = SNAKE_INIT_LEN,
		int direction = RIGHT_DIRECTION);
	void generateHead();
	void generateBody();
	Coordinate getNextHead();
	void move();
	void directionController();
	bool collideBody(const Coordinate& head);
	void initialize();
	int getNextMove();
	void addNextMove(int next);
	bool movementIsEmpty();
	void clear();
};