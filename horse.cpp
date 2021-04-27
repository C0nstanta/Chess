#include "headers/horse.hpp"
#include "headers/chessboard.hpp"


Horse::Horse(const Color color, const PieceType piece_type, const  Cell& key)
            : Piece(color, piece_type, key){};


bool Horse::can_move(const Cell& e_cell)
{
    auto b_cell = getPos();

    
    //movies
    //std::pair(2,1) (1,2) (2,-1) (-2,-1)(-1,2)(1,-2)(-2, 1)(-1,-2)
    //ходит всегда 2х1 или 1х2
    if (((std::abs(b_cell.first - e_cell.first) == 2 && std::abs(b_cell.second - e_cell.second) == 1)
        || (std::abs(b_cell.first - e_cell.first) == 1 && std::abs(b_cell.second - e_cell.second) == 2))
        && ChessBoard::getData(e_cell)->getColor() != getColor())
        return true;
    

    return false;
};


void Horse::computeAttackedCells()
{

    std::vector<std::pair<int, int>> horse_move {{2, 1}, {1, 2}, {2, -1}, {-2, -1},
                                                {-1, 2}, {1, -2}, {-2, 1}, {-1, -2}};

    auto b_cell = getPos();
    std::set<Cell> tmp_set;
    
    for (const auto& h_m : horse_move)
    {
        char x = b_cell.first - h_m.first;
        char y = b_cell.second - h_m.second;
        auto attack_cell = std::make_pair(x, y);
        
        tmp_set.insert(attack_cell);
    }

    addAttacksSet(tmp_set, getColor());
}
