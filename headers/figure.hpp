#pragma once


#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <set>

using Cell = std::pair<char, char>;

enum class Color
{
    None = 0,
    WHITE,
    BLACK
};

enum class PieceType
{
    None = 0,
    Pawn,
    Rook,
    Horse,
    Bishop,
    Queen,
    King
};

class Piece
{
public:
    Piece(const Color , const PieceType&  , const Cell& );
    
    virtual bool can_move(const std::pair<char, char>&) = 0;
    
    //В этом методе будем записывать все возможные удары фигур.
    virtual void computeAttackedCells() = 0;
        
    Color getColor() const;
    
    PieceType getPieceType() const;

    Cell& getPos();
    void setPos(const Cell& p);
    
    //считаем количество ходов фигуры(надо для пешки и для рокировки)
    void setCountMoves();
    int getCountMoves();
    
    //проверка, есть ли в ходе диагональ-вертикаль-горизонталь
    bool is_vert(const Cell&, const Cell&);
    bool is_horiz(const Cell&, const Cell&);
    bool is_diag(const Cell&, const Cell&);
    
    void addAttacksSet(const std::set<Cell>&, const Color&);
    
    std::set<Cell> getAttackSet();
    
    void eraseAttackSet();
    
private:
    const Color _color;
    const PieceType _piece_type;
    char _x;
    char _y;
    int _count_moves;
    
    Cell _pos;
    std::set<Cell> possible_attack_set;
};


