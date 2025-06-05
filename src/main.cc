#include "raylib.h"
#include <string>
#include <iostream>
#include "board.h"
#include "spiel.h"
#include "chess.h"
#include "window.h"
int main()
{
    SetTargetFPS(60);

    Board board; // Criar um tabuleiro 8x8
    auto game = open_spiel::LoadGame("chess");
    auto state = game->NewInitialState();

    state->ApplyAction(state->StringToAction("e4"));
    state->ApplyAction(state->StringToAction("d5"));
    state->ApplyAction(state->StringToAction("exd5"));
    state->ApplyAction(state->StringToAction("a5"));
    state->ApplyAction(state->StringToAction("a3"));
    state->ApplyAction(state->StringToAction("a4"));
    state->ApplyAction(state->StringToAction("h3"));
    state->ApplyAction(state->StringToAction("Ra5"));
    state->ApplyAction(state->StringToAction("b3"));
    state->ApplyAction(state->StringToAction("h5"));
    state->ApplyAction(state->StringToAction("b4"));
    state->ApplyAction(state->StringToAction("Ra8"));
    std::cout << state->ToString() << std::endl;
    std::cout << "Ações legais:" << std::endl;
    std::cout << state->CurrentPlayer() << std::endl;
    std::vector<open_spiel::Action> legal_actions = state->LegalActions();
    for (open_spiel::Action action : legal_actions)
    {
        std::cout << "  " << state->ActionToString(state->CurrentPlayer(), action) << std::endl;
    }
    std::cout << "------------------------" << std::endl;
    board.setFromFen(state->ToString());

    Window window(800, 800, "Olá mundo");
    window.gameLoop(1, board);
    return 0;
}