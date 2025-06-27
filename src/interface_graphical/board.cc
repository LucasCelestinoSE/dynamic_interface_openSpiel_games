#include "board.h"
#include "square.h"
#include "piece.h"
#include <cctype>
#include <sstream>
#include <iostream>

Board::Board(int rows, int cols) : rows(rows), cols(cols)
{
    // Redimensionar o vetor externo para o número de linhas
    squares.resize(rows);
    // PieceType = "" string é na verdade um numero, ou seja, envia vazia
    // PieceType =
    for (int row = 0; row < rows; ++row)
    {
        // Redimensionar cada linha para o número de colunas
        Piece piece = Piece();
        squares[row].resize(cols);

        for (int col = 0; col < cols; ++col)
        {
            // Inicializar cada quadrado
            Color color = ((row + col) % 2 == 0) ? LIGHTGRAY : DARKGRAY;
            squares[row][col] = Square(row, col, color, piece);
        }
    }
}

std::string Board::toString()
{
    std::ostringstream oss;

    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            // Adicionar a posição e o tipo de peça ao stream
            oss << "[" << row << "," << col << ": " << squares[row][col].toString() << "] ";
        }
        oss << "\n"; // Nova linha após cada linha do tabuleiro
    }

    return oss.str();
}

Piece Board::getTypeFEN(std::string fen)
{

    if (fen.empty())
    {
        return Piece();
    }
    char fenChar = fen[0];
    PieceType type;
    Color color;

    switch (fenChar)
    {
    case 'p':
        type = PieceType::PAWN;
        color = BLACK;
        break;
    case 'P':
        type = PieceType::PAWN;
        color = WHITE;
        break;
    case 'r':
        type = PieceType::ROOK;
        color = BLACK;
        break;
    case 'R':
        type = PieceType::ROOK;
        color = WHITE;
        break;
    case 'n':
        type = PieceType::KNIGHT;
        color = BLACK;
        break;
    case 'N':
        type = PieceType::KNIGHT;
        color = WHITE;
        break;
    case 'b':
        type = PieceType::BISHOP;
        color = BLACK;
        break;
    case 'B':
        type = PieceType::BISHOP;
        color = WHITE;
        break;
    case 'q':
        type = PieceType::QUEEN;
        color = BLACK;
        break;
    case 'Q':
        type = PieceType::QUEEN;
        color = WHITE;
        break;
    case 'k':
        type = PieceType::KING;
        color = BLACK;
        break;
    case 'K':
        type = PieceType::KING;
        color = WHITE;
        break;
    }
    return Piece(type, color);
}
