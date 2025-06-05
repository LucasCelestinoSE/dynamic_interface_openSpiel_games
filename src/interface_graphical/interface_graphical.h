#pragma once
#include "raylib.h"
#include <array>
#include <string>
#include <vector>
#ifndef Interface_Graphical
#define Interface_Graphical
class InterfaceGraphical
{
public:
    void drawBoardFromFenString(std::string fen_string);
    std::string getPieceType(char letter);
    std::vector<std::string> split(const std::string &str, char delimitador);
    struct FENInfo
    {
        std::string board;
        std::string activeColor;
        std::string castlingAvailability;
        std::string enPassantTarget;
        int halfmoveClock;
        int fullmoveNumber;
    };
};
#endif