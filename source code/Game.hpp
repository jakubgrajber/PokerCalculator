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
#include "TableVariations.hpp"

class Game{
private:
    Table *table;
public:
    Game(){table = NULL;};
    Game(Table *table);
    void randomMode();
    void manualMode();
    void modifyMode();
    void draw();
    ~Game(){};
};


#endif /* Game_hpp */
