//
//  Table.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#ifndef Table_hpp
#define Table_hpp

#include <memory>
#include <stdio.h>
#include "Player.hpp"
#include "Deck.hpp"

class Table{
private:
    Player *player;
    Deck deck;
public:
    Table(int amountOfPlayers);
    ~Table();
};

#endif /* Table_hpp */
