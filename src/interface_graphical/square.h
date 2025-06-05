#ifndef SQUARE_H
#define SQUARE_H

#include "raylib.h"
#include <string>

class Square
{
private:
    int row, col; // Posição do quadrado no tabuleiro
    Color color;  // Cor do quadrado
    int size;     // Tamanho do quadrado (em pixels)
    char piece;   // Peça no quadrado (ou vazio)
    bool selected;

public:
    Square(int row, int col, Color color, int size = 100)
        : row(row), col(col), color(color), size(size), piece(' ') {}

    void draw() const
    {
        // Desenhar o quadrado
        DrawRectangle(col * size, row * size, size, size, color);

        // Desenhar a peça (se houver)
        if (piece != ' ')
        {
            // Determinar a cor da letra com base no tipo da peça
            Color textColor = std::isupper(piece) ? WHITE : BLACK;

            // Desenhar a peça no centro do quadrado
            DrawText(std::string(1, piece).c_str(),
                     col * size + size / 4,
                     row * size + size / 4,
                     40, textColor);
        }
    }

    void setPiece(char p)
    {
        piece = p; // Definir a peça no quadrado
    }
    bool isEqual(const Square &other) const
    {
        return row == other.row && col == other.col && piece == other.piece;
    }
    void setColor(Color rgb)
    {
        color = rgb;
    }
    char getPiece() const
    {
        return piece; // Retorna a peça no quadrado
    }
    void setSelect()
    {
        selected = true;
    }
    int getRow() const
    {
        return 8 - row; // Retorna a linha do quadrado
    }
    char getColString() const
    {
        switch (col)
        {
        case 0:
            return 'a';
        case 1:
            return 'b';
        case 2:
            return 'c';
        case 3:
            return 'd';
        case 4:
            return 'e';
        case 5:
            return 'f';
        case 6:
            return 'g';
        case 7:
            return 'h';
        }
    }
    int getCol() const
    {
        return col; // Retorna a coluna do quadrado
    }
    int getSize() const
    {
        return size;
    }
    Color getColor() const
    {
        return color;
    }
    bool contains(int x, int y) const
    {
        // Verificar se o ponto (x, y) está dentro do quadrado
        int xStart = col * size;
        int yStart = row * size;
        return x >= xStart && x < xStart + size && y >= yStart && y < size + yStart;
    }
};

#endif // SQUARE_H