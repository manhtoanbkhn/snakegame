#include "score.h"



Score::Score(int score, int step, string playerName)
{
	cursor = &Cursor::getInstance();
	this->points = score;
	this->step = step;
	this->playerName = playerName;
	coor.x = SCORE_X_POSITION;
	coor.y = SCORE_Y_POSITION;
	coor.color = SCORE_COLOR;
}

void Score::generate()
{
	cursor->gotoxy(coor.x, coor.y);
	cursor->generate<int>(points, coor.color);
}

void Score::update()
{
	generate();
}

bool Score::checkHighScoreAndSave()
{
	string file_name = SCORE_FILE_NAME;
	ifstream score_file;
	score_file.open(file_name.c_str());
	if (score_file.good() == false)
	{
		// is 1st time run, need create new file
		ofstream new_score_file(file_name.c_str());
		new_score_file << playerName << " " << points << "\n";
		new_score_file.close();
		return true;
	}
	bool res;
	string line;
	vector<pair<int, string>> hs;
	while (getline(score_file, line))
	{
		stringstream ss(line);
		int i_score;
		string s_name;
		ss >> s_name >> i_score;
		hs.push_back({ i_score, s_name });
	}
	sort(hs.begin(), hs.end(), [](pair<int, string> a, pair<int, string> b)->bool {return a.first > b.first; });
	score_file.close();
	string tmp_name = "data/tmp.txt";
	ofstream tmp_file(tmp_name.c_str());
	if (hs.size() < 5)
	{
		res = true;
		hs.push_back({ points, playerName });
	}
	else if(hs.size() == 5 && points > hs.back().first)
	{
		res = true;
		hs.back().first = points;
		hs.back().second = playerName;	
	}
	else
	{
		res = false;
	}
	if (res == true)
	{
		for (int i = 0; i < hs.size(); ++i)
		{
			tmp_file << hs[i].second << " " << hs[i].first << "\n";
		}
		remove(file_name.c_str());
		tmp_file.close();
		rename(tmp_name.c_str(), file_name.c_str());
	}
	if (tmp_file.is_open())
		tmp_file.close();
	return res;
}

void Score::notice(string message)
{
	msg = message;
	cursor->gotoxy(MENU_BOX_LEFT_COOR + SNAKE_BOX_LENGTH / 2, MENU_BOX_TOP_COOR + SNAKE_BOX_HEIGHT + 3);
	cursor->generate(msg, 10);
}

void Score::clear()
{
	for (int i = 0; i < msg.length(); ++i)
	{
		cursor->gotoxy(MENU_BOX_LEFT_COOR + SNAKE_BOX_LENGTH / 2 + i, MENU_BOX_TOP_COOR + SNAKE_BOX_HEIGHT + 3);
		cursor->generate(NULL_SYMBOL, 0);
	}
}