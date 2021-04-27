#include "test_pieces.hpp"
#include "UnitTestFramework.hpp"
#include "../headers/figure.hpp"
#include "../headers/player.hpp"
#include "../headers/chessboard.hpp"

#include <utility>
#include <iostream>
#include <sstream>
#include <utility>
#include <algorithm>

using namespace std;

using Cell = std::pair<char, char>;

void testPawn()
{
    //Check pawn position
    {

        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto pair = std::make_pair('a', '2');
        auto pair2 = std::make_pair('b', '2');
        auto pair3 = std::make_pair('e', '2');
        auto pair4 = std::make_pair('g', '4');
        auto pair5 = std::make_pair('a', '7');
        auto pair6 = std::make_pair('f', '7');
        auto pair7 = std::make_pair('l', '7');

        Assert(player_white.board.getData(pair)->getPieceType() ==
                                PieceType::Pawn,"initialization check - Pawn");
        Assert(player_white.board.getData(pair2)->getPieceType() ==
                                PieceType::Pawn,"initialization check - Pawn2");
        Assert(player_white.board.getData(pair3)->getPieceType() ==
                                PieceType::Pawn,"initialization check - Pawn3");
        Assert(player_white.board.getData(pair4)->getPieceType() !=
                                PieceType::Pawn,"initialization check - Pawn4");
        Assert(player_white.board.getData(pair5)->getPieceType() ==
                                PieceType::Pawn,"initialization check - Pawn5");
        Assert(player_white.board.getData(pair6)->getPieceType() ==
                                PieceType::Pawn,"initialization check - Pawn6");
        Assert(player_white.board.getData(pair7)->getPieceType() ==
                                PieceType::None,"initialization check - Pawn7");

    }
    
    //Check pawn movement
    {
        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto color_white = Color::WHITE;
        auto color_black = Color::BLACK;
        
        auto begin_pair = std::make_pair('a', '2');
        auto end_pair = std::make_pair('a', '4');
        
        auto begin_pair2 = std::make_pair('b', '2');
        auto end_pair2 = std::make_pair('b', '4');
        
        auto begin_pair3 = std::make_pair('e', '2');
        auto end_pair3 = std::make_pair('e', '1');

        auto begin_pair4 = std::make_pair('g', '2');
        auto end_pair4 = std::make_pair('h', '3');
        
        auto begin_pair5 = std::make_pair('c', '7');
        auto end_pair5 = std::make_pair('c', '6');
        
        auto begin_pair6 = std::make_pair('f', '7');
        auto end_pair6 = std::make_pair('f', '4');
        
        auto begin_pair7 = std::make_pair('d', '7');
        auto end_pair7 = std::make_pair('d', '5');

        player_white.makeMove(begin_pair, end_pair, color_white);
        Assert(player_white.board.getData(end_pair)->getPieceType() ==
                                        PieceType::Pawn  ,"move check - Pawn");
        
        player_black.makeMove(begin_pair2, end_pair2, color_black);
        Assert(player_black.board.getData(end_pair2)->getPieceType() ==
                                        PieceType::None, "move check - Pawn2");//black color - white piece
        
        AssertEqual(player_white.makeMove(begin_pair3, end_pair3,
                                    color_white), false, "move check - Pawn3");
        AssertEqual(player_white.makeMove(begin_pair4, end_pair4,
                                    color_white), false, "move check - Pawn4");
        
        
        player_black.makeMove(begin_pair5, end_pair5, color_black);
        Assert(player_black.board.getData(end_pair5)->getPieceType() ==
                                        PieceType::Pawn, "move check - Pawn5");

        player_black.makeMove(begin_pair6, end_pair6, color_black);
        Assert(player_black.board.getData(end_pair6)->getPieceType() ==
                                        PieceType::None, "move check - Pawn6");
        
        player_black.makeMove(begin_pair7, end_pair7, color_black);
        Assert(player_black.board.getData(end_pair7)->getPieceType() ==
                                        PieceType::Pawn, "move check - Pawn7");
    }
}

