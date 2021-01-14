#pragma once

#include "common.h"
#include "cursor.h"


class Score
{
private:
	int points;
	int step;
	Cursor* cursor;
	string playerName;
	string msg;
	Coordinate coor;
public:
	Score(int score, int step, string playerName = "Raven");
	void increase() { points += step; }
	void update();
	void generate();
	bool checkHighScoreAndSave();
	void notice(string message);
	void clear();
	int getPoints() { return points; }
	string getPlayerName() { return playerName; }

};