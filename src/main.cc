#include "raylib.h"
#include <string>
#include <iostream>
#include "board.h"
#include "spiel.h"
#include "chess.h"
using namespace std;
int main()
{
    Board board;

    auto game = open_spiel::LoadGame("chess");
    auto state = game->NewInitialState();
    cout << state->ToString() << endl;
    cout << board.toString() << endl;

    return 0;
}