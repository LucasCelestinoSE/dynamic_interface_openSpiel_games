#ifndef BOARD_H
#define BOARD_H

#include <string>
#include "raylib.h"
#include <vector>
#include "square.h"

class Board
{
private:
    std::vector<Square> square; // Vetor de quadrados
    int rows;                   // Número de linhas
    int cols;                   // Número de colunas

public:
    Square *selectedSquare = nullptr;        // Quadrado atualmente selecionado
    Square *previousSquare = nullptr;        // Quadrado anteriormente selecionado
    Board(int rows = 8, int cols = 8);       // Construtor com valores padrão para 8x8
    void draw();                             // Método para desenhar o tabuleiro
    void setFromFen(const std::string &fen); // Configurar o tabuleiro com base em uma FEN string
    Square *getSquareAt(int x, int y);       // Retorna o quadrado na posição (x, y)
};

#endif // BOARD_H