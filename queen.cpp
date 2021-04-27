#include "headers/queen.hpp"
#include "headers/chessboard.hpp"


Queen::Queen(const Color color, const PieceType piece_type, const Cell& key)
            : Piece(color, piece_type, key){};

bool Queen::can_move(const std::pair<char, char>& e_cell)
{
    auto b_cell = getPos();
    bool diag = ChessBoard::is_clear_diagonal(b_cell, e_cell);
    bool vert = ChessBoard::is_clear_vertical(b_cell, e_cell);
    bool horiz = ChessBoard::is_clear_horizontal(b_cell, e_cell);

    bool is_diag = Piece::is_diag(b_cell, e_cell);
    bool is_vert = Piece::is_vert(b_cell, e_cell);
    bool is_horiz = Piece::is_horiz(b_cell, e_cell);
    
    bool is_white = (getColor() == Color::WHITE);
    
    if (is_white)
    {
        if ((is_diag && diag) || (is_vert && vert) || (is_horiz && horiz))
            return true;
    }
    else
    {
        if ((is_diag && diag) || (is_vert && vert) || (is_horiz && horiz))
            return true;
    }
    
    return false;
};


void Queen::computeAttackedCells()
{    
    auto pieceType = getPieceType();
    auto b_cell = getPos();
    auto color = getColor();
    
    std::set<Cell> tmp_set_vert;
    std::set<Cell> tmp_set_horiz;
    std::set<Cell> tmp_set_diag;
    
    tmp_set_vert = ChessBoard::doVertAttackSet(b_cell, pieceType, color);
    tmp_set_horiz = ChessBoard::doHorAttackSet(b_cell, pieceType, color);
    tmp_set_diag = ChessBoard::doDiagAttackSet(b_cell, pieceType, color);
    
    std::set<Cell> tmp_set(tmp_set_vert);
    tmp_set.insert(tmp_set_horiz.begin(), tmp_set_horiz.end());
    tmp_set.insert(tmp_set_diag.begin(), tmp_set_diag.end());

    addAttacksSet(tmp_set, getColor());
}
