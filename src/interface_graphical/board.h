#include <string>
#include <vector>
#include "square.h"
#include "spiel.h"
#include "chess.h"
#include "pieceInfo.h"

using namespace std;
class Board
{
private:
    int rows;
    int cols;

public:
    vector<vector<Square>> squares;
    std::unique_ptr<open_spiel::State> chessState; // Estado lógico do jogo de xadrez

    Board(int rows = 8, int cols = 8);
    std::string toString();
    Piece getTypeFEN(std::string fen);
    void fenToBoard(const std::string &fen);
    std::vector<PieceInfo> parseFenPlacement(const std::string &fen);
};
