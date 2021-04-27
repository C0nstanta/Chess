#pragma once

#include "figure.hpp"

class Queen : public Piece
{
public:
    Queen(const Color, const PieceType, const Cell&);

    bool can_move(const Cell&  p)override;
    
    void computeAttackedCells()override;
};