void testPawnToQueen()
{
    Player player_white("p1", Color::WHITE, true);
    Player player_black("p2", Color::BLACK, false);
    auto color_white = Color::WHITE;
    auto color_black = Color::BLACK;
    
    auto begin_pair = std::make_pair('a', '2');//white pawn move
    auto end_pair = std::make_pair('a', '4');
    AssertEqual(player_white.makeMove(begin_pair, end_pair,
                                            color_white), true, "pawn_queen");

    auto begin_pair1 = std::make_pair('f', '7');//black pawn move
    auto end_pair1 = std::make_pair('f', '5');
    AssertEqual(player_white.makeMove(begin_pair1, end_pair1,
                                            color_black), true, "pawn_queen1");
    
    auto begin_pair2 = std::make_pair('a', '4');//white pawn move
    auto end_pair2 = std::make_pair('a', '5');
    AssertEqual(player_white.makeMove(begin_pair2, end_pair2,
                                            color_white), true, "pawn_queen3");
    
    auto begin_pair3 = std::make_pair('f', '5');//black pawn move
    auto end_pair3 = std::make_pair('f', '4');
    AssertEqual(player_white.makeMove(begin_pair3, end_pair3,
                                            color_black), true, "pawn_queen4");

    auto begin_pair4 = std::make_pair('a', '5');//white pawn move
    auto end_pair4 = std::make_pair('a', '6');
    AssertEqual(player_white.makeMove(begin_pair4, end_pair4,
                                            color_white), true, "pawn_queen5");

    auto begin_pair5 = std::make_pair('f', '4');//black pawn move
    auto end_pair5 = std::make_pair('f', '3');
    AssertEqual(player_white.makeMove(begin_pair5, end_pair5,
                                            color_black), true, "pawn_queen6");

    auto begin_pair6 = std::make_pair('a', '6');//white pawn attack black pawn
    auto end_pair6 = std::make_pair('b', '7');
    AssertEqual(player_white.makeMove(begin_pair6, end_pair6,
                                            color_white), true, "pawn_queen7");

    auto begin_pair7 = std::make_pair('f', '3');//black pawn attack white pawn
    auto end_pair7 = std::make_pair('g', '2');
    AssertEqual(player_white.makeMove(begin_pair7, end_pair7,
                                            color_black), true, "pawn_queen8");
    
    auto begin_pair8 = std::make_pair('b', '7');//white pawn attack black bish QUEEN!
    auto end_pair8 = std::make_pair('c', '8');
    AssertEqual(player_white.makeMove(begin_pair8, end_pair8,
                                            color_white), true, "pawn_queen9");
    Assert(player_white.board.getData(end_pair8)->getPieceType() ==
                                PieceType::Queen,"pawn_queen9 check - Queen");

    auto begin_pair9 = std::make_pair('g', '2');//black pawn attack white rook QUEEN!
    auto end_pair9 = std::make_pair('h', '1');
    AssertEqual(player_white.makeMove(begin_pair9, end_pair9,
                                            color_black), true, "pawn_queen10");
    Assert(player_white.board.getData(end_pair9)->getPieceType() ==
                                PieceType::Queen,"pawn_queen10 check - Queen");
    
    auto begin_pair10 = std::make_pair('c', '8');//white QUEEN! move
    auto end_pair10 = std::make_pair('a', '6');
    AssertEqual(player_white.makeMove(begin_pair10, end_pair10, color_white),
                                                        true, "pawn_queen10");
    
    auto begin_pair11 = std::make_pair('h', '1');//black Queen attack white horse
    auto end_pair11 = std::make_pair('g', '1');
    AssertEqual(player_white.makeMove(begin_pair11, end_pair11, color_black),
                                                        true, "pawn_queen11");
    
    auto begin_pair12 = std::make_pair('a', '6');//white QUEEN! move
    auto end_pair12 = std::make_pair('h', '6');
    AssertEqual(player_white.makeMove(begin_pair12, end_pair12, color_white),
                                                        true, "pawn_queen12");
 
    auto begin_pair13 = std::make_pair('g', '1');//black Queen attack white horse
    auto end_pair13 = std::make_pair('g', '6');
    AssertEqual(player_white.makeMove(begin_pair13, end_pair13, color_black),
                                                        true, "pawn_queen11");
}


void testRook()
{
    //Check pawn position
    {

        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto pair = std::make_pair('a', '1');
        auto pair2 = std::make_pair('c', '2');
        auto pair3 = std::make_pair('e', '2');
        auto pair4 = std::make_pair('h', '8');
        auto pair5 = std::make_pair('a', '8');

        Assert(player_white.board.getData(pair)->getPieceType() ==
                                PieceType::Rook,"initialization check - Rook");
        Assert(player_white.board.getData(pair2)->getPieceType() !=
                                PieceType::Rook,"initialization check - Rook2");
        Assert(player_white.board.getData(pair3)->getPieceType() ==
                                PieceType::Pawn,"initialization check - Rook3");
        Assert(player_white.board.getData(pair4)->getPieceType() ==
                                PieceType::Rook,"initialization check - Rook4");
        Assert(player_white.board.getData(pair5)->getPieceType() ==
                                PieceType::Rook,"initialization check - Rook5");
    }
        
    //Check pawn movement
    {
        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto color_white = Color::WHITE;
        auto color_black = Color::BLACK;
        
        auto begin_pair = std::make_pair('a', '2');//First need to move pawn
        auto end_pair = std::make_pair('a', '4');
        
        auto begin_pair2 = std::make_pair('a', '1'); //wrong move
        auto end_pair2 = std::make_pair('b', '4');
        
        auto begin_pair3 = std::make_pair('a', '1');
        auto end_pair3 = std::make_pair('a', '3');

        auto begin_pair4 = std::make_pair('a', '3');
        auto end_pair4 = std::make_pair('a', '7');

        auto begin_pair5 = std::make_pair('a', '7');
        auto end_pair5 = std::make_pair('a', '5');

        auto begin_pair6 = std::make_pair('a', '8');
        auto end_pair6 = std::make_pair('a', '6');

        auto begin_pair7 = std::make_pair('a', '6');
        auto end_pair7 = std::make_pair('h', '6');

        player_white.makeMove(begin_pair, end_pair, color_white);
        Assert(player_white.board.getData(end_pair)->getPieceType() ==
                                   PieceType::Pawn  ,"move check - Pawn first");
        
        player_black.makeMove(begin_pair2, end_pair2, color_black);
        Assert(player_black.board.getData(end_pair2)->getPieceType() ==
                                         PieceType::None, "move check - Rook2");
        
        AssertEqual(player_white.makeMove(begin_pair3, end_pair3, color_white),
                                                    true, "move check - Rook3");
        AssertEqual(player_white.makeMove(begin_pair4, end_pair4, color_white),
                                                  false, "move check - Rook4");

        player_black.makeMove(begin_pair5, end_pair5, color_black);
        Assert(player_black.board.getData(end_pair5)->getPieceType() ==
                                    PieceType::Pawn, "move check - Pawn again");

        player_black.makeMove(begin_pair6, end_pair6, color_black);
        Assert(player_black.board.getData(end_pair6)->getPieceType() ==
                                        PieceType::Rook, "move check - Rook5");

        player_black.makeMove(begin_pair7, end_pair7, color_black);
        Assert(player_black.board.getData(end_pair7)->getPieceType() ==
                                        PieceType::Rook, "move check - Rook6");
    }
}

