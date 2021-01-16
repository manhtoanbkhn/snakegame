#pragma once


#include "common.h"
#include "box.h"
#include "snake.h"
#include "score.h"


class Game
{
public:
	struct player
	{
		string name;
	}player;

	enum Speed
	{
		SLOW = 5,
		NORMAL = 8,
		FAST = 13
	};
public:
	Game();
	~Game();
	void initialize();
	void start();
	void end();
	void wait();
	void menu();
	void showHighScore();
	void showMainMenu();
	void clearMainMenu();
	void showLevelMenu();
	void clearLevelMenu();
	void showHowToPlay();
	void clearHowToPlay();
private:
	Cursor* cursor;
	SnakeBox* snakebox;
	MenuBox* menubox;
	Snake* snake;
	Score* score;
	unique_ptr<thread> move_thread;
	unique_ptr<thread> input_control_thread;
	bool gameover;
	int level;
	vector<string> mainMenu = { "Play Game", "Level", "High Score" , "How To Play" , "Quit" };
	vector<string> levelMenu = { "SLOW", "NORMAL", "FAST" };
};




