#include "snake.h"


Snake::Snake(const Coordinate& head, SnakeBox* box, Score* score, int speed, int len, int direction)
    : length(len), head(head), direction(direction), box(box), speed(speed), score(score)
{
    initialized = false;
    gameOver = false;

    cursor = &Cursor::getInstance();

    for (int i = 1; i < length; ++i)
    {
        Coordinate node(head.x - i, head.y);
        node.symbol = SNAKE_BODY_SYMBOL;
        node.color = SNAKE_BODY_INIT_COLOR + ((i - 1) % SNAKE_BODY_COLOR_NUMBER) * SNAKE_BODY_STEP_COLOR;
        body.push_back(node);
    }
}

void Snake::generateHead()
{
    cursor->generate(head);
}

void Snake::generateBody()
{
    if (!initialized)
    {
        for (int i = 0; i < body.size(); ++i)
        {
            cursor->generate(body[i]);
        }
        initialized = true;
    }
    else
    {
        cursor->generate(body[0]);
    }
}

void Snake::initialize()
{
    generateHead();
    generateBody();
}

Coordinate Snake::getNextHead()
{
    Coordinate nextHead;
    nextHead.symbol = SNAKE_HEAD_SYMBOL;
    nextHead.color = SNAKE_HEAD_COLOR;

    if (direction == LEFT_DIRECTION)
    {
        if (head.x == box->Left() + 1)
        {
            nextHead.x = box->Left() + box->Width();
        }
        else
        {
            nextHead.x = head.x - 1;
        }
        nextHead.y = head.y;
    }
    else if (direction == RIGHT_DIRECTION)
    {
        if (head.x == box->Left() + box->Width())
        {
            nextHead.x = box->Left() + 1;
        }
        else
        {
            nextHead.x = head.x + 1;
        }
        nextHead.y = head.y;
    }
    else if (direction == UP_DIRECTION)
    {
        if (head.y == box->Top() + 1)
        {
            nextHead.y = box->Top() + box->Height();
        }
        else
        {
            nextHead.y = head.y - 1;
        }
        nextHead.x = head.x;
    }
    else
    {
        if (head.y == box->Top() + box->Height())
        {
            nextHead.y = box->Top() + 1;
        }
        else
        {
            nextHead.y = head.y + 1;
        }
        nextHead.x = head.x;
    }

    return nextHead;
}

int Snake::getNextMove()
{
    lock_guard<mutex> guard(moveMutex);
    int next = movement.front();
    movement.pop();
    return next;
}

bool Snake::movementIsEmpty()
{
    lock_guard<mutex> guard(moveMutex);
    return movement.empty();
}


void Snake::addNextMove(int next)
{
    lock_guard<mutex> guard(moveMutex);
    movement.push(next);
}

void Snake::move()
{
    Coordinate nextHead;
    int moveCount = 0;
    
    while (true)
    {
        chrono::system_clock::time_point start = chrono::system_clock::now();

        if (!movementIsEmpty())
        {
            direction = getNextMove();
        }

        nextHead = getNextHead();

        //// check if this position is in range or not
        //if (!box->contains(nextHead))
        //{
        //    // TODO: game over
        //    /*end_game = true;*/
        //    return;
        //}

        // check if snake collide its body
        if (collideBody(nextHead))
        {
            PlaySound(MAKEINTRESOURCE(102), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_NOSTOP);
            break;
        }
        Coordinate tail;
        if (initialized)
        {
            head.symbol = SNAKE_BODY_SYMBOL;
            head.color = SNAKE_BODY_INIT_COLOR + ((SNAKE_INIT_LEN - 1 + moveCount) % SNAKE_BODY_COLOR_NUMBER) * SNAKE_BODY_STEP_COLOR;
            body.insert(body.begin(), head);
            head = nextHead;
            if (head == box->Food())
            {
                PlaySound(MAKEINTRESOURCE(101), GetModuleHandle(NULL), SND_RESOURCE | SND_ASYNC | SND_NOSTOP);
                if (length < SNAKE_MAX_LEN)
                    length++;
                score->increase();
                score->update();
                cursor->clear(box->Food());
                box->generateFood(&head, body);
            }
            else
            {
                tail = body.back();
                body.erase(body.end() - 1);
            }
            moveCount = ++moveCount % SNAKE_BODY_COLOR_NUMBER;
        }
        generateHead();
        generateBody();
        if (tail.symbol != NULL_SYMBOL || length == SNAKE_MAX_LEN)
            cursor->clear(tail);

        chrono::system_clock::time_point end = chrono::system_clock::now();

        chrono::duration<double> duration = chrono::duration_cast<chrono::duration<double>>(end - start);

        const double sleepTime = 1. / speed - duration.count();

        if (sleepTime > 0)
            this_thread::sleep_for(chrono::milliseconds(static_cast<unsigned int>(sleepTime*1000)));
    }
    gameOver = true;
    bool hs = score->checkHighScoreAndSave();
    string message = hs ? "High Score!!!" : "Game Over!!!";
    score->notice(message);
    this_thread::sleep_for(chrono::milliseconds(2500));

    // clear current screen
    clear();
}

void Snake::clear()
{
    cursor->clear(head);
    for (unsigned int i = 0; i < body.size(); ++i)
    {
        cursor->clear(body[i]);
    }
}


void Snake::directionController()
{
    int lastDirection = direction;
    while (!gameOver)
    {
        if (GetKeyState('A') & 0x8000)
        {
            if (lastDirection != RIGHT_DIRECTION && lastDirection != LEFT_DIRECTION)
            {
                addNextMove(LEFT_DIRECTION);
                lastDirection = LEFT_DIRECTION;
            }
        }
        else if (GetKeyState('D') & 0x8000)
        {
            if (lastDirection != RIGHT_DIRECTION && lastDirection != LEFT_DIRECTION)
            {
                addNextMove(RIGHT_DIRECTION);
                lastDirection = RIGHT_DIRECTION;
            }
        }
        else if (GetKeyState('W') & 0x8000)
        {
            if (lastDirection != DOWN_DIRECTION && lastDirection != UP_DIRECTION)
            {
                addNextMove(UP_DIRECTION);
                lastDirection = UP_DIRECTION;
            }
        }
        else if (GetKeyState('S') & 0x8000)
        {
            if (lastDirection != UP_DIRECTION && lastDirection != DOWN_DIRECTION)
            {
                addNextMove(DOWN_DIRECTION);
                lastDirection = DOWN_DIRECTION;
            }
        }
        else
        {
            this_thread::sleep_for(chrono::milliseconds(50));
        }
    }
}

bool Snake::collideBody(const Coordinate& head)
{
    for (int i = 0; i < body.size(); ++i)
    {
        if (body[i].x == head.x && body[i].y == head.y)
            return true;
    }
    return false;
}