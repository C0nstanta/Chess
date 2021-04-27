#include "headers/bishop.hpp"
#include "headers/chessboard.hpp"


Bishop::Bishop(const Color color, const PieceType piece_type, const Cell& key)
            : Piece(color, piece_type, key){};

bool Bishop::can_move(const Cell& e_cell)
{
    auto b_cell = getPos();
    //Проверяем диагонали и что б не было наших там
    if (is_diag(b_cell, e_cell) && ChessBoard::is_clear_diagonal(b_cell, e_cell) )
    {
        return true;
    }
    return false;
};

void Bishop::computeAttackedCells()
{

    auto pieceType = getPieceType();
    auto b_cell = getPos();
    auto color = getColor();
    
    std::set<Cell> tmp_set;

    tmp_set = ChessBoard::doDiagAttackSet(b_cell, pieceType, color);
    
    addAttacksSet(tmp_set, getColor());
}
