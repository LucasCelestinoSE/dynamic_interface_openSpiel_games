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
    int selectedRow = -1;
    int selectedCol = -1;

public:
    vector<vector<Square>> squares;

    Board(int rows = 8, int cols = 8);
    std::string toString();
    Piece getTypeFEN(std::string fen);
    void updateFromState(std::string fen); // Sincroniza o tabuleiro com o estado
    void fenToBoard(const std::string &fen);
    std::vector<PieceInfo> parseFenPlacement(const std::string &fen);
    void drawBoard();
    bool isSquareSelected(int row, int col);
    void selectSquare(int row, int col);
    void clearSelection();
    std::pair<int, int> getSelectedSquare();
    std::pair<int, int> getSquareFromMousePosition(Vector2 mousePos);
    void handleMouseClick(Vector2 mousePos);
};
