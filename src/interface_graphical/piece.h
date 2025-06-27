#ifndef PIECE_H
#define PIECE_H

#include "raylib.h"
#include "pieceType.h"
class Piece
{

public:
    PieceType pieceType;
    Color color;

    Piece()
    {
        this->pieceType = PieceType::NONE;
    }
    Piece(PieceType pieceType, Color color)
    {
        this->pieceType = pieceType;
        this->color = color;
    }
};

#endif // PIECE_H
