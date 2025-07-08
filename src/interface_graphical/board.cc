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
            oss << squares[row][col].toString() << "] ";
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
void Board::updateFromState(std::string fen)
{

    // Primeiro, limpe todas as peças
    for (int row = 0; row < rows; ++row)
    {
        for (int col = 0; col < cols; ++col)
        {
            squares[row][col].piece = Piece(); // Peça vazia
        }
    }

    // Parse apenas a parte de posicionamento das peças
    std::vector<PieceInfo> pieces = parseFenPlacement(fen);

    // Atualizar o tabuleiro com as peças
    for (const auto &pieceInfo : pieces)
    {
        if (pieceInfo.row < rows && pieceInfo.col < cols)
        {
            squares[pieceInfo.row][pieceInfo.col].piece = (pieceInfo.piece);
        }
    }
}
void Board::drawBoard()
{
    const int screenWidth = 1360;
    const int screenHeight = 760;
    const int squareSize = 80;                                        // Tamanho de cada quadrado
    const int boardStartX = (screenWidth - (cols * squareSize)) / 2;  // Centralizar horizontalmente
    const int boardStartY = (screenHeight - (rows * squareSize)) / 2; // Centralizar verticalmente

    InitWindow(screenWidth, screenHeight, "Chess Board - FEN Notation");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{245, 245, 220, 255}); // Fundo bege claro

        // Título
        DrawText("CHESS BOARD", screenWidth / 2 - MeasureText("CHESS BOARD", 30) / 2, 30, 30, DARKBLUE);

        // Desenhar o tabuleiro
        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                int x = boardStartX + col * squareSize;
                int y = boardStartY + row * squareSize;

                // Determinar cor do quadrado (padrão xadrez)
                Color squareColor;
                if ((row + col) % 2 == 0)
                {
                    squareColor = Color{240, 217, 181, 255}; // Bege claro
                }
                else
                {
                    squareColor = Color{181, 136, 99, 255}; // Marrom
                }

                // Desenhar quadrado
                DrawRectangle(x, y, squareSize, squareSize, squareColor);
                DrawRectangleLines(x, y, squareSize, squareSize, DARKGRAY);

                // Desenhar peça se houver
                Piece piece = squares[row][col].piece;
                if (piece.pieceType != PieceType::NONE)
                {
                    // Determinar o caractere da peça seguindo notação FEN
                    char pieceChar = ' ';
                    bool isWhite = false;

                    // Verificar se é peça branca (assumindo que WHITE da raylib indica peça branca)
                    // Se piece.color for do tipo Color da raylib, comparamos com WHITE
                    if (piece.color.r == WHITE.r && piece.color.g == WHITE.g &&
                        piece.color.b == WHITE.b && piece.color.a == WHITE.a)
                    {
                        isWhite = true;
                    }

                    switch (piece.pieceType)
                    {
                    case PieceType::PAWN:
                        pieceChar = isWhite ? 'P' : 'p';
                        break;
                    case PieceType::ROOK:
                        pieceChar = isWhite ? 'R' : 'r';
                        break;
                    case PieceType::KNIGHT:
                        pieceChar = isWhite ? 'N' : 'n';
                        break;
                    case PieceType::BISHOP:
                        pieceChar = isWhite ? 'B' : 'b';
                        break;
                    case PieceType::QUEEN:
                        pieceChar = isWhite ? 'Q' : 'q';
                        break;
                    case PieceType::KING:
                        pieceChar = isWhite ? 'K' : 'k';
                        break;
                    default:
                        pieceChar = '?';
                        break;
                    }

                    // Configurar cores para desenhar a peça
                    Color pieceTextColor = isWhite ? WHITE : BLACK;
                    Color outlineColor = isWhite ? BLACK : WHITE;

                    // Criar string válida para DrawText - CORREÇÃO PRINCIPAL
                    char pieceString[2] = {pieceChar, '\0'};

                    // Calcular posição central para o texto
                    int fontSize = squareSize / 2;
                    int textWidth = MeasureText(pieceString, fontSize); // Usar pieceString aqui também
                    int textX = x + (squareSize - textWidth) / 2;
                    int textY = y + (squareSize - fontSize) / 2;

                    // Desenhar contorno para melhor visibilidade
                    for (int dx = -1; dx <= 1; dx++)
                    {
                        for (int dy = -1; dy <= 1; dy++)
                        {
                            if (dx != 0 || dy != 0)
                            {
                                DrawText(pieceString, textX + dx, textY + dy, fontSize, outlineColor);
                            }
                        }
                    }

                    // Desenhar a peça principal
                    DrawText(pieceString, textX, textY, fontSize, pieceTextColor);
                }
            }
        }

        // Desenhar coordenadas do tabuleiro
        // Letras (a-h) na parte inferior
        for (int col = 0; col < cols; ++col)
        {
            char letter = 'a' + col;
            int x = boardStartX + col * squareSize + squareSize / 2;
            int y = boardStartY + rows * squareSize + 10;
            DrawText(TextFormat("%c", letter), x - 5, y, 20, DARKBLUE);
        }

        // Números (1-8) na lateral esquerda
        for (int row = 0; row < rows; ++row)
        {
            int number = rows - row; // Inverter para mostrar 8-1
            int x = boardStartX - 25;
            int y = boardStartY + row * squareSize + squareSize / 2;
            DrawText(TextFormat("%d", number), x, y - 10, 20, DARKBLUE);
        }

        // Legenda
        int legendX = 50;
        int legendY = 100;
        DrawText("PIECES LEGEND:", legendX, legendY, 16, DARKBLUE);
        DrawText("White pieces (FEN): P R N B Q K", legendX, legendY + 25, 14, WHITE);
        DrawText("Black pieces (FEN): p r n b q k", legendX, legendY + 50, 14, BLACK);

        DrawText("P/p = Pawn", legendX, legendY + 80, 12, GRAY);
        DrawText("R/r = Rook", legendX, legendY + 95, 12, GRAY);
        DrawText("N/n = Knight", legendX, legendY + 110, 12, GRAY);
        DrawText("B/b = Bishop", legendX, legendY + 125, 12, GRAY);
        DrawText("Q/q = Queen", legendX, legendY + 140, 12, GRAY);
        DrawText("K/k = King", legendX, legendY + 155, 12, GRAY);

        EndDrawing();
    }

    CloseWindow();
}