#ifndef PIECE_H
#define PIECE_H

#include <string>
#include "raylib.h"
#include <vector>
#include <iostream>
#include <pieceType.cc>
class Piece
{
private:
    PieceType type;
    Color color;
    std::string TexturePath;

public:
    void movePiece()
    {
    }
};

#endif // PIECE_H