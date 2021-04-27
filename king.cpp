
#include "headers/king.hpp"
#include "figure.hpp"
#include "chessboard.hpp"
#include "emptypiece.hpp"
#include <utility>


King::King(const Color color, const PieceType piece_type, const Cell& key)
    : Piece(color, piece_type, key) {}

bool King::can_move(const Cell& e_cell)
{


    auto color = getColor();
    auto b_cell = getPos();
    char b_x = b_cell.first;
    char b_y = b_cell.second;
    
    char e_x = e_cell.first;
    char e_y = e_cell.second;
    
    if (std::abs(b_x - e_x) <= 1 && std::abs(b_y - e_y) <= 1 &&
        !(std::abs(b_x - e_x) == 0 && std::abs(b_y - e_y) == 0) &&
        ChessBoard::getData(e_cell)->getColor() != color)
    {
        return true;
    }
    
    //check castl for king
    if (checkCastl(b_cell, e_cell, color))
        return true;

    return false;
};


bool King::checkCastl(const std::pair<char, char>& b_cell,
                        const std::pair<char, char>& e_cell, const Color& color)
{
    auto white_king_cell = std::make_pair('e', '1');
    auto black_king_cell = std::make_pair('e', '8');
    
    //check left castling for white
    if (color == Color::WHITE && white_king_cell == b_cell && !getCountMoves())
    {
        auto left_castl_king = std::make_pair('c', '1');
        auto left_rook = std::make_pair('a', '1');
        auto left_rook_end = std::make_pair('d', '1');
        
        auto right_castl_king = std::make_pair('g', '1');
        auto right_rook = std::make_pair('h', '1');
        auto right_rook_end = std::make_pair('f', '1');
        
        if (left_castl_king == e_cell && ChessBoard::is_clear_horizontal(b_cell, left_rook) && ChessBoard::getData(left_rook)->getPieceType() == PieceType::Rook &&
            ChessBoard::getData(left_rook)->getColor() == Color::WHITE &&
            ChessBoard::getData(left_rook)->getCountMoves() == 0)
        {
            auto val = ChessBoard::getData(left_rook);
            
            auto piece = ChessBoard::getData(left_rook);
            piece->setCountMoves();
            ChessBoard::setData(left_rook_end, piece);
            ChessBoard::setData(left_rook, std::make_shared<EmptyPiece>(Color::None,PieceType::None,
                                                    std::make_pair('0', '0')));
            piece->setPos(e_cell);
            return true;
        }//check right castling for white
        else if(right_castl_king == e_cell && ChessBoard::is_clear_horizontal(b_cell, right_rook) && ChessBoard::getData(right_rook)->getPieceType() == PieceType::Rook && ChessBoard::getData(right_rook)->getColor() == Color::WHITE &&
                         ChessBoard::getData(right_rook)->getCountMoves() == 0)
        {
            auto val = ChessBoard::getData(right_rook);//_board_data[b_cell];
            
            auto piece = ChessBoard::getData(right_rook);
            piece->setCountMoves();
            ChessBoard::setData(right_rook_end, piece);
            ChessBoard::setData(right_rook, std::make_shared<EmptyPiece>(Color::None,PieceType::None,
                                                    std::make_pair('0', '0')));
            piece->setPos(e_cell);
            return true;
        }
        return false;
    }//black castl left side
    else if (black_king_cell == b_cell && !getCountMoves())
    {
        auto left_castl_king = std::make_pair('c', '8');
        auto left_rook = std::make_pair('a', '8');
        auto left_rook_end = std::make_pair('d', '8');
        
        auto right_castl_king = std::make_pair('g', '8');
        auto right_rook = std::make_pair('h', '8');
        auto right_rook_end = std::make_pair('f', '8');
        
        if (left_castl_king == e_cell && ChessBoard::is_clear_horizontal(b_cell, left_rook) && ChessBoard::getData(left_rook)->getPieceType() ==
            PieceType::Rook && ChessBoard::getData(left_rook)->getColor() == Color::BLACK && ChessBoard::getData(left_rook)->getCountMoves() == 0)
        {
            auto val = ChessBoard::getData(left_rook);
            
            auto piece = ChessBoard::getData(left_rook);
            piece->setCountMoves();
            ChessBoard::setData(left_rook_end, piece);
            ChessBoard::setData(left_rook, std::make_shared<EmptyPiece>(Color::None,PieceType::None,
                                                    std::make_pair('0', '0')));
            piece->setPos(e_cell);
            return true;
        }//right castling for right
        else if(right_castl_king == e_cell && ChessBoard::is_clear_horizontal(b_cell, right_rook) && ChessBoard::getData(right_rook)->getPieceType() == PieceType::Rook && ChessBoard::getData(right_rook)->getColor() == Color::BLACK &&
                         ChessBoard::getData(right_rook)->getCountMoves() == 0)
        {
            auto val = ChessBoard::getData(right_rook);//_board_data[b_cell];
            
            auto piece = ChessBoard::getData(right_rook);
            piece->setCountMoves();
            ChessBoard::setData(right_rook_end, piece);
            ChessBoard::setData(right_rook, std::make_shared<EmptyPiece>
                      (Color::None,PieceType::None, std::make_pair('0', '0')));
            piece->setPos(e_cell);
            return true;
        }
        return false;
    }
    return false;
}


void King::computeAttackedCells()
{
    std::vector<std::pair<int, int>> king_move {{0, 1}, {1, 1}, {1, 0}, {1, -1},
                                          {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}};

    auto b_cell = getPos();
    std::set<Cell> tmp_set;
    
    for (const auto& k_m : king_move)
    {
        char x = b_cell.first - k_m.first;
        char y = b_cell.second - k_m.second;
        auto attack_cell = std::make_pair(x, y);
        
        tmp_set.insert(attack_cell);
    }
    addAttacksSet(tmp_set, getColor());
}

