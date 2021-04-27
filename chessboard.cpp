#include "headers/chessboard.hpp"
#include "headers/figure.hpp"
#include "headers/emptypiece.hpp"
#include "headers/pawn.hpp"
#include "headers/rook.hpp"
#include "headers/horse.hpp"
#include "headers/queen.hpp"
#include "headers/king.hpp"
#include "headers/bishop.hpp"


template<class P1, class P2>
bool operator==(std::pair<P1, P2>& lhs, std::pair<P1, P2>& rhs)
{
    return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<class P1, class P2>
std::ostream& operator<<(std::ostream& os, std::pair<P1, P2>& lhs)
{
    os << lhs.first << lhs.second;
    return os;
}

//инициализация статического приват словаря
std::map<Cell, std::shared_ptr<Piece>> ChessBoard::_board_data;


void ChessBoard::setData(const Cell& key, const std::shared_ptr<Piece> piece)
{
    if (_board_data.count(key) > 0)
        _board_data[key] = piece;
    else
        throw std::invalid_argument("Wrong data!");
}


//Возвращаем фигуру по указанным координатам
std::shared_ptr<Piece> ChessBoard::getData(const Cell& key)
{
    if (_board_data.count(key) > 0)
        return _board_data[key];
    else
        return std::make_shared<EmptyPiece>(Color::None,PieceType::None,
                                            std::make_pair('0', '0'));
}


//Проверка того, свободен ли путь для фигуры по горизонтали
bool ChessBoard::is_clear_horizontal(const Cell& b_cell, const Cell& e_cell)
{
    //Отдельно учитываем, что может быть рокировка
    if (getData(b_cell)->getColor() == getData(e_cell)->getColor() &&
        !(getData(b_cell)->getPieceType() == PieceType::King &&
          getData(e_cell)->getPieceType() == PieceType::Rook))
        return false;
    
    int b_x = b_cell.first;
    int e_x = e_cell.first;
    
    if (b_x > e_x)
    {
        for (int i = (e_x + 1); i < b_x; i++)
        {
            auto p = std::make_pair((char)i, b_cell.second);
            if(_board_data[p]->getPieceType() != PieceType::None)
                return false;
        }
    }
    
    if(b_x < e_x)
    {
        for (int i = (b_x + 1); i < e_x; i++)
        {
            auto p = std::make_pair((char)i, b_cell.second);
            if(_board_data[p]->getPieceType() != PieceType::None)
                return false;
        }
    }
    return true;
}


//Проверка свободы передвижения по вертикали
bool ChessBoard::is_clear_vertical(const Cell& b_cell, const Cell& e_cell)
{
    if (getData(b_cell)->getColor() == getData(e_cell)->getColor())
        return false;

    int b_y = b_cell.second;
    int e_y = e_cell.second;
    if (b_y > e_y)
    {
        for (int i = (e_y + 1); i < b_y; i++)
        {
            auto p = std::make_pair(b_cell.first, (char)i);
            if(_board_data[p]->getPieceType() != PieceType::None)
                return false;
        }
    }
    
    if(b_y < e_y)
    {
        for (int i = (b_y + 1); i < e_y; i++)
        {
            auto p = std::make_pair(b_cell.first, (char)i);
            if(_board_data[p]->getPieceType() != PieceType::None)
                return false;
        }
    }

    return true;
}


bool ChessBoard::is_clear_diagonal(const Cell& b_cell, const Cell& e_cell)
{
    if (getData(b_cell)->getColor() == getData(e_cell)->getColor())
        return false;
    
    int b_x = b_cell.first;
    int b_y = b_cell.second;
    
    int e_x = e_cell.first;
    int e_y = e_cell.second;

    //Проверяем есть ли там вообще диагональ
    if (std::abs(b_x - e_x) != std::abs(b_y - e_y))
        return false;//throw std::invalid_argument("Wrong data!");
   
    // Проверка 3 четверти
    if (b_x > e_x && b_y > e_y)
    {
        int start_x = --b_x;
        int start_y = --b_y;
        while (start_x > e_x)
        {
            auto pair_x_y =  std::make_pair((char)start_x--, (char)start_y--);
            if(_board_data[pair_x_y]->getPieceType() != PieceType::None)
                return false;
        }
    }
    
    //Проверка 4 четверти
    if (b_x > e_x && e_y > b_y)
    {
        int start_x = --b_x;//сразу на одну клетку вперед передвинулись
        int start_y = ++b_y;
        while (start_x > e_x)
        {
            auto pair_x_y =  std::make_pair((char)start_x--, (char)start_y++);
            if(_board_data[pair_x_y]->getPieceType() != PieceType::None)
                return false;
        }
    }

    //Проверка 1 четверти
    if (b_x < e_x && b_y < e_y)
    {
        int start_x = ++b_x;
        int start_y = ++b_y;
        while (start_x < e_x)
        {
            auto pair_x_y =  std::make_pair((char)start_x++, (char)start_y++);
            if(_board_data[pair_x_y]->getPieceType() != PieceType::None)
                return false;
        }
    }

    //Проверка 2 четверти
    if (b_x < e_x && b_y > e_y)
    {
        int start_x = ++b_x;
        int start_y = --b_y;
        while (start_x < e_x)
        {
            auto pair_x_y =  std::make_pair((char)start_x++, (char)start_y--);
            if(_board_data[pair_x_y]->getPieceType() != PieceType::None)
                return false;
        }
    }
    return true;
}


//Тут будем двигать фигуру, проверку отдельно на возможность движения делаем
bool ChessBoard::movePiece(const Cell& b_cell, const Cell& e_cell,
                           const Color& color)
{
    //Если начало и конец на доске
    if (_board_data.count(b_cell) > 0 && _board_data.count(e_cell) > 0 &&
        b_cell != e_cell)
    {
        auto piece = _board_data[b_cell];
        //Если в начале стоит фигура и она наша
        if (piece->getPieceType() != PieceType::None &&
            piece->getColor() == color)
        {
            //Идем к фигуре и проверяем правильность и возможность хода
            if (piece->can_move(e_cell))
            {
                //Обновляем все поля которые под атакой противника и возвращаем
                //координату нашего короля!
                Cell king_cell = updAttackField(color);
                
                //Отдельно пешку в ферзя добавим
                if(pawnToQueen(b_cell, e_cell, color))
                    return true;
                
                //Проверка того, находится/будет находиться король под угрозой
                if(isKingAttacked(king_cell, b_cell, e_cell, color))
                    return false;
                
                return true;
            }
        }
    }
    return false;
}


// Простая инициализация статик доски
void ChessBoard::initBoard()
{
    std::string x_val = "abcdefgh";
    for (const char& x : x_val)
    {
        for (int i = 1; i <= 8; i++ )
        {
            char num = i + '0';

            if (i <= 6 && i >= 3)
            {
                auto key = std::make_pair(x, num);
                auto valEmpty = std::make_shared<EmptyPiece>(Color::None,
                                    PieceType::None, std::make_pair('0', '0'));
                
                _board_data[key] = valEmpty;
                valEmpty->setPos(key);
            }
            
            if (i == 2)
            {
                auto key = std::make_pair(x, num);
                auto valPawn = std::make_shared<Pawn>(Color::WHITE,
                                                      PieceType::Pawn, key);
                _board_data[key] = valPawn;
                valPawn->setPos(key);
            }
            
            if (i == 1 && (x == 'a' || x == 'h'))
            {
                auto key = std::make_pair(x, num);
                auto valRook = std::make_shared<Rook>(Color::WHITE,
                                                      PieceType::Rook, key);
                _board_data[key] = valRook;
                valRook->setPos(key);
            }
            
            if (i == 1 && (x == 'b' || x == 'g'))
            {
                auto key = std::make_pair(x, num);
                auto valHorse = std::make_shared<Horse>(Color::WHITE,
                                                        PieceType::Horse, key);
                _board_data[key] = valHorse;
                valHorse->setPos(key);
            }

            if (i == 1 && (x == 'c' || x == 'f'))
            {
                auto key = std::make_pair(x, num);
                auto valBish = std::make_shared<Bishop>(Color::WHITE,
                                                        PieceType::Bishop, key);
                _board_data[key] = valBish;
                valBish->setPos(key);
            }
            
            if (i == 1 && x == 'd')
            {
                auto key = std::make_pair(x, num);
                auto valQueen = std::make_shared<Queen>(Color::WHITE,
                                                        PieceType::Queen, key);
                _board_data[key] = valQueen;
                valQueen->setPos(key);
            }
            
            if (i == 1 && x == 'e')
            {
                auto key = std::make_pair(x, num);
                auto valKing = std::make_shared<King>(Color::WHITE,
                                                      PieceType::King, key);
                
                _board_data[key] = valKing;
                valKing->setPos(key);
            }
            
            if (i == 7)
            {
                auto key = std::make_pair(x, num);
                auto val = std::make_shared<Pawn>(Color::BLACK,
                                                  PieceType::Pawn, key);
                _board_data[key] = val;
                val->setPos(key);

            }
            
            if (i == 8 && (x == 'a' || x == 'h'))
            {
                auto key = std::make_pair(x, num);
                auto val = std::make_shared<Rook>(Color::BLACK,
                                                  PieceType::Rook, key);
                _board_data[key] = val;
                val->setPos(key);
            }
            
            if (i == 8 && (x == 'b' || x == 'g'))
            {
                auto key = std::make_pair(x, num);
                auto val = std::make_shared<Horse>(Color::BLACK,
                                                   PieceType::Horse, key);
                _board_data[key] = val;
                val->setPos(key);
            }
            
            if (i == 8 && (x == 'c' || x == 'f'))
            {
                auto key = std::make_pair(x, num);
                auto val = std::make_shared<Bishop>(Color::BLACK,
                                                    PieceType::Bishop, key);
                _board_data[key] = val;
                val->setPos(key);

            }
            
            if (i == 8 && x == 'd')
            {
                auto key = std::make_pair(x, num);
                auto val = std::make_shared<Queen>(Color::BLACK,
                                                   PieceType::Queen, key);
                _board_data[key] = val;
                val->setPos(key);
            }
            
            if (i == 8 && x == 'e')
            {
                auto key = std::make_pair(x, num);
                auto val = std::make_shared<King>(Color::BLACK, PieceType::King,
                                                  key);
                _board_data[key] = val;
                val->setPos(key);
            }
        }
    }
}


void ChessBoard::printBoard() const
{
    
    std::cout << "  ________________" << std::endl;


        for (int i = 8; i > 0; i--)
        {
            std::cout << i << '|';
            for (const auto& [key, value] : ChessBoard::_board_data)
            {
                if (key.second == i + '0')
                {
                    if (value->getPieceType() == PieceType::King)
                    {
//                        value->movePiece(key, key);
                        std::cout << "K";
                    }
                    else if (value->getPieceType() == PieceType::Pawn)
                    {
                        
                        std::cout << "P";
                    }
                    else if (value->getPieceType() == PieceType::Rook)
                    {
                        std::cout << "R";
                    }
                    else if (value->getPieceType() == PieceType::Horse)
                    {
                        std::cout << "H";
                    }
                    else if (value->getPieceType() == PieceType::Bishop)
                    {
                        std::cout << "B";
                    }
                     else if (value->getPieceType() == PieceType::Queen)
                    {
                        std::cout << "Q";
                    }
                     else
                    {
                        std::cout << "-";
                    }

                    if (value->getColor() == Color::WHITE)
                    {
                        std::cout << "w";
                    }
                    else if(value->getColor() == Color::BLACK)
                    {
                        std::cout << "b";
                    }
                    else
                    {
                        std::cout << " ";
                    }
                }
            }
            std::cout << std::endl;
        }
    std::cout << "  a b c d e f g h " << std::endl;
}


bool ChessBoard::pawnToQueen(const Cell& b_cell, const Cell& e_cell,
                             const Color& color)
{
    auto piece = _board_data[b_cell];
    
    if (e_cell.second == '8' && piece->getPieceType() == PieceType::Pawn &&
        color == Color::WHITE)
    {
        _board_data[b_cell] = std::make_shared<EmptyPiece>(Color::None,
                              PieceType::None, std::make_pair('0', '0'));

        auto valQueen = std::make_shared<Queen>(Color::WHITE, PieceType::Queen,
                                                e_cell);
        _board_data[e_cell] = valQueen;
        piece = _board_data[e_cell];
        piece->setPos(e_cell);
        piece->computeAttackedCells();//Потом его на новой точке переписываем
        return true;
    }
    else if(e_cell.second == '1' && piece->getPieceType() ==PieceType::Pawn &&
                                    piece->getColor() == Color::BLACK)
    {
        _board_data[b_cell] = std::make_shared<EmptyPiece>(Color::None,
                                    PieceType::None, std::make_pair('0', '0'));
        auto valQueen = std::make_shared<Queen>(Color::BLACK, PieceType::Queen,
                                                e_cell);
        _board_data[e_cell] = valQueen;
        piece = _board_data[e_cell];
        piece->setPos(e_cell);
        piece->computeAttackedCells();//Потом его на новой точке переписываем
        return true;
    }
    return false;
}


//Проверяем все клетки, атакует ли кто то из них короля начало/конец
bool ChessBoard::isKingAttacked(const Cell& king_cell, const Cell& b_cell,
                                const Cell& e_cell, const Color& color)
{
    for (const auto& [key, value] : _board_data)
    {
        if (value->getColor() != color)
        {
            auto attack_set = value->getAttackSet();
            auto b_res = std::find(attack_set.begin(), attack_set.end(),
                            king_cell);
            if (b_res != attack_set.end())
            {
                std::cout << "Your King under attack! Do smth!" << std::endl;
            }
        }
    }
    
//    Тут логика странная. но как по другому сделать не переписывая кучу всего
//    и не добавляя.. не думается.
//    Мы имитируем ход. добавляем  и удаляем фигуру как при ходе. Дальше
//    проверяем остался ли король под угрозой, если да - просим переходить.
    auto piece = getData(b_cell);
    _board_data[e_cell] = piece;
    _board_data[b_cell] = std::make_shared<EmptyPiece>(Color::None,
                        PieceType::None, std::make_pair('0', '0'));
    piece->setPos(e_cell);
    piece->eraseAttackSet();//Сначала стерли сет полностью
    piece->computeAttackedCells();//Потом его на новой точке переписываем
    
    Cell king_cell_upd = updAttackField(color);
    for (const auto& [key, value] : _board_data)
    {
        if (value->getColor() != color)
        {
//          для всех фигур противника постоянно надо вычислять поля под боем!
            auto attack_set = value->getAttackSet();
            auto b_res = std::find(attack_set.begin(), attack_set.end(),
                                                        king_cell_upd);
            if (b_res != attack_set.end())
            {
                std::cout << "You can't move to this cell! You King will be "
                            "under" << std::endl;
                
                auto piece = getData(e_cell);
                _board_data[b_cell] = piece;
                _board_data[e_cell] = std::make_shared<EmptyPiece>(Color::None,
                                    PieceType::None, std::make_pair('0', '0'));
                piece->setPos(b_cell);
                piece->eraseAttackSet();//Сначала стерли сет полностью
                piece->computeAttackedCells();//Потом его на новой -переписываем
                return true;
            }
        }
    }

    piece->setCountMoves();
    return false;
}

//Обновляем полностью все поля для атаки у противника
Cell ChessBoard::updAttackField(const Color& color)
{
    Cell king_cell;
    for (const auto& [key, value] : _board_data)
    {
        if (value->getPieceType() == PieceType::King && value->getColor() == color)
            king_cell = value->getPos();
        
        if (value->getColor() != color)
            //для всех фигур противника постоянно надо вычислять поля под боем!
            value->computeAttackedCells();
    }
    return king_cell;
}

//Заполняем вертикаль клетками под атакой и первой клеткой противника
std::set<Cell> ChessBoard::doVertAttackSet(const Cell& cell_pos,
                                           const PieceType& type, const Color& color)
{
    std::set<Cell> tmp_set;
    char b_y = cell_pos.second;
    
    while (b_y++ != '8')
    {
        if (getData({cell_pos.first, b_y})->getColor() == color)
            break;

        if (getData({cell_pos.first, b_y})->getColor() != color)
        {
            tmp_set.insert({cell_pos.first, b_y});
            if (getData({cell_pos.first, b_y})->getColor() != Color::None)
                break;
        }
    }

    b_y = cell_pos.second;
    while (b_y-- != '1')
    {
        if (getData({cell_pos.first, b_y})->getColor() == color)
            break;

        if (getData({cell_pos.first, b_y})->getColor() != color)
        {
            tmp_set.insert({cell_pos.first, b_y});
            if (getData({cell_pos.first, b_y})->getColor() != Color::None)
                break;
        }
    }
    
    return tmp_set;
}

std::set<Cell> ChessBoard::doHorAttackSet(const Cell& cell_pos,
                         const PieceType& type, const Color& color)
{
    std::set<Cell> tmp_set;
    char b_x = cell_pos.first;
    
    while (b_x++ != 'h')
    {
        if (getData({b_x, cell_pos.second})->getColor() == color)
            break;

        if (getData({b_x, cell_pos.second})->getColor() != color)
        {
            tmp_set.insert({b_x, cell_pos.second});
            if (getData({b_x, cell_pos.second})->getColor() != Color::None)
                break;
        }
    }

    b_x = cell_pos.first;
    while (b_x-- != 'a')
    {
        if (getData({b_x, cell_pos.second})->getColor() == color)
            break;

        if (getData({b_x, cell_pos.second})->getColor() != color)
        {
            tmp_set.insert({b_x, cell_pos.second});
            if (getData({b_x, cell_pos.second})->getColor() != Color::None)
                break;
        }
    }
    
    return tmp_set;
}


std::set<Cell> ChessBoard::doDiagAttackSet(const Cell& cell_pos,
                                      const PieceType& type, const Color& color)
{
    std::set<Cell> tmp_set1;
    std::set<Cell> tmp_set2;
    std::set<Cell> tmp_set3;
    std::set<Cell> tmp_set4;
    

    int b_x = cell_pos.first;
    int b_y = cell_pos.second;

    //3 четверть
    while (b_x-- != 'a' && b_y-- != '1')
    {
        if (getData({b_x, b_y})->getColor() == color)
            break;

        if (getData({b_x, b_y})->getColor() != color)
        {
            tmp_set3.insert({b_x, b_y});
            if (getData({b_x, b_y})->getColor() != Color::None)
                break;
        }
    }
    
    b_x = cell_pos.first;
    b_y = cell_pos.second;
    //4 четверть
    while (b_x-- != 'a' && b_y++ != '8')
    {
        if (getData({b_x, b_y})->getColor() == color)
            break;

        if (getData({b_x, b_y})->getColor() != color)
        {
            tmp_set4.insert({b_x, b_y});
            if (getData({b_x, b_y})->getColor() != Color::None)
                break;
        }
    }

    
    b_x = cell_pos.first;
    b_y = cell_pos.second;
    //1 четверть
    while (b_x++ != 'h' && b_y++ != '8')
    {
        if (getData({b_x, b_y})->getColor() == color)
            break;

        if (getData({b_x, b_y})->getColor() != color)
        {
            tmp_set1.insert({b_x, b_y});
            if (getData({b_x, b_y})->getColor() != Color::None)
                break;
        }
    }

    b_x = cell_pos.first;
    b_y = cell_pos.second;
    //2 четверть
    while (b_x++ != 'h' && b_y-- != '1')
    {
        if (getData({b_x, b_y})->getColor() == color)
            break;

        if (getData({b_x, b_y})->getColor() != color)
        {
            tmp_set2.insert({b_x, b_y});
            if (getData({b_x, b_y})->getColor() != Color::None)
                break;
        }
    }

    std::set<Cell> tmp_set(tmp_set1);
    tmp_set.insert(tmp_set2.begin(), tmp_set2.end());
    tmp_set.insert(tmp_set3.begin(), tmp_set3.end());
    tmp_set.insert(tmp_set4.begin(), tmp_set4.end());
    
    return tmp_set;
}

