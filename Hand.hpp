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

struct SameCards{
    handValue::eHandValue handValue;
    int value[2][2];
};

struct Straight{
    bool isComplete;
    bool cardFlag[14];
    int lastValue;
};

struct Color{
    bool isComplete;
    int amountOfHearts, amountOfDiamonds, amountOfClubs, amountOfSpades;
    eColor color;
};

using std::vector;

class Hand{
private:
    vector<const Card*> hand;
    vector<const Card*> bestFive;
    
    //qualifiers
    Straight straight;
    Color color;
    SameCards sameCards;
    bool straightFlush;
    int repeatedCards[13][2];

    
    handValue::eHandValue value;
    int capacity;
    
    void setBestHighCard();
    void setBestSameCards();
    void setBestStraight();
    void setBestFlush();
    void setBestStraightFlush();
public:
    Hand();
    friend class Table;
    friend class Variations;
    
    void setValue();
    void getCards(const vector<Card> &card);
    void getCard(const Card & card);
    void popCard();
    void setBestFive();
    
    void updateQualifiers(cmn::Stage stage);
    void updateQualifiers();
    void resetQualifiers();
    
    void checkRepeated(int start, int stop);
    void checkColor(int start, int stop);
    void checkStraight(int start, int stop);
    void checkStraightFlush();
    void print();
    void printValue();
    void printBestFive();
    
    bool operator==(const Hand &hand) const;
    bool operator>(const Hand &hand) const;
    bool operator<(const Hand &hand) const;
    ~Hand(){};
};
#endif /* Hand_hpp */
