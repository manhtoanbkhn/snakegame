#include "game.h"




int main()
{
    Game game;
    game.menu();
    //game.initialize();
    //game.start();
    //game.end();

    //HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //// you can loop k higher to see more color choices
    //for (int k = 0; k < 255; k++)
    //{
    //    // pick the colorattribute k you want
    //    SetConsoleTextAttribute(hConsole, k);
    //    cout << k << " I want to be nice today!" << endl;
    //}

    system("pause");
    return 0;
}