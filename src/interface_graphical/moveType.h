#ifndef MOVETYPE_H
#define MOVETYPE_H

class MoveType
{
public:
    virtual ~MoveType() = default;            // Destrutor virtual para garantir destruição correta
    virtual void applyMove(int x, int y) = 0; // Método virtual puro
    virtual void undoMove() = 0;              // Outro método virtual puro
};

#endif // MOVETYPE_H