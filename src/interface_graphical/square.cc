#include "square.h"
#include "raylib.h"
#include <sstream>
std::string pieceTypeToString(PieceType piece)
{
    switch (piece)
    {
    case PAWN:
        return "Pawn";
    case ROOK:
        return "Rook";
    case KNIGHT:
        return "Knight";
    case BISHOP:
        return "Bishop";
    case QUEEN:
        return "Queen";
    case KING:
        return "King";
    case NONE:
        return "None";
    default:
        return "Unknown";
    }
}

Square::Square(int row, int col, Color color, Piece piece)
{
    this->row = row;
    this->col = col;
    this->color = color;
    this->piece = piece;
}

std::string Square::toString()
{
    std::ostringstream oss;

    // Adicionar a posição, cor e tipo de peça ao stream
    oss // << "Square("
        //    << "Row: " << row << ", "
        //    << "Col: " << col << ", ";
        // << "Color: (" << color.r << ", " << color.g << ", " << color.b << "), "
        << pieceTypeToString(piece.pieceType);

    return oss.str();
}
