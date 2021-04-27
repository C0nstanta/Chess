#pragma once

#include "figure.hpp"
#include <iostream>


class Bishop : public Piece
{
public:
    Bishop(const Color, const PieceType, const Cell&);

    void computeAttackedCells()override;
    
    bool can_move(const Cell& p)override;
};


