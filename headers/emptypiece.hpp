#pragma once
#include "figure.hpp"

#include <iostream>
#include <iostream>


class EmptyPiece: public Piece
{
public:
    EmptyPiece(const Color, const PieceType, const Cell&);
    
    void computeAttackedCells()override;

    bool can_move(const Cell& p)override;
};


