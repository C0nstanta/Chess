
#include "headers/emptypiece.hpp"
#include "headers/chessboard.hpp"
#include "headers/figure.hpp"


EmptyPiece::EmptyPiece(const Color color, const PieceType piece_type,
           const Cell& key)
            : Piece(color, piece_type, key){};

bool EmptyPiece::can_move(const std::pair<char, char>& p)
{
    
    return true;
};

void EmptyPiece::computeAttackedCells(){}


