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
#include "Common.hpp"

namespace handValue{
enum eHandValue {highcard, pair, twopairs, set, straight, flush, fullhouse, quads, straightflush};
}


struct Straight{
    bool isComplete;
    bool cardFlag[14] {false};
};

struct Color{
    bool isComplete;
    int amountOfHearts, amountOfDiamonds, amountOfClubs, amountOfSpades;
};

using std::vector;

class Hand{
private:
    vector<const Card*> hand;
    
    //qualifiers
    Straight straight;
    Color color;
    int repeatedCards[13];
    int *repeatedCardsSorted[13];
    
    handValue::eHandValue value;
    int capacity;
public:
    Hand();
    void setValue();
    void getCards(const vector<Card> &card);
    void getCard(const Card & card);
    
    void updateQualifiers(cmn::Stage stage);
    
    void checkRepeated(int start, int stop);
    void checkColor(int start, int stop);
    void checkStraight(int start, int stop);
    void print();
    void printValue();
    ~Hand(){};
};
#endif /* Hand_hpp */
