#pragma once
#include "figure.hpp"

#include <stdio.h>
#import <iostream>
#import <sstream>
#import <map>
#import <vector>
#import <string>
#import <utility>
#import <memory>

using Cell = std::pair<char, char>;

class ChessBoard
{
public:

    void initBoard();
    
    static bool is_clear_horizontal(const Cell&, const Cell&);
    static bool is_clear_vertical(const Cell&, const Cell&);
    static bool is_clear_diagonal(const Cell&, const Cell&);
    
    bool movePiece(const Cell&, const Cell&, const Color&);
    
    void printBoard() const;
    
    static void setData(const Cell& p, const std::shared_ptr<Piece> piece);
    static std::shared_ptr<Piece> getData(const Cell& p);

    static std::set<Cell> doVertAttackSet(const Cell&, const PieceType&,
                                           const Color&);
    static std::set<Cell> doHorAttackSet(const Cell&, const PieceType&,
                                           const Color&);
    
    static std::set<Cell> doDiagAttackSet(const Cell&, const PieceType&,
                                         const Color&);
    
    bool pawnToQueen(const Cell&, const Cell&, const Color&);
    bool isKingAttacked(const Cell&, const Cell&, const Cell&, const Color&);
    Cell updAttackField(const Color&);
    

private:
    static std::map<Cell, std::shared_ptr<Piece>> _board_data;
    
};

