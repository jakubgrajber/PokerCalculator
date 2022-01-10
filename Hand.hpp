//
//  Hand.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 29/12/2021.
//

#ifndef Hand_hpp
#define Hand_hpp

#include "Card.hpp"
#include <vector>
#include <algorithm>

enum eHandValue {none, highcard, pair, twopairs, set, straight, flush, fullhouse, quads, straightflush, royalflush};

using std::vector;

class Hand{
private:
    vector<const Card*> hand;
    eHandValue value;
    int capacity;
public:
    Hand(){capacity =0;};
    void setValue();
    void updateHand(const vector<Card> &card);
    void updateHand(const Card & card);
    void print();
    ~Hand(){};
};
#endif /* Hand_hpp */
