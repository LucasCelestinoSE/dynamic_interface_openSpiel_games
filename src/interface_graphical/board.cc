#include "board.h"
#include "square.h"
#include "piece.h"
#include <cctype>
#include <sstream>
#include <iostream>
#include "raylib.h"
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
// iterar as colunas
// Se for letra, chama a função getTypefen
// Se for número
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

Piece getPieceFromChar(char fenChar)
{

    switch (fenChar)
    {
    case 'p':
        return Piece(PieceType::PAWN, BLACK);
    case 'P':
        return Piece(PieceType::PAWN, WHITE);
    case 'r':
        return Piece(PieceType::ROOK, BLACK);
    case 'R':
        return Piece(PieceType::ROOK, WHITE);
    case 'n':
        return Piece(PieceType::KNIGHT, BLACK);
    case 'N':
        return Piece(PieceType::KNIGHT, WHITE);
    case 'b':
        return Piece(PieceType::BISHOP, BLACK);
    case 'B':
        return Piece(PieceType::BISHOP, WHITE);
    case 'q':
        return Piece(PieceType::QUEEN, BLACK);
    case 'Q':
        return Piece(PieceType::QUEEN, WHITE);
    case 'k':
        return Piece(PieceType::KING, BLACK);
    case 'K':
        return Piece(PieceType::KING, WHITE);
    default:
        return Piece(); // Retorna uma peça vazia para caracteres inválidos
    }
}
std::vector<PieceInfo> Board::parseFenPlacement(const std::string &fen)
{
    std::vector<PieceInfo> boardPieces;
    int currentRow = 0;
    int currentCol = 0;

    for (char fenChar : fen)
    {
        // Para quando a parte de posicionamento das peças terminar (indicado por um espaço)
        if (fenChar == ' ')
        {
            break;
        }

        // Se for um dígito, ele indica quadrados vazios. Avançamos a coluna.
        if (isdigit(fenChar))
        {
            currentCol += (fenChar - '0'); // Converte char '1' para int 1, etc.
        }
        // Se for uma barra, pulamos para a próxima linha.
        else if (fenChar == '/')
        {
            currentRow++;
            currentCol = 0;
        }
        // Se for uma letra, é uma peça.
        else
        {
            Piece piece = getPieceFromChar(fenChar);
            // Adiciona a peça à lista se ela for válida
            if (piece.pieceType != PieceType::NONE)
            {
                boardPieces.push_back({currentRow, currentCol, piece});
                currentCol++;
            }
        }
    }

    return boardPieces;
}