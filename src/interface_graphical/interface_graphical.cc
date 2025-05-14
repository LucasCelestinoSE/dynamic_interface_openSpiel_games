#include "interface_graphical.h"

void InterfaceGraphical::loadAssets() {
    whitePawnTexture = LoadTexture("src/assets/white_pawn.png");
}

void InterfaceGraphical::unloadAssets() {
    UnloadTexture(whitePawnTexture);
}

void InterfaceGraphical::drawWhitePawn(int x, int y, int size) {
    DrawTextureEx(whitePawnTexture, (Vector2){(float)x, (float)y}, 0.0f, (float)size / whitePawnTexture.width, WHITE);
}

void InterfaceGraphical::drawChessBoard(const std::array<std::array<char, 8>, 8>& chess_board) {
    int squareSize = 100;
    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            Color color = ((row + col) % 2 == 0) ? LIGHTGRAY : DARKGRAY;
            DrawRectangle(col * squareSize, row * squareSize, squareSize, squareSize, color);

            char piece = chess_board[row][col];
            if (piece == 'P') {
                drawWhitePawn(col * squareSize, row * squareSize, squareSize);
            }
        }
    }
}