void testHorse()
{
    //Check pawn position
    {

        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto pair = std::make_pair('b', '1');
        auto pair2 = std::make_pair('c', '1');
        auto pair3 = std::make_pair('g', '1');
        auto pair4 = std::make_pair('b', '8');
        auto pair5 = std::make_pair('g', '8');

        Assert(player_white.board.getData(pair)->getPieceType() ==
                              PieceType::Horse,"initialization check - Horse");
        Assert(player_white.board.getData(pair2)->getPieceType() !=
                             PieceType::Horse,"initialization check - Horse2");
        Assert(player_white.board.getData(pair3)->getPieceType() ==
                             PieceType::Horse,"initialization check - Horse3");
        Assert(player_white.board.getData(pair4)->getPieceType() ==
                              PieceType::Horse,"initialization check - Horse4");
        Assert(player_white.board.getData(pair5)->getPieceType() ==
                             PieceType::Horse,"initialization check - Horse5");
    }
        
    //Check pawn movement
    {
        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto color_white = Color::WHITE;
        auto color_black = Color::BLACK;
        
        auto begin_pair = std::make_pair('b', '1');
        auto end_pair = std::make_pair('a', '3');
        
        auto begin_pair2 = std::make_pair('a', '0'); //wrong move
        auto end_pair2 = std::make_pair('a', '4');
        
        auto begin_pair3 = std::make_pair('a', '3');//our location
        auto end_pair3 = std::make_pair('c', '2');

        auto begin_pair4 = std::make_pair('a', '3');
        auto end_pair4 = std::make_pair('b', '5');

        auto begin_pair5 = std::make_pair('g', '8');
        auto end_pair5 = std::make_pair('f', '6');

        auto begin_pair6 = std::make_pair('b', '8');
        auto end_pair6 = std::make_pair('a', '6');

        auto begin_pair7 = std::make_pair('a', '6');
        auto end_pair7 = std::make_pair('c', '5');

        player_white.makeMove(begin_pair, end_pair, color_white);
        Assert(player_white.board.getData(end_pair)->getPieceType() ==
                                        PieceType::Horse, "move check - Horse");
        
        player_black.makeMove(begin_pair2, end_pair2, color_black);
        Assert(player_black.board.getData(end_pair2)->getPieceType() ==
                                        PieceType::None, "move check - Horse2");
        
        AssertEqual(player_white.makeMove(begin_pair3, end_pair3, color_white),
                                                 false, "move check - Horse3");//our location
        AssertEqual(player_white.makeMove(begin_pair4, end_pair4, color_white),
                                                 true, "move check - Horse4");

        player_black.makeMove(begin_pair5, end_pair5, color_black);
        Assert(player_black.board.getData(end_pair5)->getPieceType() ==
                                      PieceType::Horse, "move check - Horse5");

        player_black.makeMove(begin_pair6, end_pair6, color_black);
        Assert(player_black.board.getData(end_pair6)->getPieceType() ==
                                       PieceType::Horse, "move check - Horse6");

        player_black.makeMove(begin_pair7, end_pair7, color_black);
        Assert(player_black.board.getData(end_pair7)->getPieceType() ==
                                       PieceType::Horse, "move check - Horse7");
    }
}


void testQueen()
{
    //Check Queen position
    {

        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto pair = std::make_pair('d', '1');
        auto pair2 = std::make_pair('d', '8');

        Assert(player_white.board.getData(pair)->getPieceType() ==
                              PieceType::Queen,"initialization check - Queen");
        Assert(player_white.board.getData(pair2)->getPieceType() ==
                              PieceType::Queen,"initialization check - Queen2");
    }
        
    //Check queen movement
    {
        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto color_white = Color::WHITE;
        auto color_black = Color::BLACK;
        
        auto begin_pair = std::make_pair('d', '1');
        auto end_pair = std::make_pair('d', '3');
        player_white.makeMove(begin_pair, end_pair, color_white);
        Assert(player_white.board.getData(end_pair)->getPieceType() ==
                                        PieceType::None, "move check - Queen");
        
        auto begin_pair2 = std::make_pair('d', '2'); //move pawn
        auto end_pair2 = std::make_pair('d', '4');
        player_black.makeMove(begin_pair2, end_pair2, color_white);
        Assert(player_black.board.getData(end_pair2)->getPieceType() ==
                                        PieceType::Pawn, "move check - Queen2");
        
        auto begin_pair3 = std::make_pair('d', '1');
        auto end_pair3 = std::make_pair('d', '3');
        AssertEqual(player_white.makeMove(begin_pair3, end_pair3, color_white),
                                                 true, "move check - Queen3");//our location
        
        auto begin_pair4 = std::make_pair('d', '3');
        auto end_pair4 = std::make_pair('a', '6');
        AssertEqual(player_white.makeMove(begin_pair4, end_pair4, color_white),
                                                 true, "move check - Queen4");

        auto begin_pair5 = std::make_pair('e', '7');
        auto end_pair5 = std::make_pair('e', '5');
        player_black.makeMove(begin_pair5, end_pair5, color_black);
        Assert(player_black.board.getData(end_pair5)->getPieceType() ==
                                        PieceType::Pawn, "move check - Queen5");
        
        auto begin_pair51 = std::make_pair('d', '7');
        auto end_pair51 = std::make_pair('d', '5');
        player_black.makeMove(begin_pair51, end_pair51, color_black);
        Assert(player_black.board.getData(end_pair51)->getPieceType() ==
                                      PieceType::Pawn, "move check - Queen51");
        
        auto begin_pair6 = std::make_pair('d', '8');
        auto end_pair6 = std::make_pair('d', '6');
        player_black.makeMove(begin_pair6, end_pair6, color_black);
        Assert(player_black.board.getData(end_pair6)->getPieceType() ==
                                      PieceType::Queen, "move check - Queen6");
        
        auto begin_pair7 = std::make_pair('d', '6');
        auto end_pair7 = std::make_pair('a', '3');
        player_black.makeMove(begin_pair7, end_pair7, color_black);
        Assert(player_black.board.getData(end_pair7)->getPieceType() ==
                                      PieceType::Queen, "move check - Queen7");
    }
}

