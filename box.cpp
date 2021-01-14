#include "box.h"





//void Box::initializeBorder()
//{
//
//    border.push_back(Cursor(left, top, BOX_LEFT_TOP_CORNER_SYMBOL));
//    border.push_back(Cursor(left + width, top, BOX_RIGHT_TOP_CORNER_SYMBOL));
//    border.push_back(Cursor(left, top + height, BOX_LEFT_BOTTOM_CORNER_SYMBOL));
//    border.push_back(Cursor(left + width, top + height, BOX_RIGHT_BOTTOM_CORNER_SYMBOL));
//    for (int i = 1; i < width; ++i)
//    {
//        border.push_back(Cursor(left + i, top, BOX_HORIZONTAL_BORDER_SYMBOL));
//        border.push_back(Cursor(left + i, top + height, BOX_HORIZONTAL_BORDER_SYMBOL));
//    }
//    for (int i = 1; i < height; ++i)
//    {
//        border.push_back(Cursor(left, top + i, BOX_VERTICAL_BORDER_SYMBOL));
//        border.push_back(Cursor(left + width, top + i, BOX_VERTICAL_BORDER_SYMBOL));
//    }
//}

void Box::clearBorder()
{
    for (int i = 0; i < width + 2; i++)
    {
        cursor->gotoxy(left + i, top);
        cursor->generate(NULL_SYMBOL, NULL_COLOR);
        cursor->gotoxy(left + i, top + height + 1);
        cursor->generate(NULL_SYMBOL, NULL_COLOR);
    }
    for (int i = 0; i < height; i++)
    {
        cursor->gotoxy(left, i + top + 1);
        cursor->generate(NULL_SYMBOL, NULL_COLOR);
        cursor->gotoxy(left + width + 1, i + top + 1);
        cursor->generate(NULL_SYMBOL, NULL_COLOR);
    }
}

void SnakeBox::generateFood(Coordinate* head, vector<Coordinate> body)
{
    int x, y;
    bool unique = false;
    while (true)
    {
        x = rand() % width + left + 1;
        y = rand() % height + top + 1;
        food.x = x;
        food.y = y;

        /* is initialization of game */
        if (head == nullptr)
        {
            Coordinate h(SNAKE_X_INIT_COOR, SNAKE_Y_INIT_COOR);
            head = &h;
            for (int i = 1; i < SNAKE_INIT_LEN; ++i)
            {
                body.push_back(Coordinate(SNAKE_X_INIT_COOR - 1, SNAKE_Y_INIT_COOR));
            }
        }

        /* check if food is same position with snake */
        if (food == *head)
            continue;

        unique = true;
        for (auto p : body)
        {
            if (p == food)
            {
                unique = false;
                break;
            }
        }
        if (unique) break;
    }
    
    cursor->generate(food);
}



void SnakeBox::draw()
{
    COLOR cl = border.color;
    cursor->gotoxy(left, top);
    cursor->generate<SYMBOL>(BOX_LEFT_TOP_CORNER_SYMBOL, cl);
    for (int i = 0; i < width; i++)
        cursor->generate<SYMBOL>(BOX_HORIZONTAL_BORDER_SYMBOL, cl);
    cursor->generate<SYMBOL>(BOX_RIGHT_TOP_CORNER_SYMBOL, cl);
    cursor->gotoxy(left, height + top + 1);
    cursor->generate<SYMBOL>(BOX_LEFT_BOTTOM_CORNER_SYMBOL, cl);
    for (int i = 0; i < width; i++)
        cursor->generate<SYMBOL>(BOX_HORIZONTAL_BORDER_SYMBOL, cl);
    cursor->generate<SYMBOL>(BOX_RIGHT_BOTTOM_CORNER_SYMBOL, cl);
    for (int i = 0; i < height; i++)
    {
        cursor->gotoxy(left, i + top + 1);
        cursor->generate<SYMBOL>(BOX_VERTICAL_BORDER_SYMBOL, cl);
        cursor->gotoxy(left + width + 1, i + top + 1);
        cursor->generate<SYMBOL>(BOX_VERTICAL_BORDER_SYMBOL, cl);
    }
}


bool SnakeBox::contains(Coordinate point)
{
    if ((point.x > left) && (point.x < left + width) && (point.y < top + height) && (point.y > top))
        return true;
    return false;
}


void SnakeBox::initialize()
{
    draw();
    generateFood();
}

void SnakeBox::clear()
{
    /* clear the food */
    cursor->clear(food);
    /* clear the border */
    clearBorder();
}


void MenuBox::draw()
{
    COLOR cl = border.color;
    cursor->gotoxy(left, top);
    cursor->generate<SYMBOL>(BOX_LEFT_TOP_CORNER_SYMBOL, cl);
    for (int i = 0; i < width; ++i)
        cursor->generate<SYMBOL>(BOX_HORIZONTAL_BORDER_SYMBOL, cl);
    cursor->gotoxy(left, top + height + 1);
    cursor->generate<SYMBOL>(BOX_LEFT_BOTTOM_CORNER_SYMBOL, cl);
    for (int i = 0; i < width; ++i)
        cursor->generate<SYMBOL>(BOX_HORIZONTAL_BORDER_SYMBOL, cl);
    for (int i = 0; i < height; ++i)
    {
        cursor->gotoxy(left, top + i + 1);
        cursor->generate<SYMBOL>(BOX_VERTICAL_BORDER_SYMBOL, cl);
    }
    cursor->gotoxy(left + 2, top + 2);
    cursor->generate<string>("Name: " + score->getPlayerName(), SCORE_COLOR);
    cursor->gotoxy(left + 2, top + 4);
    cursor->generate<string>("Score: ", SCORE_COLOR);

}


void MenuBox::initialize()
{
    draw();
}

void MenuBox::clear()
{
    /* clear the border */
    clearBorder();
    /* clear contents */
    string name_line = "Name: " + score->getPlayerName();
    string score_line = "Score: " + to_string(score->getPoints());
    for (int i = 0; i < name_line.length(); ++i)
    {
        cursor->gotoxy(left + 2 + i, top + 2);
        cursor->generate(NULL_SYMBOL, NULL_COLOR);
    }
    for (int i = 0; i < score_line.length(); ++i)
    {
        cursor->gotoxy(left + 2 + i, top + 4);
        cursor->generate(NULL_SYMBOL, NULL_COLOR);
    }
}