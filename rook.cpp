#include "headers/rook.hpp"
#include "headers/chessboard.hpp"



Rook::Rook(const Color color, const PieceType piece_type, const Cell& key)
            : Piece(color, piece_type, key){};

bool Rook::can_move(const std::pair<char, char>& e_cell)
{
    auto b_cell = getPos();
    is_horiz(b_cell, e_cell);

    
    if (((is_horiz(b_cell, e_cell) && ChessBoard::is_clear_horizontal(b_cell,
                                                                      e_cell))
        ||( is_vert(b_cell, e_cell) && ChessBoard::is_clear_vertical(b_cell,
                                                                     e_cell)))
        )
    {
        setCountMoves();
        return true;
    }
    setCountMoves();
    return false;
};


void Rook::computeAttackedCells()
{

    auto pieceType = getPieceType();
    auto b_cell = getPos();
    auto color = getColor();
    
    std::set<Cell> tmp_set_vert;
    std::set<Cell> tmp_set_horiz;
    
    tmp_set_vert = ChessBoard::doVertAttackSet(b_cell, pieceType, color);
    tmp_set_horiz = ChessBoard::doHorAttackSet(b_cell, pieceType, color);
    
    std::set<Cell> tmp_set(tmp_set_vert);
    tmp_set.insert(tmp_set_horiz.begin(), tmp_set_horiz.end());

    addAttacksSet(tmp_set, getColor());

}
