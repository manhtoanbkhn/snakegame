// consoleSnake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "game.h"



void Game::initialize()
{
    score = new Score(SNAKE_INIT_LEN* level, level, player.name);
    menubox = new MenuBox(MENU_BOX_LEFT_COOR, MENU_BOX_TOP_COOR, MENU_BOX_LENGTH, MENU_BOX_HEIGHT, score);
    snakebox = new SnakeBox(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR, SNAKE_BOX_LENGTH, SNAKE_BOX_HEIGHT);
    Coordinate head(SNAKE_X_INIT_COOR, SNAKE_Y_INIT_COOR);
    head.symbol = SNAKE_HEAD_SYMBOL;
    head.color = SNAKE_HEAD_COLOR;
    snake = new Snake(head, snakebox, score, SNAKE_INIT_LEN, RIGHT_DIRECTION, level);
}


void Game::start()
{
    gameover = false;
    menubox->initialize();
    snakebox->initialize();
    score->generate();
    move_thread = unique_ptr<thread>(new thread(&Snake::move, snake));
    input_control_thread = unique_ptr<thread>(new thread(&Snake::directionController, snake));

}

void Game::end()
{
    snakebox->clear();
    menubox->clear();
    score->clear();
    move_thread.reset(nullptr);
    input_control_thread.reset(nullptr);
    delete snakebox;
    snakebox = nullptr;
    delete snake;
    snake = nullptr;
    delete score;
    score = nullptr;
    delete menubox;
    menubox = nullptr;
    //cout << "Game::end()" << endl;
}

void Game::wait()
{
    move_thread->join();
    input_control_thread->join();

    gameover = true;
    //cout << "Game::wait()" << endl;
}

void Game::noticeHighScore()
{
    cursor->gotoxy(SNAKE_BOX_LENGTH / 2, SNAKE_BOX_HEIGHT + 5);
    cursor->generate<string>("HIGH SCORE!", 10);
}

void Game::showHighScore()
{
    ifstream f(SCORE_FILE_NAME);
    if (!f.good())
        return;
    vector<pair<int, string>> v;
    string s;
    while (getline(f, s))
    {
        stringstream ss(s);
        string player_name;
        int player_score;
        ss >> player_name >> player_score;
        v.push_back({ player_score, player_name });
    }
    sort(v.begin(), v.end(), [](pair<int, string> a, pair<int, string> b) -> bool {
        return (a.first > b.first);
    });
    for (int i = 0; i < v.size(); ++i)
    {
        cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + i);
        cursor->generate<string>(v[i].second, 10);
        cursor->gotoxy(SNAKE_BOX_LEFT_COOR + 10, SNAKE_BOX_TOP_COOR + i);
        cursor->generate<int>(v[i].first, 10);
    }
    f.close();
    cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + 6);
    cursor->generate("OK", 26);
    
    while (true)
    {
        if (GetAsyncKeyState(VK_RETURN) & 1)
        {
            cin.clear();
            for (int i = 0; i < v.size(); ++i)
            {
                for (int j = 0; j < v[i].second.length(); ++j)
                {
                    cursor->gotoxy(SNAKE_BOX_LEFT_COOR + j, SNAKE_BOX_TOP_COOR + i);
                    cursor->generate(NULL_SYMBOL, NULL_COLOR);
                }
                for (int j = 0; j < to_string(v[i].first).length(); ++j)
                {
                    cursor->gotoxy(SNAKE_BOX_LEFT_COOR + 10 + j, SNAKE_BOX_TOP_COOR + i);
                    cursor->generate(NULL_SYMBOL, NULL_COLOR);
                }
            }
            for (int j = 0; j < 2; ++j)
            {
                cursor->gotoxy(SNAKE_BOX_LEFT_COOR + j, SNAKE_BOX_TOP_COOR + 6);
                cursor->generate(NULL_SYMBOL, NULL_COLOR);
            }
            break;
        }
        else
        {
            this_thread::sleep_for(chrono::microseconds(500));
        }
    }
    
}

void Game::showMainMenu()
{
    unsigned int menu_size = mainMenu.size();
    for (unsigned int i = 0; i < menu_size; ++i)
    {
        cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + i);
        cursor->generate(mainMenu[i], 0 == i ? 26 : 10);
    }
}

void Game::clearMainMenu()
{
    unsigned int menu_size = mainMenu.size();
    for (unsigned int i = 0; i < menu_size; ++i)
    {
        for (unsigned int j = 0; j < string(mainMenu[i]).length(); ++j)
        {
            cursor->gotoxy(SNAKE_BOX_LEFT_COOR + j, SNAKE_BOX_TOP_COOR + i);
            cursor->generate(NULL_SYMBOL, 0);
        }
    }
}

void Game::showLevelMenu()
{
    unsigned int level_size = levelMenu.size();
    for (unsigned int i = 0; i < level_size; ++i)
    {
        cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + i);
        cursor->generate(levelMenu[i], i == 0 ? 26 : 10);
    }
}

void Game::clearLevelMenu()
{
    unsigned int level_size = levelMenu.size();
    for (unsigned int i = 0; i < level_size; ++i)
    {
        for (unsigned int j = 0; j < string(levelMenu[i]).length(); ++j)
        {
            cursor->gotoxy(SNAKE_BOX_LEFT_COOR + j, SNAKE_BOX_TOP_COOR + i);
            cursor->generate(NULL_SYMBOL, NULL_COLOR);
        }
    }
}

void Game::showHowToPlay()
{
    string how_to_play = HOW_TO_PLAY_GAME;
    unsigned int len = how_to_play.length();
    cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR);
    cursor->generate(how_to_play, 10);
    cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + 2);
    cursor->generate("OK!", 26);
}

