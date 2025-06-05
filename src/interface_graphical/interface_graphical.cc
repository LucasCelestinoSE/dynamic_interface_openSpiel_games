#include "interface_graphical.h"
#include <cctype>

#include "interface_graphical.h"
#include <cctype>
#include <map>
#include <sstream>
#include <array>
void InterfaceGraphical::drawBoardFromFenString(std::string fen_string)
{
    int squareSize = 100;
    int row = 0, col = 0;

    // Iterar sobre a FEN string
    for (char c : fen_string)

    {
        if (std::isdigit(c))
        {
            // Desenhar quadrados vazios para os espaços representados por números
            int emptySpaces = c - '0';
            for (int i = 0; i < emptySpaces; ++i)
            {
                Color color = ((row + col) % 2 == 0) ? LIGHTGRAY : DARKGRAY;
                DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, color);
                col++;
            }
        }
        else if (c == '/')
        {
            // Avançar para a próxima linha
            row++;
            col = 0;
        }
        else
        {
            // Desenhar o quadrado do tabuleiro
            Color color = ((row + col) % 2 == 0) ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, color);

            // Desenhar a peça (representada pelo caractere)
            DrawText(std::string(1, c).c_str(), col * squareSize + squareSize / 4, row * squareSize + squareSize / 4, 40, BLACK);

            col++;
        }
    }
}
