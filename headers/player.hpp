#pragma once
#include "chessboard.hpp"


class Player
{
public:
    Player(const std::string&, const Color&, bool);
    
    ChessBoard board;
    
    std::string getName()const;
    
    Color getColor() const;
    
    bool makeMove(const Cell&, const Cell&,const Color &);
    
    
    void printBoard();
    
    void headPrint();
    
    void briefHelp();
    
    void clrScr();
    
    void quit();
    
    std::pair<char, char> ParseMove(std::istream& is);

private:
    const std::string _name;
    const Color _color;
    
};