void Game::clearHowToPlay()
{
    string how_to_play = HOW_TO_PLAY_GAME;
    unsigned int len = how_to_play.length();
    for (unsigned int i = 0; i < len; ++i)
    {
        cursor->gotoxy(SNAKE_BOX_LEFT_COOR + i, SNAKE_BOX_TOP_COOR);
        cursor->generate(NULL_SYMBOL, NULL_COLOR);
    }
    for (unsigned int i = 0; i < 3; ++i)
    {
        cursor->gotoxy(SNAKE_BOX_LEFT_COOR + i, SNAKE_BOX_TOP_COOR + 2);
        cursor->generate(NULL_SYMBOL, NULL_COLOR);
    }
}

void Game::menu()
{
    int option = 0;

    //bool sub = false;
    //bool is_first_run = true;

    showMainMenu();
    //cin.clear();
    while ( true )
    {
        if (gameover == true)
        {
            showMainMenu();
            gameover = false;
        }
        
        while (true)
        {
            /*cin.clear();*/
            //cin.ignore(INT_MAX);
            if (GetAsyncKeyState(VK_RETURN) & 1)
            {
                clearMainMenu();
                //cin.clear();
                break;
            }
            else if (GetAsyncKeyState('W') & 1 || GetAsyncKeyState(VK_UP) & 1)
            {
                //cin.clear();
                cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + option);
                cursor->generate(mainMenu[option], 10);
                if (option == 0)
                    option = 4;
                else
                    option--;
                cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + option);
                cursor->generate(mainMenu[option], 26);
                this_thread::sleep_for(chrono::milliseconds(150));
            }
            else if (GetAsyncKeyState('S') & 1 || GetAsyncKeyState(VK_DOWN) & 1)
            {
                //cin.clear();
                cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + option);
                cursor->generate(mainMenu[option], 10);
                if (option == 4)
                    option = 0;
                else
                    option++;
                cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + option);
                cursor->generate(mainMenu[option], 26);
                this_thread::sleep_for(chrono::milliseconds(150));
            }
            else
                this_thread::sleep_for(chrono::microseconds(500));
        }
        //cin.clear();
        //clearMainMenu();

        switch (option)
        {
        case PLAY_GAME:
        {
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR);
            cursor->generate("Your name: ", 10);
            //cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            string player_name;
            getline(cin, player_name);
            player.name = player_name.length() < MAX_NAME_LEN ? player_name : player_name.substr(0, MAX_NAME_LEN);
            
            for (int i = 0; i < 11 + player_name.length(); ++i)
            {
                cursor->gotoxy(SNAKE_BOX_LEFT_COOR + i, SNAKE_BOX_TOP_COOR);
                cursor->generate(NULL_SYMBOL, NULL_COLOR);
            }
            initialize();
            start();
            wait();
            end();
            //cin.clear();
            break;
        }
        case LEVEL:
        {
            //cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            int level_opt = 0;
            showLevelMenu();
            
            while (true)
            {
                //cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                if (GetAsyncKeyState(VK_RETURN) & 1)
                {
                    level = level_opt;
                    clearLevelMenu();
                    showMainMenu();
                    option = 0;
                    //this_thread::sleep_for(chrono::milliseconds(150));
                    break;
                }
                else if (GetAsyncKeyState('W') & 1 || GetAsyncKeyState(VK_UP) & 1)
                {
                    cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + level_opt);
                    cursor->generate(levelMenu[level_opt], 10);
                    if (level_opt == 0)
                        level_opt = 2;
                    else
                        level_opt--;
                    cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + level_opt);
                    cursor->generate(levelMenu[level_opt], 26);
                    this_thread::sleep_for(chrono::milliseconds(150));
                }
                else if (GetAsyncKeyState('S') & 1 || GetAsyncKeyState(VK_DOWN) & 1)
                {
                    cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + level_opt);
                    cursor->generate(levelMenu[level_opt], 10);
                    if (level_opt == 2)
                        level_opt = 0;
                    else
                        level_opt++;
                    cursor->gotoxy(SNAKE_BOX_LEFT_COOR, SNAKE_BOX_TOP_COOR + level_opt);
                    cursor->generate(levelMenu[level_opt], 26);
                    this_thread::sleep_for(chrono::milliseconds(150));
                }
                else
                    this_thread::sleep_for(chrono::microseconds(500));
            }
            break;
        }
        case HIGH_SCORE:
        {
            showHighScore();
            showMainMenu();
            option = 0;
            cin.clear();
            break;
        }
        case HOW_TO_PLAY:
        {
            //cin.clear();
            showHowToPlay();
            /*cin.ignore((numeric_limits<streamsize>::max)(), '\n');*/
            while (true)
            {
                if (GetAsyncKeyState(VK_RETURN) & 1)
                {
                    
                    clearHowToPlay();
                    showMainMenu();
                    
                    break;
                }
                else
                    this_thread::sleep_for(chrono::microseconds(500));
            }
            option = 0;
            break;
        }
        case QUIT:
        {
            return;
        }
        default:
            break;
        }
    }
    //return option;
}

 

Game::~Game()
{
    move_thread.reset(nullptr);
    input_control_thread.reset(nullptr);
    delete snakebox;
    snakebox = nullptr;
    delete snake;
    snake = nullptr;
    delete score;
    score = nullptr;
    delete menubox;
    menubox = nullptr;
}











//void Snake::startMove()
//{
//    //end_game = false;
//    move_thread = new thread(&Snake::move, this);
//}
//
//void Snake::stopMove()
//{/*
//    end_game = true;
//    while (!isStopped())
//        this_thread::sleep_for(chrono::milliseconds(5));*/
//    move_thread->join();
//}

