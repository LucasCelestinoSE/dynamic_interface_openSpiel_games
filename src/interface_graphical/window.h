#ifndef WINDOW_H
#define WINDOW_H

#include <string> // Precisamos disso para std::string
#include "raylib.h"
#include "board.h"
class Window
{
private:
    int width;
    int high;
    std::string title;
    bool isRunning;
    Board board;

public:
    Window(int w, int h, std::string t);
    void gameLoop(bool isRunning, Board board);
    // desenhar o tabuleiro na tela...
};

#endif // WINDOW_H