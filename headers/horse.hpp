#pragma once

#include "figure.hpp"

class Horse : public Piece
{
public:
    Horse(const Color, const PieceType, const Cell&) ;

    void computeAttackedCells()override;
    
    bool can_move(const Cell& p)override;
};


