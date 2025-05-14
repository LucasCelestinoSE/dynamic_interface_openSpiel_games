#include "raylib.h"
#include <string>
#include <array>
#include <cctype>
#if defined(__EMSCRIPTEN__)
#include <emscripten/emscripten.h>
#include "interface_graphical/interface_graphical.h"

#endif
InterfaceGraphical gui;

Texture2D whitePawnTexture;
// Função para converter FEN em matriz 8x8 de chars
std::array<std::array<char, 8>, 8> parseFEN(const std::string& fen) {
    std::array<std::array<char, 8>, 8> board{};
    int row = 0, col = 0;
    for (char c : fen) {
        if (c == ' ') break; // FEN termina a posição antes do primeiro espaço
        if (c == '/') { row++; col = 0; }
        else if (isdigit(c)) col += c - '0';
        else board[row][col++] = c;
    }
    return board;
}
void loadAssets() {
    whitePawnTexture = LoadTexture("src/assets/white_pawn.png");
}
void unloadAssets() {
    UnloadTexture(whitePawnTexture);
}

void drawWhitePawn(int x, int y, int size) {
    DrawTextureEx(whitePawnTexture, (Vector2){(float)x, (float)y}, 0.0f, (float)size / whitePawnTexture.width, WHITE);
}

// Exemplo de FEN inicial do xadrez
std::string start_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
auto chess_board = parseFEN(start_fen);

struct ShapeDrawer {
    void drawSquare(int x, int y, int size, Color color) {
        DrawRectangle(x, y, size, size, color);
    }
    void drawText(int x, int y, const char* text, int fontSize, Color color) {
        DrawText(text, x, y, fontSize, color);
    }
};

void drawChessBoard() {
    int squareSize = 100;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Color color = ((row + col) % 2 == 0) ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, color);

            char piece = chess_board[row][col];
            if (piece == 'P') { // Peão branco
                drawWhitePawn(col * squareSize, row * squareSize, squareSize);
            }
        }
    }
}

void main_loop() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    drawChessBoard();
    EndDrawing();
}

int main() {
    InitWindow(800, 800, "Chess board with FEN");
    loadAssets();
    SetTargetFPS(60);
#if defined(__EMSCRIPTEN__)
    emscripten_set_main_loop(main_loop, 0, 1);
#else
    while (!WindowShouldClose()) {
        main_loop();
    }
#endif
    unloadAssets();
    CloseWindow();
    return 0;
}