void testBishop()
{
    //Check Queen position
    {

        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto pair = std::make_pair('c', '1');
        auto pair2 = std::make_pair('f', '1');
        auto pair3 = std::make_pair('c', '8');
        auto pair4 = std::make_pair('f', '8');

        Assert(player_white.board.getData(pair)->getPieceType() ==
                              PieceType::Bishop,"initialization check - Bish");
        Assert(player_white.board.getData(pair2)->getPieceType() ==
                             PieceType::Bishop,"initialization check - Bish2");
        Assert(player_white.board.getData(pair3)->getPieceType() ==
                             PieceType::Bishop,"initialization check - Bish3");
        Assert(player_white.board.getData(pair4)->getPieceType() ==
                            PieceType::Bishop,"initialization check - Bish4");
    }
    
    //Check bishop movement
    {
        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto color_white = Color::WHITE;
        auto color_black = Color::BLACK;
        
        auto begin_pair = std::make_pair('d', '2');//move pawn first
        auto end_pair = std::make_pair('d', '4');//white
        
        auto begin_pair2 = std::make_pair('c', '1');//white
        auto end_pair2 = std::make_pair('h', '6');
        
        auto begin_pair3 = std::make_pair('e', '7');//move pawn second
        auto end_pair3 = std::make_pair('e', '5');//black

        
        auto begin_pair4 = std::make_pair('h', '6'); // false
        auto end_pair4 = std::make_pair('a', '6');//white

        auto begin_pair5 = std::make_pair('h', '6');//white back
        auto end_pair5 = std::make_pair('c', '1');

        auto begin_pair6 = std::make_pair('a', '3');//attack via 1//false
        auto end_pair6 = std::make_pair('c', '1');

        auto begin_pair7 = std::make_pair('f', '8');//black move bish
        auto end_pair7 = std::make_pair('a', '3');
        
        auto begin_pair8 = std::make_pair('a', '1');//attack rook-bish via 1
        auto end_pair8 = std::make_pair('a', '3');
        
        auto begin_pair9 = std::make_pair('a', '3');//attack bish
        auto end_pair9 = std::make_pair('b', '2');

        player_white.makeMove(begin_pair, end_pair, color_white);
        Assert(player_white.board.getData(end_pair)->getPieceType() ==
                                        PieceType::Pawn, "move check - Bish");
        
        player_black.makeMove(begin_pair2, end_pair2, color_white);
        Assert(player_black.board.getData(end_pair2)->getPieceType() ==
                                     PieceType::Bishop, "move check - Bish2");
        
        AssertEqual(player_white.makeMove(begin_pair3, end_pair3, color_black),
                                                    true, "move check - Bish3");//our location
        AssertEqual(player_white.makeMove(begin_pair4, end_pair4, color_white),
                                                  false, "move check - Bish4");

        player_black.makeMove(begin_pair5, end_pair5, color_white);
        Assert(player_black.board.getData(end_pair5)->getPieceType() ==
                                      PieceType::Bishop, "move check - Bish5");

        player_black.makeMove(begin_pair6, end_pair6, color_black);
        Assert(player_black.board.getData(end_pair6)->getPieceType() ==
                                      PieceType::Bishop, "move check - Bish6");

        player_black.makeMove(begin_pair7, end_pair7, color_black);
        Assert(player_black.board.getData(end_pair7)->getPieceType() ==
                                      PieceType::Bishop, "move check - Bish7");
        
        player_black.makeMove(begin_pair8, end_pair8, color_black);
        Assert(player_black.board.getData(end_pair8)->getPieceType() ==
                                      PieceType::Bishop, "move check - Bish8");

        player_black.makeMove(begin_pair9, end_pair9, color_black);
        Assert(player_black.board.getData(end_pair9)->getPieceType() ==
                                      PieceType::Bishop, "move check - Bish9");
    }
}

void testKing()
{
    //Check King position
    {

        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto pair = std::make_pair('e', '1');
        auto pair2 = std::make_pair('e', '8');
        
        Assert(player_white.board.getData(pair)->getPieceType() ==
                                 PieceType::King,"initialization check - King");
        Assert(player_white.board.getData(pair2)->getPieceType() ==
                                PieceType::King,"initialization check - King2");

    }
    
    //Check king movement
    {
        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto color_white = Color::WHITE;
        auto color_black = Color::BLACK;
        
        auto begin_pair = std::make_pair('e', '2');//move pawn first
        auto end_pair = std::make_pair('e', '4');//white
        
        auto begin_pair2 = std::make_pair('e', '7');//black pawn
        auto end_pair2 = std::make_pair('e', '5');
        
        auto begin_pair3 = std::make_pair('e', '1');//white king
        auto end_pair3 = std::make_pair('d', '2');//move through //false

        
        auto begin_pair4 = std::make_pair('e', '1'); // false
        auto end_pair4 = std::make_pair('e', '3');//white 2 cell

        auto begin_pair5 = std::make_pair('e', '1');//white
        auto end_pair5 = std::make_pair('e', '2');

        auto begin_pair6 = std::make_pair('e', '8');//black move
        auto end_pair6 = std::make_pair('e', '7');

        auto begin_pair7 = std::make_pair('e', '2');//white move
        auto end_pair7 = std::make_pair('d', '3');
        
        auto begin_pair8 = std::make_pair('e', '7');//black back
        auto end_pair8 = std::make_pair('e', '8');
        
        auto begin_pair9 = std::make_pair('d', '3');//king move
        auto end_pair9 = std::make_pair('d', '4');

        player_white.makeMove(begin_pair, end_pair, color_white);
        Assert(player_white.board.getData(end_pair)->getPieceType() ==
                                         PieceType::Pawn, "move check - King");
        
        player_black.makeMove(begin_pair2, end_pair2, color_black);
        Assert(player_black.board.getData(end_pair2)->getPieceType() ==
                                         PieceType::Pawn, "move check - King2");
        
        AssertEqual(player_white.makeMove(begin_pair3, end_pair3, color_white),
                                                  false, "move check - King3");
        AssertEqual(player_white.makeMove(begin_pair4, end_pair4, color_white),
                                                  false, "move check - King4");

        AssertEqual(player_white.makeMove(begin_pair5, end_pair5, color_white),
                                                   true, "move check - King5");
        AssertEqual(player_white.makeMove(begin_pair6, end_pair6, color_black),
                                                    true, "move check - King6");
        AssertEqual(player_white.makeMove(begin_pair7, end_pair7, color_white),
                                                    true, "move check - King7");
        AssertEqual(player_white.makeMove(begin_pair8, end_pair8, color_black),
                                                    true, "move check - King8");


    }
}

