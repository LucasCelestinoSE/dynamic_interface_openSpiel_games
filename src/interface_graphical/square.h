#ifndef SQUARE_H
#define SQUARE_H

#include "raylib.h"
#include <string>
#include "piece.h"
using namespace std;

class Square
{

private:
    int row, col; // Posição do quadrado no tabuleiro
    Color color;  // Cor do quadrado
    int size;     // interface gráfica.

public:
    Piece piece;
    Square() : row(0), col(0), color(LIGHTGRAY) {} // Preciso para inicializar o board pela primeira vez
    Square(int row, int colum, Color color, Piece piece);
    string toString();
};
#endif // SQUARE_H