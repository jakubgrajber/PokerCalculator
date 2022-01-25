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
#include <iostream>
#include <iomanip>

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
    
    void setPercentage(int amountOfVariations);
    void printPercentage();
    void resetValues();
    void addWin() {wins++;};
    void addTie() {ties++;};

    Player();
    
    ~Player(){};
};

#endif /* Player_hpp */