void testKingCastlingWhite()
{
    //Check King castl position
    {

        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto pair = std::make_pair('e', '1');
        auto pair2 = std::make_pair('e', '8');
        
        Assert(player_white.board.getData(pair)->getPieceType() ==
                          PieceType::King,"initialization check - King castl");
        Assert(player_white.board.getData(pair2)->getPieceType() ==
                         PieceType::King,"initialization check - King2 castl");

    }
    
    //Check king castl movement white left
    {
        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto color_white = Color::WHITE;
        auto color_black = Color::BLACK;
        
        auto begin_pair = std::make_pair('b', '2');//move pawn first
        auto end_pair = std::make_pair('b', '4');//white

        
        player_white.makeMove(begin_pair, end_pair, color_white);
        Assert(player_white.board.getData(end_pair)->getPieceType() ==
                        PieceType::Pawn, "move check - King castl__right_left");
        
        auto begin_pair2 = std::make_pair('b', '7');//move pawn first
        auto end_pair2 = std::make_pair('b', '5');//black
        
        player_black.makeMove(begin_pair2, end_pair2, color_black);
        Assert(player_black.board.getData(end_pair2)->getPieceType() ==
                       PieceType::Pawn, "move check - King2 castl__right_left");
        
        auto begin_pair3 = std::make_pair('c', '1');//white Bish
        auto end_pair3 = std::make_pair('a', '3');//
        
        AssertEqual(player_white.makeMove(begin_pair3, end_pair3,
                    color_white), true, "move check - King3 castl__right_left");
        
        auto begin_pair4 = std::make_pair('e', '1'); //move pawn
        auto end_pair4 = std::make_pair('e', '3');//white
        AssertEqual(player_white.makeMove(begin_pair4, end_pair4,
                  color_white), false, "move check - King4 castl__right_left");
        
        auto begin_pair5 = std::make_pair('d', '7');//black pawn
        auto end_pair5 = std::make_pair('d', '5');
        AssertEqual(player_white.makeMove(begin_pair5, end_pair5,
                    color_black), true, "move check - King5 castl__right_left");

        auto begin_pair6 = std::make_pair('c', '5');//black move /false/left white pawn
        auto end_pair6 = std::make_pair('c', '4');
        AssertEqual(player_white.makeMove(begin_pair6, end_pair6,
                  color_black), false, "move check - King6 castl__right_left");

        auto begin_pair7 = std::make_pair('b', '8');//black horse move
        auto end_pair7 = std::make_pair('a', '6');
        AssertEqual(player_white.makeMove(begin_pair7, end_pair7,
                    color_black), true, "move check - King7 castl__right_left");

        auto begin_pair71 = std::make_pair('d', '2');//white pawn
        auto end_pair71 = std::make_pair('d', '4');
        AssertEqual(player_white.makeMove(begin_pair71, end_pair71,
                  color_white), true, "move check - King71 castl__right_left");
        
        auto begin_pair8 = std::make_pair('b', '1');//white horse move
        auto end_pair8 = std::make_pair('c', '3');
        AssertEqual(player_white.makeMove(begin_pair8, end_pair8,
                    color_white), true, "move check - King8 castl__right_left");

        auto begin_pair9 = std::make_pair('e', '7');//black pawn move
        auto end_pair9 = std::make_pair('e', '5');
        AssertEqual(player_white.makeMove(begin_pair9, end_pair9,
                    color_black), true, "move check - King9 castl__right_left");
        
        auto begin_pair91 = std::make_pair('d', '1');//white queen move
        auto end_pair91 = std::make_pair('d', '2');
        AssertEqual(player_white.makeMove(begin_pair91, end_pair91,
                   color_white), true, "move check - King91 castl__right_left");


        //left castling for white king check!!!
        auto begin_pair10 = std::make_pair('e', '1');//king castling left!
        auto end_pair10 = std::make_pair('c', '1');
        auto left_rook = std::make_pair('a', '1');//after castling coord None pos
        auto left_rook_end = std::make_pair('d', '1');//white after castling king pos
        auto king_pos_begin = std::make_pair('e', '1');//after castling coord None pos
        auto king_pos_end = std::make_pair('c', '1');//white after castling king pos
        AssertEqual(player_white.makeMove(begin_pair10, end_pair10,
                color_white), true, "move check - King10 castl_0__right_left");
        Assert(player_white.board.getData(left_rook)->getPieceType() ==
                    PieceType::None, "move check - King10 castl_1__right_left");
        Assert(player_white.board.getData(left_rook)->getPieceType() ==
                    PieceType::None, "move check - King10 castl_1__right_left");
        Assert(player_white.board.getData(left_rook_end)->getPieceType() ==
                    PieceType::Rook, "move check - King10 castl_2__right_left");
        Assert(player_white.board.getData(king_pos_begin)->getPieceType() ==
                    PieceType::None, "move check - King10 castl_3__right_left");
        Assert(player_white.board.getData(king_pos_end)->getPieceType() ==
                    PieceType::King, "move check - King10 castl_4__right_left");
    }
    
    //Check king castl movement white right
    {
        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto color_white = Color::WHITE;
        auto color_black = Color::BLACK;
        
        auto begin_pair = std::make_pair('f', '2');//move pawn first
        auto end_pair = std::make_pair('f', '4');//white

        
        player_white.makeMove(begin_pair, end_pair, color_white);
        Assert(player_white.board.getData(end_pair)->getPieceType() ==
                        PieceType::Pawn, "move check - King castl_right_white");
        
        auto begin_pair2 = std::make_pair('f', '7');//move pawn first
        auto end_pair2 = std::make_pair('f', '5');//black
        
        player_black.makeMove(begin_pair2, end_pair2, color_black);
        Assert(player_black.board.getData(end_pair2)->getPieceType() ==
                       PieceType::Pawn, "move check - King2 castl_right_white");
        
        auto begin_pair3 = std::make_pair('g', '2');//white pawn 2
        auto end_pair3 = std::make_pair('g', '4');//white
        
        AssertEqual(player_white.makeMove(begin_pair3, end_pair3,
                    color_white), true, "move check - King3 castl_right_white");
        
        auto begin_pair4 = std::make_pair('g', '7'); //move pawn
        auto end_pair4 = std::make_pair('g', '5');//black
        AssertEqual(player_white.makeMove(begin_pair4, end_pair4,
                    color_black), true, "move check - King4 castl_right_white");
        
        auto begin_pair5 = std::make_pair('h', '2');//black pawn
        auto end_pair5 = std::make_pair('h', '4');
        AssertEqual(player_white.makeMove(begin_pair5, end_pair5, color_white),
                                 true, "move check - King5 castl_right_white");

        auto begin_pair6 = std::make_pair('h', '7');//black move /true/
        auto end_pair6 = std::make_pair('h', '5');
        AssertEqual(player_white.makeMove(begin_pair6, end_pair6,
                    color_black), true, "move check - King6 castl_right_white");

        auto begin_pair7 = std::make_pair('g', '1');//white horse move
        auto end_pair7 = std::make_pair('f', '3');
        AssertEqual(player_white.makeMove(begin_pair7, end_pair7,
                    color_white), true, "move check - King7 castl_right_white");

        auto begin_pair71 = std::make_pair('f', '8');//black bish move
        auto end_pair71 = std::make_pair('h', '6');
        AssertEqual(player_white.makeMove(begin_pair71, end_pair71,
                  color_black), true, "move check - King71 castl_right_white");
        
        auto begin_pair8 = std::make_pair('f', '1');//white bish move
        auto end_pair8 = std::make_pair('h', '3');
        AssertEqual(player_white.makeMove(begin_pair8, end_pair8,
                    color_white), true, "move check - King8 castl_right_white");

        auto begin_pair9 = std::make_pair('h', '5');//black pawn attack white
        auto end_pair9 = std::make_pair('g', '4');
        AssertEqual(player_white.makeMove(begin_pair9, end_pair9,
                    color_black), true, "move check - King9 castl_right_white");
        
        auto begin_pair91 = std::make_pair('f', '3');//white horse attack pawn
        auto end_pair91 = std::make_pair('g', '5');
        AssertEqual(player_white.makeMove(begin_pair91, end_pair91,
                  color_white), true, "move check - King91 castl_right_white");

        auto begin_pair92 = std::make_pair('g', '8');//black horse attack pawn
        auto end_pair92 = std::make_pair('f', '6');
        AssertEqual(player_white.makeMove(begin_pair92, end_pair92,
                  color_black), true, "move check - King92 castl_right_white");

        //left castling for white king check!!!
        auto begin_pair10 = std::make_pair('e', '1');//king castling left!
        auto end_pair10 = std::make_pair('g', '1');
        auto right_rook = std::make_pair('h', '1');//after castling coord None pos
        auto right_rook_end = std::make_pair('f', '1');//white after castling king pos
        auto king_pos_begin = std::make_pair('e', '1');//after castling coord None pos
        auto king_pos_end = std::make_pair('g', '1');//white after castling king pos
        AssertEqual(player_white.makeMove(begin_pair10, right_rook, color_white)
                          , false, "move check - King_false_move _right_white");
        AssertEqual(player_white.makeMove(begin_pair10, end_pair10,
                        color_white), true, "move check - King10 _right_white");
        Assert(player_white.board.getData(right_rook)->getPieceType() ==
                    PieceType::None, "move check - King10 castl_1_right_white");
        Assert(player_white.board.getData(king_pos_begin)->getPieceType() ==
                    PieceType::None, "move check - King10 castl_3_right_white");
        Assert(player_white.board.getData(king_pos_end)->getPieceType() ==
                    PieceType::King, "move check - King10 castl_4_right_white");
        Assert(player_white.board.getData(right_rook_end)->getPieceType() ==
                    PieceType::Rook, "move check - King10 castl_2_right_white");

    }
}

