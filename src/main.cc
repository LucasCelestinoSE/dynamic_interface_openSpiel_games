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
    state->ApplyAction(state->StringToAction("e4"));
    board.updateFromState(state->ToString());
    cout << board.toString() << endl;
    board.drawBoard();

    return 0;
}