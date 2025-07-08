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
// Adicione esta função no square.cc ou em um arquivo de utilitários
std::string colorToString(Color color)
{
    // Verificar se é uma cor conhecida
    if (color.r == WHITE.r && color.g == WHITE.g &&
        color.b == WHITE.b && color.a == WHITE.a)
    {
        return "WHITE";
    }
    else if (color.r == BLACK.r && color.g == BLACK.g &&
             color.b == BLACK.b && color.a == BLACK.a)
    {
        return "BLACK";
    }
    else
    {
        return "EU ODEIO ESSA LINGUAGEM ! ";
    }
}
std::string Square::toString()
{
    std::ostringstream oss;

    oss << "Square("
        << "Row: " << row << ", "
        << "Col: " << col << ", "
        << "Color: " << colorToString(piece.color) << ", " // Use a função colorToString
        << "Piece: " << pieceTypeToString(piece.pieceType) << ")";

    return oss.str();
}