void testKingCastlingBlack()
{
    //Check King castl position
    {

        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto pair = std::make_pair('e', '1');
        auto pair2 = std::make_pair('e', '8');
        
        Assert(player_white.board.getData(pair)->getPieceType() ==
                        PieceType::King,"initialization check - King castl_2");
        Assert(player_white.board.getData(pair2)->getPieceType() ==
                        PieceType::King,"initialization check - King2 castl_2");

    }
    //Check king castl movement black left
    {
        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto color_white = Color::WHITE;
        auto color_black = Color::BLACK;
        
        auto begin_pair = std::make_pair('d', '2');//move pawn first
        auto end_pair = std::make_pair('d', '4');//white

        
        player_white.makeMove(begin_pair, end_pair, color_white);
        Assert(player_white.board.getData(end_pair)->getPieceType() ==
                                             PieceType::Pawn, "castl black_1");
        
        auto begin_pair2 = std::make_pair('d', '7');//move pawn first
        auto end_pair2 = std::make_pair('d', '5');//black
        
        player_black.makeMove(begin_pair2, end_pair2, color_black);
        Assert(player_black.board.getData(end_pair2)->getPieceType() ==
                                            PieceType::Pawn, "castl black_2");
        
        auto begin_pair3 = std::make_pair('c', '1');//white Bish
        auto end_pair3 = std::make_pair('h', '6');//
        
        AssertEqual(player_white.makeMove(begin_pair3, end_pair3,
                                          color_white), true, "castl black_3");
        
        auto begin_pair4 = std::make_pair('b', '7'); //move pawn
        auto end_pair4 = std::make_pair('b', '5');//black
        AssertEqual(player_white.makeMove(begin_pair4, end_pair4,
                                          color_black), true, "castl black_4");
        
        auto begin_pair5 = std::make_pair('b', '1');//black pawn
        auto end_pair5 = std::make_pair('c', '3');
        AssertEqual(player_white.makeMove(begin_pair5, end_pair5,
                                          color_white), true, "castl black_5");

        auto begin_pair6 = std::make_pair('b', '8');//black move horse
        auto end_pair6 = std::make_pair('c', '6');
        AssertEqual(player_white.makeMove(begin_pair6, end_pair6,
                                          color_black), true, "castl black_6");

        auto begin_pair7 = std::make_pair('c', '3');//white horse attack black pawn
        auto end_pair7 = std::make_pair('d', '5');
        AssertEqual(player_white.makeMove(begin_pair7, end_pair7,
                                          color_white), true, "castl black_7");

        auto begin_pair71 = std::make_pair('c', '8');//black bish move
        auto end_pair71 = std::make_pair('h', '3');
        AssertEqual(player_white.makeMove(begin_pair71, end_pair71,
                                          color_black), true, "castl black_8");

        auto begin_pair8 = std::make_pair('c', '6');//black horse move
        auto end_pair8 = std::make_pair('e', '5');
        AssertEqual(player_white.makeMove(begin_pair8, end_pair8,
                                          color_black), true, "castl black_9");

        auto begin_pair9 = std::make_pair('d', '1');//white queen move
        auto end_pair9 = std::make_pair('d', '3');
        AssertEqual(player_white.makeMove(begin_pair9, end_pair9,
                                          color_white), true, "castl black_10");

        auto begin_pair91 = std::make_pair('d', '8');//black bish move
        auto end_pair91 = std::make_pair('d', '6');
        AssertEqual(player_white.makeMove(begin_pair91, end_pair91,
                                          color_black), true, "castl black_11");


        
//        //left castling for white king check!!!
        auto begin_pair10 = std::make_pair('e', '8');//black king castling left!
        auto end_pair10 = std::make_pair('c', '8');
        auto left_rook = std::make_pair('a', '8');//after castling coord None pos
        auto left_rook_end = std::make_pair('d', '8');//white after castling king pos
        auto king_pos_begin = std::make_pair('e', '8');//after castling coord None pos
        auto king_pos_end = std::make_pair('c', '8');//white after castling king pos
        AssertEqual(player_white.makeMove(begin_pair10, end_pair10,
                                          color_black), true, "move check - castle black 12");
        Assert(player_white.board.getData(left_rook)->getPieceType() ==
               PieceType::None, "move check - castle black 13");
        Assert(player_white.board.getData(left_rook)->getPieceType() ==
               PieceType::None, "move check - castle black 14");
        Assert(player_white.board.getData(left_rook_end)->getPieceType() ==
               PieceType::Rook, " - castle black 15");
        Assert(player_white.board.getData(king_pos_begin)->getPieceType() ==
               PieceType::None, " - castle black 16");
        Assert(player_white.board.getData(king_pos_end)->getPieceType() ==
               PieceType::King, "move check - - castle black 17");
    }
    
    //Check king castl movement black right
    {
        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto color_white = Color::WHITE;
        auto color_black = Color::BLACK;
        
        auto begin_pair = std::make_pair('d', '2');//move pawn first
        auto end_pair = std::make_pair('d', '4');//white

        
        player_white.makeMove(begin_pair, end_pair, color_white);
        Assert(player_white.board.getData(end_pair)->getPieceType() ==
               PieceType::Pawn, "castl black_1_right");
        
        auto begin_pair2 = std::make_pair('h', '7');//move pawn
        auto end_pair2 = std::make_pair('h', '6');//black
        
        player_black.makeMove(begin_pair2, end_pair2, color_black);
        Assert(player_black.board.getData(end_pair2)->getPieceType() ==
               PieceType::Pawn, "castl black_2_right");
        
        auto begin_pair3 = std::make_pair('d', '1');//white Queen move
        auto end_pair3 = std::make_pair('d', '3');//
        
        AssertEqual(player_white.makeMove(begin_pair3, end_pair3,
                                          color_white), true, "castl black_3_right");
        
        auto begin_pair4 = std::make_pair('g', '8'); //move horse
        auto end_pair4 = std::make_pair('f', '6');//black
        AssertEqual(player_white.makeMove(begin_pair4, end_pair4,
                                          color_black), true, "castl black_4_right");
        
        auto begin_pair5 = std::make_pair('d', '3');//white queen
        auto end_pair5 = std::make_pair('h', '3');
        AssertEqual(player_white.makeMove(begin_pair5, end_pair5,
                                          color_white), true, "castl black_5_right");

        auto begin_pair6 = std::make_pair('e', '7');//black move pawn
        auto end_pair6 = std::make_pair('e', '5');
        AssertEqual(player_white.makeMove(begin_pair6, end_pair6,
                                          color_black), true, "castl black_6_right");

        auto begin_pair7 = std::make_pair('h', '3');//white queen attack black bish
        auto end_pair7 = std::make_pair('d', '7');//chess here!
        AssertEqual(player_white.makeMove(begin_pair7, end_pair7,
                                          color_white), true, "castl black_7_right");

        auto begin_pair71 = std::make_pair('f', '8');//black bish move
        auto end_pair71 = std::make_pair('a', '3');//Chess!!!Your King under attack! Do smth!Chess!!!You can't move to this cell! You King will be under
        AssertEqual(player_white.makeMove(begin_pair71, end_pair71,
                                          color_black), false, "castl black_8_right");

        auto begin_pair8 = std::make_pair('d', '4');//white pawn move /false
        auto end_pair8 = std::make_pair('d', '6');
        AssertEqual(player_white.makeMove(begin_pair8, end_pair8,
                                          color_white), false, "castl black_9_right");

        auto begin_pair9 = std::make_pair('c', '8');//black bish attack white queen
        auto end_pair9 = std::make_pair('d', '7');
        AssertEqual(player_white.makeMove(begin_pair9, end_pair9,
                                          color_black), true, "castl black_10_right");

        auto begin_pair92 = std::make_pair('f', '8');//black bish move
        auto end_pair92 = std::make_pair('a', '3');
        AssertEqual(player_white.makeMove(begin_pair92, end_pair92,
                                          color_black), true, "castl black_11_right");
        
        auto begin_pair93 = std::make_pair('c', '1');//white bish attack black pawn
        auto end_pair93 = std::make_pair('h', '6');
        AssertEqual(player_white.makeMove(begin_pair93, end_pair93,
                                          color_white), true, "castl black_12_right");
        
//        //left castling for black king check!!!
        auto begin_pair10 = std::make_pair('e', '8');//black king castling left!
        auto end_pair10 = std::make_pair('g', '8');
        auto left_rook = std::make_pair('h', '8');//after castling coord None pos
        auto left_rook_end = std::make_pair('f', '8');//black after castling king pos
        auto king_pos_begin = std::make_pair('e', '8');//after castling coord None pos
        auto king_pos_end = std::make_pair('g', '8');//black after castling king pos
        AssertEqual(player_white.makeMove(begin_pair10, end_pair10, color_black),
                    true, "move check - castle black 12_right");
        Assert(player_white.board.getData(left_rook)->getPieceType() ==
               PieceType::None, "move check - castle black 13_right");
        Assert(player_white.board.getData(left_rook)->getPieceType() ==
               PieceType::None, "move check - castle black 14_right");
        Assert(player_white.board.getData(left_rook_end)->getPieceType() == PieceType::Rook, " - castle black 15_right");
        Assert(player_white.board.getData(king_pos_begin)->getPieceType() ==
                                   PieceType::None, " - castle black 16_right");
        Assert(player_white.board.getData(king_pos_end)->getPieceType() ==
                      PieceType::King, "move check - - castle black 17_right");
    }

}

