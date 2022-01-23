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
    double winningPercentage;
    double tiePercentage;
    int wins;
    int ties;
public:
    friend class Table;
    friend class Variations;
    Player();
    
    ~Player(){};
};

#endif /* Player_hpp */
