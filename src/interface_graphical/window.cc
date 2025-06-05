#include "iostream"
#include "window.h"
using namespace std;
Window::Window(int w, int h, std::string t)
    : width(w), high(h), title(t)
{
    // Corpo do construtor
    std::cout << "Window::Window() - Janela '" << title << "' criada com "
              << width << "x" << high << std::endl;

    InitWindow(width, high, "raylib [core] example - basic window");

    SetTargetFPS(60);
}
string action;
void Window::gameLoop(bool isRunning, Board board)
{
    while (!WindowShouldClose())
    {
        Vector2 mousePostion = GetMousePosition();
        BeginDrawing();
        board.draw();

        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            std::cout << "Mouse foi apertado !" << std::endl;
            Square *sq = board.getSquareAt(mousePostion.x, mousePostion.y);
            cout << sq->getRow() << sq->getColString() << endl;
            cout << sq->getPiece() << endl;
        }
        EndDrawing();
    }
};
