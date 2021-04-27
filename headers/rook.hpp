#pragma once
#include "figure.hpp"


class Rook : public Piece
{
public:
    Rook(const Color, const PieceType, const Cell&);

    void computeAttackedCells()override;

    bool can_move(const Cell& p)override;
    
};


