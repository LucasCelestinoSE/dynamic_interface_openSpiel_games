#include "board.h"
#include "square.h"
#include <cctype>

Board::Board(int rows, int cols) : rows(rows), cols(cols)
{
    // Inicializar o vetor de quadrados
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            // Alternar cores entre LIGHTGRAY e DARKGRAY
            Color color = ((row + col) % 2 == 0) ? GREEN : DARKGRAY;
            square.push_back(Square(row, col, color));
        }
    }
}

void Board::draw()
{
    for (const auto &sq : square)
    {
        sq.draw(); // Desenhar cada quadrado
    }
}

void Board::setFromFen(const std::string &fen)
{
    // Limpar o estado anterior do tabuleiro
    for (auto &sq : square)
    {
        sq.setPiece(' '); // Remover qualquer peça do quadrado
    }

    int row = 0, col = 0;

    for (char c : fen)
    {
        if (c == ' ')
            break; // Fim da parte do tabuleiro na FEN string

        if (std::isdigit(c))
        {
            // Avançar colunas para espaços vazios
            col += c - '0';
        }
        else if (c == '/')
        {
            // Avançar para a próxima linha
            row++;
            col = 0;
        }
        else
        {
            // Atualizar o quadrado com a peça correspondente
            if (row < rows && col < cols)
            {
                int index = row * cols + col;
                square[index].setPiece(c); // Atualizar a peça no quadrado
                col++;
            }
        }
    }
}

Square *Board::getSquareAt(int x, int y)
{

    for (auto &sq : square)
    {
        if (sq.contains(x, y))
        {

            return &sq; // Retornar o quadrado que contém o ponto (x, y)
        }
    }
    return nullptr;
}

// CLicar em um quadrado do tabuleiro
// Selecionar o quadrado clicado e travar os outros de serem pegos.
// Destravar somente quando o mesmo for clicado !
