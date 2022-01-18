//
//  Player.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#ifndef Player_hpp
#define Player_hpp

#include "Hand.hpp"
#include <vector>

class Player{
private:
    Hand hand;
    int amountOfCards;
    double winningPercentage;
public:
    friend class Table;
    Player(){amountOfCards =0;};
    
    ~Player(){};
};

#endif /* Player_hpp */
