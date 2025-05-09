#include "raylib.h"
#include <string>
#include <vector>
#include <iostream>
#include <array>

std::array<std::array<int, 8>, 8> tabuleiro;
int main() {
    // Inicializar Raylib
    InitWindow(800, 800, "Tabuleiro de Xadrez com FEN");
    SetTargetFPS(60);

    

    while (!WindowShouldClose()) {
    }

    
    return 0;
}