void testPawnAttackSet()
{
    {
        Player player_white("p1", Color::WHITE, true);
        Player player_black("p2", Color::BLACK, false);
        
        auto color_white = Color::WHITE;
        auto color_black = Color::BLACK;
        
        auto begin_pair = std::make_pair('a', '2');//move pawn
        auto end_pair = std::make_pair('a', '4');//white
        
        Cell tmp1 ('b', '5');
        std::set<Cell> tmp_pawn_1 {tmp1};
        
        player_white.makeMove(begin_pair, end_pair, color_white);
        Assert(player_white.board.getData(end_pair)->getAttackSet() ==
                                              tmp_pawn_1, "pawn_attack_set_1");
        
//------
        auto begin_pair1 = std::make_pair('b', '7');//move pawn
        auto end_pair1 = std::make_pair('b', '5');//black


        Cell tmp2 ('a', '4');
        Cell tmp3 ('c', '4');
        std::set<Cell> tmp_pawn_2 {tmp2, tmp3};
        
        player_white.makeMove(begin_pair1, end_pair1, color_black);
        Assert(player_white.board.getData(end_pair1)->getAttackSet() ==
                                             tmp_pawn_2, "pawn_attack_set_2");
//------
//------
        auto begin_pair2 = std::make_pair('c', '2');//move pawn
        auto end_pair2 = std::make_pair('c', '3');//white


        Cell tmp4 ('b', '4');
        Cell tmp5 ('d', '4');
        std::set<Cell> tmp_pawn_3 {tmp4, tmp5};
        
        player_white.makeMove(begin_pair2, end_pair2, color_white);
        Assert(player_white.board.getData(end_pair2)->getAttackSet() ==
                                              tmp_pawn_3, "pawn_attack_set_3");
//------
//------
        auto begin_pair3 = std::make_pair('h', '7');//move pawn
        auto end_pair3 = std::make_pair('h', '6');//white


        Cell tmp6 ('g', '5');
        std::set<Cell> tmp_pawn_4 {tmp6};
        
        player_white.makeMove(begin_pair3, end_pair3, color_black);
        Assert(player_white.board.getData(end_pair3)->getAttackSet() ==
                                              tmp_pawn_4, "pawn_attack_set_4");
//------
//------
        auto begin_pair4 = std::make_pair('a', '4');//move pawn
        auto end_pair4 = std::make_pair('b', '5');//white


        Cell tmp7 ('a', '6');
        Cell tmp8 ('c', '6');
        std::set<Cell> tmp_pawn_5 {tmp7, tmp8};
        
        player_white.makeMove(begin_pair4, end_pair4, color_white);
        Assert(player_white.board.getData(end_pair4)->getAttackSet() ==
                                              tmp_pawn_5, "pawn_attack_set_5");
//------
//------
        auto begin_pair5 = std::make_pair('f', '7');//move pawn
        auto end_pair5 = std::make_pair('f', '6');//black


        Cell tmp9 ('g', '5');
        Cell tmp10 ('e', '5');
        std::set<Cell> tmp_pawn_6 {tmp9, tmp10};
        
        player_white.makeMove(begin_pair5, end_pair5, color_black);
        Assert(player_white.board.getData(end_pair5)->getAttackSet() ==
                                              tmp_pawn_6, "pawn_attack_set_6");
//------
//------
        auto begin_pair6 = std::make_pair('c', '3');//move pawn
        auto end_pair6 = std::make_pair('c', '4');//white


        Cell tmp11 ('d', '5');
        std::set<Cell> tmp_pawn_7 {tmp11};
        
        player_white.makeMove(begin_pair6, end_pair6, color_white);
        Assert(player_white.board.getData(end_pair6)->getAttackSet() ==
                                            tmp_pawn_7, "pawn_attack_set_7");
//------
//------
        auto begin_pair7 = std::make_pair('g', '7');//move pawn
        auto end_pair7 = std::make_pair('g', '5');//black


        Cell tmp12 ('f', '4');
        Cell tmp13 ('h', '4');
        std::set<Cell> tmp_pawn_8 {tmp12, tmp13};
        
        player_white.makeMove(begin_pair7, end_pair7, color_black);
        Assert(player_white.board.getData(end_pair7)->getAttackSet() ==
                                            tmp_pawn_8, "pawn_attack_set_8");
//------
    }
}
