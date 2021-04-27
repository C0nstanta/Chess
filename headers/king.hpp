#pragma once

#include "figure.hpp"

class King : public Piece
{
public:
    King(const Color, const PieceType, const Cell&);
    
    bool can_move(const std::pair<char, char>& p)override;

    void computeAttackedCells()override;
    
    bool checkCastl(const Cell&, const Cell&, const Color&);
    
};

