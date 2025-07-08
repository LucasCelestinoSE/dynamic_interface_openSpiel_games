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

    Board(int rows = 8, int cols = 8);
    std::string toString();
    Piece getTypeFEN(std::string fen);
    void updateFromState(std::string fen); // Sincroniza o tabuleiro com o estado
    void fenToBoard(const std::string &fen);
    std::vector<PieceInfo> parseFenPlacement(const std::string &fen);
    void drawBoard();
};
