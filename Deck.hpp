//
//  Deck.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 29/12/2021.
//

#ifndef Deck_hpp
#define Deck_hpp

#include <algorithm>
#include <random>
#include "Card.hpp"


const int DECK_SIZE = 52;
const int SUIT_SIZE = 13;

class Deck{
private:
    Card card[DECK_SIZE];
public:
    Deck();
    
    friend eColor intToColor(int value);
    const Card & operator[](int index) const;
    void print();
    
    ~Deck(){};
};

#endif /* Deck_hpp */
