#include "headers/figure.hpp"
#include "chessboard.hpp"


Piece::Piece(const Color color, const PieceType& piece_type, const Cell& key)
        : _color(color), _piece_type(piece_type), _x(key.first), _y(key.second), _count_moves(0){};


Color Piece::getColor() const
{
    return _color;
}


PieceType Piece::getPieceType() const
{
    return _piece_type;
}


Cell& Piece::getPos()
{
    return _pos;
}


void Piece::setPos(const Cell& p)
{
    _x = p.first;
    _y = p.second;
    _pos = p;
}


bool Piece::is_vert(const Cell& b_cell, const Cell& e_cell)
{
    char b_x = b_cell.first;
    char b_y = b_cell.second;
    
    char e_x = e_cell.first;
    char e_y = e_cell.second;
 
    if(b_x != e_x || b_y == e_y)
        return false;
    
    return true;
}


bool Piece::is_horiz(const Cell& b_cell, const Cell& e_cell)
{
    char b_x = b_cell.first;
    char b_y = b_cell.second;
    
    char e_x = e_cell.first;
    char e_y = e_cell.second;

    if(b_x == e_x || b_y != e_y)
        return false;

    return true;
}


bool Piece::is_diag(const Cell& b_cell, const Cell& e_cell)
{
    char b_x = b_cell.first;
    char b_y = b_cell.second;
    
    char e_x = e_cell.first;
    char e_y = e_cell.second;

    if(b_x == e_x || b_y == e_y || std::abs(b_x - e_x) != std::abs(b_y - e_y))
        return false;

    return true;
}

void Piece::setCountMoves()
{
    _count_moves++;
}

int Piece::getCountMoves()
{
    return _count_moves;
}


void Piece::addAttacksSet(const std::set<std::pair<char, char>>& raw_attack_set,
                          const Color& color)
{
    for (const auto& p : raw_attack_set)
    {
        if(p.first >= 'a' && p.first <= 'h' && p.second >= '1' && p.second <= '8' &&
           ChessBoard::getData(p)->getColor() != color)
        {
            possible_attack_set.insert(p);
            if (ChessBoard::getData(p)->getPieceType() == PieceType::King)
            {
                std::cout << "Chess!!!" << std::endl;
            }
        }
    }
}

std::set<std::pair<char, char>> Piece::getAttackSet()
{
    return possible_attack_set;
}

void Piece::eraseAttackSet()
{
    possible_attack_set.clear();
}
