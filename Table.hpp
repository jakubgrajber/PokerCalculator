//
//  Table.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#ifndef Table_hpp
#define Table_hpp

#include <memory>
#include "Player.hpp"
#include "Deck.hpp"


class Table{
private:
    Player *player;
    Deck deck;
    const Card *flop[3];
    const Card *turn;
    const Card *river;
    
    int amountOfPlayers;
    int deckPosition;
public:
    Table(int amountOfPlayers);
    void pocketAssignment();
    void flopAssignment();
    void turnAssignment();
    void riverAssignment();
    void print();
    ~Table();
};

#endif /* Table_hpp */
