//
//  Game.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 01/01/2022.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Table.hpp"

class Game{
private:
    friend class Table;
    Table *copyTable;
public:
    Game(){copyTable = NULL;};
    Game(Table *table);
    void setup();
    void draw();
    ~Game(){};
};

#endif /* Game_hpp */
