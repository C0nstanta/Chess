#pragma once

#include "figure.hpp"

class Pawn : public Piece
{
public:
    Pawn(const Color color, const PieceType piece_type, const Cell& key)
                : Piece(color, piece_type, key){};

    void computeAttackedCells()override;
    
    bool can_move(const Cell& p)override;

};

