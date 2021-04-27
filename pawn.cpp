#include "headers/pawn.hpp"
#include "headers/chessboard.hpp"
#include "headers/figure.hpp"
#include "headers/queen.hpp"


bool Pawn::can_move(const Cell& e_cell)
{
    int max_step_length = !getCountMoves() ? 2: 1;
    
    auto b_cell = getPos();
    char b_x = b_cell.first;
    char b_y = b_cell.second;
    
    char e_x = e_cell.first;
    char e_y = e_cell.second;
    
    max_step_length = max_step_length >= std::abs(e_y - b_y)? std::abs(e_y - b_y) : 0;
    
    bool is_white = (getColor() == Color::WHITE);
    bool vert = ChessBoard::is_clear_vertical(b_cell, e_cell);//свободна ли вертикаль


    bool is_vert = Piece::is_vert(b_cell, e_cell);//вертикаль ли это
    bool is_free_cell = ChessBoard::getData(e_cell)->getPieceType() == PieceType::None;
    
    if (is_vert && is_free_cell && max_step_length && vert)//проверяем движение по вертикали
    {

        if((is_white && e_y < b_y) || (!is_white && e_y > b_y))
        {
            return false;
        }

        setCountMoves();
        return true;
    }
    
    //если нужно бить фигуру
    if (std::abs(b_x - e_x) == std::abs(b_y - e_y) && std::abs(b_y - e_y) == 1)
    {
        if (is_white && e_y > b_y && ChessBoard::getData(e_cell)->getColor() == Color::BLACK)
        {
            setCountMoves();
            return true;
        }
        else if(e_y < b_y && ChessBoard::getData(e_cell)->getColor() == Color::WHITE)
        {
            setCountMoves();
            return true;
        }
    }
    
    return false;
};

 //запись всех клеток, которые атакует пешка в наш сэт.
void Pawn::computeAttackedCells()
{
    auto b_cell = getPos();
    if (getColor() == Color::WHITE)
    {
        char left_x = b_cell.first - 1;
        char left_y = b_cell.second + 1;
        auto left_cell = std::make_pair(left_x, left_y);
        
        char right_x = b_cell.first + 1;
        char right_y = b_cell.second + 1;
        auto right_cell = std::make_pair(right_x, right_y);

        std::set<Cell> tmp_set;
        tmp_set.insert(left_cell);
        tmp_set.insert(right_cell);
        
        addAttacksSet(tmp_set, Color::WHITE);
    }
    else
    {
        char left_x = b_cell.first - 1;
        char left_y = b_cell.second - 1;
        auto left_cell = std::make_pair(left_x, left_y);
        
        char right_x = b_cell.first + 1;
        char right_y = b_cell.second - 1;
        auto right_cell = std::make_pair(right_x, right_y);

        std::set<Cell> tmp_set;
        tmp_set.insert(left_cell);
        tmp_set.insert(right_cell);
        
        addAttacksSet(tmp_set, Color::BLACK);
    }
}
