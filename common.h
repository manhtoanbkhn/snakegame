#pragma once


#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <queue>
#include <fstream>
#include <string>
#include <sstream>
#include <ios>
#include<limits>


#define SNAKE_INIT_LEN 4
#define SNAKE_BOX_LENGTH 30
#define SNAKE_BOX_HEIGHT 10
#define SNAKE_MAX_LEN SNAKE_BOX_LENGTH*SNAKE_BOX_HEIGHT-SNAKE_BOX_LENGTH-SNAKE_BOX_HEIGHT/2
#define MENU_BOX_LENGTH 15
#define MENU_BOX_HEIGHT SNAKE_BOX_HEIGHT
#define MENU_BOX_LEFT_COOR 5
#define MENU_BOX_TOP_COOR 5
#define SNAKE_BOX_LEFT_COOR MENU_BOX_LEFT_COOR+MENU_BOX_LENGTH+1
#define SNAKE_BOX_TOP_COOR MENU_BOX_TOP_COOR
#define SNAKE_X_INIT_COOR SNAKE_BOX_LEFT_COOR+SNAKE_BOX_LENGTH/3
#define SNAKE_Y_INIT_COOR SNAKE_BOX_TOP_COOR+SNAKE_BOX_HEIGHT/2
#define SCORE_X_POSITION MENU_BOX_LEFT_COOR+9
#define SCORE_Y_POSITION MENU_BOX_TOP_COOR+4

#define NULL_SYMBOL char(0)
#define DEFAULT_SYMBOL NULL_SYMBOL
#define SNAKE_HEAD_SYMBOL char(1)
#define SNAKE_BODY_SYMBOL char(255)
#define FOOD_SYMBOL char(42)
#define BIG_FOOD_SYMBOL char(15)
#define BOX_HORIZONTAL_BORDER_SYMBOL char(205)
#define BOX_VERTICAL_BORDER_SYMBOL char(186)
#define BOX_LEFT_TOP_CORNER_SYMBOL char(201)
#define BOX_LEFT_BOTTOM_CORNER_SYMBOL char(200)
#define BOX_RIGHT_TOP_CORNER_SYMBOL char(187)
#define BOX_RIGHT_BOTTOM_CORNER_SYMBOL char(188)

#define DEFAULT_COLOR 7
#define NULL_COLOR 0
#define BORDER_COLOR 17
#define FOOD_COLOR 2
#define BIG_FOOD_COLOR 10
#define SCORE_COLOR 10
#define SNAKE_HEAD_COLOR 70
#define SNAKE_BODY_INIT_COLOR 96
#define SNAKE_BODY_STEP_COLOR 16
#define SNAKE_BODY_COLOR_NUMBER 2

#define SCORE_FILE_NAME "data/score.txt"
#define HOW_TO_PLAY_GAME "Are you crazy? Just do not hit your body, bro!"

#define MAX_NAME_LEN 8

//#define INIT_SCORE 0

using namespace std;

typedef unsigned char SYMBOL;
typedef unsigned int COLOR;





enum Direction
{
	LEFT_DIRECTION,
	RIGHT_DIRECTION,
	UP_DIRECTION,
	DOWN_DIRECTION
};

enum Speed	// pixel/s
{
	SLOW = 5,
	NORMAL = 8,
	FAST= 13
};

enum Menu
{
	PLAY_GAME,
	LEVEL,
	HIGH_SCORE,
	HOW_TO_PLAY,
	QUIT
};