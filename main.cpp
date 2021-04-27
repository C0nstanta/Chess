#include "headers/player.hpp"
#include "tests/test_pieces.hpp"
#include "tests/UnitTestFramework.hpp"

#include <iostream>
#include <string>
#include <sstream>
#include <exception>


void TestAll()
{
    TestRunner tr;
    tr.RunTest(testPawn, "PawnTest1");
    tr.RunTest(testRook, "RookTest1");
    tr.RunTest(testHorse, "HorseTest1");
    tr.RunTest(testQueen, "QueenTest1");
    tr.RunTest(testBishop, "BishopTest");
    tr.RunTest(testKing, "KingTest");
    tr.RunTest(testKingCastlingWhite, "testKingCastlingWhite");
    tr.RunTest(testKingCastlingBlack, "testKingCastlingBlack");
    tr.RunTest(testPawnAttackSet, "testPawnAttackSet");
    tr.RunTest(testPawnToQueen,  "testPawnToQueen");
    std::cout << "\n" << std::endl;
}


 
int main(int argc, const char * argv[])
{
//Раскомментировать для прогонки через тесты
//    TestAll();

    bool turn_white = true;
    
    Player player_white("p1", Color::WHITE, true);
    Player player_black("p2", Color::BLACK, false);
    

    
    player_white.headPrint();
    std::cout << "white moves first: " << std::endl;
    
    player_black.printBoard();

    
    for (std::string line; getline(std::cin, line);)
    {
        std::istringstream is(line);
                
        if (turn_white)
        {
            
            auto begin_move = player_white.ParseMove(is);
            auto end_move = player_white.ParseMove(is);
            auto bad_answer = std::make_pair('0', '0');
            
            if ((begin_move != bad_answer || end_move != bad_answer) &&
                    player_white.makeMove(begin_move, end_move,
                                      player_white.getColor()))
            {
                player_white.printBoard();
                
                std::cout << "Now is Black Turn: " << std::endl;
                turn_white = false;
            }
            else
            {
                std::cerr << "White Player: " << "try again." << std::endl;
            }
        }
        else if (!turn_white)
        {
            auto begin_move = player_white.ParseMove(is);
            auto end_move = player_white.ParseMove(is);
            auto bad_answer = std::make_pair('0', '0');
            
            if ((begin_move != bad_answer || end_move != bad_answer) &&
                player_white.makeMove(begin_move, end_move,
                                      player_black.getColor()))
            {
                player_white.printBoard();
                std::cout << "Now is White Turn: " << std::endl;
                turn_white = true;
            }
            else
            {
                std::cerr << "Black player: " << "try again." << std::endl;
            }
        }
        
    }
    return 0;
}
