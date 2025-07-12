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
    const int squareSize = 80;
    const int boardStartX = (screenWidth - (cols * squareSize)) / 2;
    const int boardStartY = (screenHeight - (rows * squareSize)) / 2;

    InitWindow(screenWidth, screenHeight, "Chess Board - FEN Notation");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(Color{245, 245, 220, 255});

        Vector2 mousePosition = GetMousePosition();

        // Detectar clique do mouse
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            handleMouseClick(mousePosition);
        }

        // Título
        DrawText("CHESS BOARD", screenWidth / 2 - MeasureText("CHESS BOARD", 30) / 2, 30, 30, DARKBLUE);

        // Desenhar o tabuleiro
        for (int row = 0; row < rows; ++row)
        {
            for (int col = 0; col < cols; ++col)
            {
                int x = boardStartX + col * squareSize;
                int y = boardStartY + row * squareSize;

                // Determinar cor do quadrado
                Color squareColor;
                if ((row + col) % 2 == 0)
                {
                    squareColor = Color{240, 217, 181, 255}; // Bege claro
                }
                else
                {
                    squareColor = Color{181, 136, 99, 255}; // Marrom
                }

                // Destacar quadrado selecionado
                if (isSquareSelected(row, col))
                {
                    squareColor = Color{255, 255, 0, 180}; // Amarelo translúcido
                }

                // Desenhar quadrado
                DrawRectangle(x, y, squareSize, squareSize, squareColor);

                // Desenhar borda mais grossa se selecionado
                if (isSquareSelected(row, col))
                {
                    DrawRectangleLines(x, y, squareSize, squareSize, RED);
                    DrawRectangleLines(x - 1, y - 1, squareSize + 2, squareSize + 2, RED);
                }
                else
                {
                    DrawRectangleLines(x, y, squareSize, squareSize, DARKGRAY);
                }

                // Desenhar peça (código existente)
                Piece piece = squares[row][col].piece;
                if (piece.pieceType != PieceType::NONE)
                {
                    // ... código existente para desenhar peças ...
                    char pieceChar = ' ';
                    bool isWhite = (piece.color.r == WHITE.r && piece.color.g == WHITE.g &&
                                    piece.color.b == WHITE.b && piece.color.a == WHITE.a);

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

                    Color pieceTextColor = isWhite ? WHITE : BLACK;
                    Color outlineColor = isWhite ? BLACK : WHITE;

                    char pieceString[2] = {pieceChar, '\0'};
                    int fontSize = squareSize / 2;
                    int textWidth = MeasureText(pieceString, fontSize);
                    int textX = x + (squareSize - textWidth) / 2;
                    int textY = y + (squareSize - fontSize) / 2;

                    // Desenhar contorno
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

                    DrawText(pieceString, textX, textY, fontSize, pieceTextColor);
                }
            }
        }

        // Mostrar informações do quadrado selecionado
        if (selectedRow != -1 && selectedCol != -1)
        {
            DrawText(TextFormat("Selecionado: (%d,%d)", selectedRow, selectedCol),
                     50, screenHeight - 100, 20, DARKBLUE);
            DrawText(TextFormat("Coordenada: %c%d", 'a' + selectedCol, rows - selectedRow),
                     50, screenHeight - 75, 20, DARKBLUE);
        }

        // Coordenadas e legenda (código existente)...

        EndDrawing();
    }

    CloseWindow();
}

std::pair<int, int> Board::getSquareFromMousePosition(Vector2 mousePos)
{
    const int screenWidth = 1360;
    const int screenHeight = 760;
    const int squareSize = 80;
    const int boardStartX = (screenWidth - (cols * squareSize)) / 2;
    const int boardStartY = (screenHeight - (rows * squareSize)) / 2;

    // Verificar se o mouse está dentro do tabuleiro
    if (mousePos.x < boardStartX || mousePos.x > boardStartX + (cols * squareSize) ||
        mousePos.y < boardStartY || mousePos.y > boardStartY + (rows * squareSize))
    {
        return std::make_pair(-1, -1); // Fora do tabuleiro
    }

    // Calcular qual quadrado foi clicado
    int col = (mousePos.x - boardStartX) / squareSize;
    int row = (mousePos.y - boardStartY) / squareSize;

    // Verificar se está dentro dos limites
    if (row >= 0 && row < rows && col >= 0 && col < cols)
    {
        return std::make_pair(row, col);
    }

    return std::make_pair(-1, -1); // Fora dos limites
}

void Board::handleMouseClick(Vector2 mousePos)
{
    std::pair<int, int> square = getSquareFromMousePosition(mousePos);

    if (square.first != -1 && square.second != -1)
    {
        int row = square.first;
        int col = square.second;

        // Se já há um quadrado selecionado e clicamos em outro
        if (selectedRow != -1 && selectedCol != -1)
        {
            if (selectedRow == row && selectedCol == col)
            {
                // Desselecionar se clicar no mesmo quadrado
                clearSelection();
                std::cout << "Quadrado desmarcado" << std::endl;
            }
            else
            {
                // Movimento: de (selectedRow, selectedCol) para (row, col)
                std::cout << "Movimento: de (" << selectedRow << "," << selectedCol
                          << ") para (" << row << "," << col << ")" << std::endl;

                // Aqui você pode implementar a lógica do movimento
                // Por exemplo, chamar uma função para aplicar o movimento

                clearSelection(); // Limpar seleção após movimento
            }
        }
        else
        {
            // Selecionar novo quadrado
            selectSquare(row, col);
            std::cout << "Quadrado selecionado: (" << row << "," << col << ")" << std::endl;

            // Mostrar informações sobre o quadrado selecionado
            if (squares[row][col].piece.pieceType != PieceType::NONE)
            {
                std::cout << "Peça: " << squares[row][col].toString() << std::endl;
            }
            else
            {
                std::cout << "Quadrado vazio" << std::endl;
            }
        }
    }
}

void Board::selectSquare(int row, int col)
{
    selectedRow = row;
    selectedCol = col;
}

void Board::clearSelection()
{
    selectedRow = -1;
    selectedCol = -1;
}

bool Board::isSquareSelected(int row, int col)
{
    return (selectedRow == row && selectedCol == col);
}

std::pair<int, int> Board::getSelectedSquare()
{
    return std::make_pair(selectedRow, selectedCol);
}