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
#include <vector>


class Table{
private:
    Player *player;
    Deck deck;
    std::vector <const Card*> communityCards; //0-2 flop, 3 turn, 4 river
    
    int amountOfPlayers;
    int deckPosition;
public:
    Table(int amountOfPlayers);
    void pocketAssignment();
    void flopAssignment();
    void turnRiverAssignment();
    
    void pocket();
    void flop();
    void turn();
    void river();
    
    
    void print();
    ~Table();
};

#endif /* Table_hpp */
