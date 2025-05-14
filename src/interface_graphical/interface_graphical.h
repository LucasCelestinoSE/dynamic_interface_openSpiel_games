#pragma once
#include "raylib.h"
#include <array>
#include <string>

class InterfaceGraphical {
public:
    Texture2D whitePawnTexture;

    void loadAssets();
    void unloadAssets();
    void drawWhitePawn(int x, int y, int size);
    void drawChessBoard(const std::array<std::array<char, 8>, 8>& chess_board);
};