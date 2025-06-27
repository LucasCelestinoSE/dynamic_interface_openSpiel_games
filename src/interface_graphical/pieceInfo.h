#include "piece.h"

struct PieceInfo
{
    int row;     // Linha no tabuleiro (0 = rank 8, 7 = rank 1)
    int col;     // Coluna no tabuleiro (0 = file 'a', 7 = file 'h')
    Piece piece; // A peça com seu tipo e cor
};