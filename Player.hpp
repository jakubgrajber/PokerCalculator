//
//  Player.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#ifndef Player_hpp
#define Player_hpp

#include <stdio.h>
#include "Hand.hpp"

class Player{
private:
    Hand hand;
    double winningPercentage;
public:
    Player(){};
    
    ~Player(){};
};

#endif /* Player_hpp */