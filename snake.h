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
	Snake(Coordinate head,
		SnakeBox* box,
		Score* score, 
		int len = SNAKE_INIT_LEN,
		int direction = RIGHT_DIRECTION,
		int speed = SLOW);
	void generateHead();
	void generateBody();
	Coordinate getNextHead();
	void move();
	void directionController();
	bool collideBody(Coordinate head);
	void initialize();
	int getNextMove();
	void addNextMove(int next);
	bool movementIsEmpty();
	void clear();
};