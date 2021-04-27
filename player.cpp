#include "headers/player.hpp"
#include "chessboard.hpp"



Player::Player(const std::string& name, const Color& color, bool init_board=false)
        : _name(name), _color(color)
{
    if (init_board)
    {
        board.initBoard();
    }
};

std::string Player::getName()const
{
    return _name;
}

Color Player::getColor() const
{
    return _color;
}



bool Player::makeMove(const Cell& b_cell, const Cell& e_cell,const Color & color)
{
    return board.movePiece(b_cell, e_cell, color);
}

void Player::printBoard()
{
    board.printBoard();
}

void Player::briefHelp()
{
    std::cout << "The Pawn  (white/black): P(w/b)" << std::endl;
    std::cout << "The Bishop(white/black): B(w/b)" << std::endl;
    std::cout << "The Horse (white/black): H(w/b)" << std::endl;
    std::cout << "The Rook  (white/black): R(w/b)" << std::endl;
    std::cout << "The Queen (white/black): Q(w/b)" << std::endl;
    std::cout << "The King  (white/black): K(w/b)\n\n" << std::endl;
    
    std::cout << "Chess moves" << std::endl;
    std::cout << "King can move: one square horizontally, vertically, or "
                                "diagonally. Can make castling." << std::endl;
    std::cout << "Queen can move any number of vacant squares diagonally, "
                                    "horizontally, or vertically." << std::endl;
    std::cout << "Rook can move any number of vacant squares vertically or "
                                                  "horizontally." << std::endl;
    std::cout << "Bishop can move any number of vacant squares in any diagonal"
                                                     "direction." << std::endl;
    std::cout << "Knight/Horse can move as an \“L\” or \“7\″ 2x1 or 1x2 cell."
                                                                  << std::endl;
    std::cout << "Pawns ... everything is complicated here\n\n" << std::endl;
    printBoard();
    
}


void Player::headPrint()
{
    std::cout << "Press 1: Print Board\n";
    std::cout << "Press 2: Get Help\n";
//    std::cout << "Press 3: Clear console\n";
    std::cout << "Press 3: Quit\n\n";
    
    
    std::cout << "write your move separating coordinates with a space"
                                                                  << std::endl;
    std::cout << "example: e2 e4" << std::endl;
}


void Player::clrScr()
{
    
    system("cls | clear");
    headPrint();
}

void Player::quit()
{
    std::exit(1);
}


std::pair<char, char> Player::ParseMove(std::istream& is)
{

    bool ok = true;
    char x = 'a';
    int y = 0;
    ok = ok && (is >> x);
    ok = ok && (is >> y);
    if (ok && x >= 'a' && x <= 'h' && y >= 1 && y <= 8)
    {
        char _y = y + '0';
        return std::make_pair(x, _y);
    }
        
    if (!y)
    switch (x)
    {
        case '1':
        {
            printBoard();
            break;
        }
        case '2':
        {
            briefHelp();
            break;
        }
        case '3':
        {
//            clrScr();
            std::cout << "Thank you for your game. Bye Bye.\n" << std::endl;
            quit();
  
            break;
        }
        case '4':
        {
            std::cout << "Thank you for your game. Bye Bye.\n" << std::endl;
            quit();
            break;
        }
        default:
            break;
    }
    
    return std::make_pair('0', '0');
}
