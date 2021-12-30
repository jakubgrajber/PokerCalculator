//
//  Player.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#ifndef Player_hpp
#define Player_hpp

#include "Card.hpp"
#include <vector>

class Player{
private:
    std::vector<Card> hand;
    int amountOfCards;
    double winningPercentage;
public:
    Player(){amountOfCards =0;};
    void getCard(const Card &card);
    void print();
    ~Player(){};
};

#endif /* Player_hpp */
