//
//  Hand.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 29/12/2021.
//

#include "Hand.hpp"

Hand::Hand(){
    straight.isComplete = false;
    
    color.isComplete = false;
    color.amountOfClubs = color.amountOfDiamonds = color.amountOfHearts = color.amountOfSpades = 0;
    
    straightFlush = false;
    
    for (int i =0; i<13; i++)
        repeatedCards[i][0] = 0;
    for (int i = 0; i<13; i++)
        repeatedCards[i][1] = i+2;
    
    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            sameCards.value[i][j] = 0;
        }
    }
    for (int i =0; i<14; i++) {
        straight.cardFlag[i] = false;
    }
}

void Hand::setValue(){
    if (straightFlush)
        value = handValue::straightflush;
    else if (sameCards.value[0][0] == 4)
        value = handValue::quads;
    else if (sameCards.value[0][0] == 3 && sameCards.value[1][0] >= 2)
        value = handValue::fullhouse;
    else if (color.isComplete)
        value = handValue::flush;
    else if (straight.isComplete)
        value = handValue::straight;
    else if (sameCards.value[0][0] == 3)
        value = handValue::set;
    else if (sameCards.value[0][0] == 2 && sameCards.value[1][0] == 2)
        value = handValue::twopairs;
    else if (sameCards.value[0][0] == 2)
        value = handValue::pair;
    else
        value = handValue::highcard;
}

void Hand::setBestFive(){
    switch (value) {
        case handValue::highcard:
            setBestHighCard();
            break;
        case handValue::pair: case handValue::twopairs: case handValue::set: case handValue::fullhouse: case handValue::quads:
            setBestSameCards();
            break;
        case handValue::straight:
            setBestStraight();
            break;
        case handValue::flush:
            setBestFlush();
            break;
        case handValue::straightflush:
            setBestStraightFlush();
            break;
        default:
            break;
    }
}

void Hand::updateQualifiers(cmn::Stage stage){
    int start, stop;
    cmn::stageToDomain(stage, start, stop);
    checkRepeated(start, stop);
    checkColor(start, stop);
    checkStraight(start, stop);
    if (straight.isComplete && color.isComplete)
        checkStraightFlush();
    setValue();
    if (stage == cmn::river)
        setBestFive();
}

void Hand::updateQualifiers(){
    checkRepeated(0, 6);
    checkColor(0, 6);
    checkStraight(0, 6);
    if (straight.isComplete && color.isComplete)
        checkStraightFlush();
    setValue();
    setBestFive();
}

void Hand::resetQualifiers(){
    straight.isComplete = false;
    straight.lastValue = 0;
    straightFlush = false;
    color.isComplete = false;
    color.color = none;
    color.amountOfClubs = color.amountOfDiamonds = color.amountOfHearts = color.amountOfSpades = 0;
    
    for (int i =0; i<13; i++)
        repeatedCards[i][0] = 0;
    for (int i = 0; i<13; i++)
        repeatedCards[i][1] = i+2;
    
    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {
            sameCards.value[i][j] = 0;
        }
    }
    for (int i =0; i<14; i++) {
        straight.cardFlag[i] = false;
    }
}

void Hand::checkRepeated(int start, int stop){
    
    for (int i=start; i<=stop; i++)
        repeatedCards[hand[i]->Card::getValue()-2][0]++;
    
    int tempRepeatedCards[13][2];
    for (int i =0; i<13; i++)
        for (int j = 0; j<2; j++)
            tempRepeatedCards[i][j] = repeatedCards[i][j];

    cmn::insertionSort(tempRepeatedCards, 13, 0);
    
    for (int i =0; i<2; i++)
        for (int j=0; j<2; j++)
            sameCards.value[i][j] = tempRepeatedCards[i][j];
}

void Hand::checkColor(int start, int stop){
    if (!color.isComplete){
        for (int i =start; i<=stop; i++) {
            switch (hand[i]->getColor()) {
                case spade:
                    color.amountOfSpades++;
                    break;
                case club:
                    color.amountOfClubs++;
                    break;
                case heart:
                    color.amountOfHearts++;
                    break;
                case diamond:
                    color.amountOfDiamonds++;
                    break;
                default:
                    break;
            }
        }
        if (color.amountOfHearts >= 5){
            color.isComplete = true;
            color.color = heart;
        }
        else if (color.amountOfDiamonds >= 5){
            color.isComplete = true;
            color.color = diamond;
        }
        else if (color.amountOfClubs >= 5){
            color.isComplete = true;
            color.color = club;
        }
        else if (color.amountOfSpades >= 5){
            color.isComplete = true;
            color.color = spade;
        }
    }
}

void Hand::checkStraight(int start, int stop){
        for (int i=start; i<=stop; i++)
            straight.cardFlag[hand[i]->getValue()-1] = true;
        
        if (straight.cardFlag[13])
            straight.cardFlag[0] = true;
            
        int howManyStraightCards = 0;
        int lastIndex = 0;
        int longestStreak = 0;
        
        for (int i = 0; i < 14; i++) {
            if (straight.cardFlag[i]){
                howManyStraightCards++;
                if (howManyStraightCards > longestStreak){
                    longestStreak=howManyStraightCards;
                    lastIndex = i;
                }
            }
            else
                howManyStraightCards = 0;
        }
        if (longestStreak >= 5){
            straight.isComplete = true;
            straight.lastValue = lastIndex+1;
        }
        else
            straight.lastValue = 0;
    }

void Hand::checkStraightFlush(){
    int howManyOneSuitStraightCards = 1;
    int lastValue = 0;
    int longestStreak = 1;
    
    vector<const Card*> tempHand = hand;
    
    for (int i=0; i<tempHand.size(); i++)
        if (tempHand[i]->color != color.color){
            tempHand.erase(tempHand.begin()+i);
            i--;
        }
    
    std::sort(std::begin(tempHand), std::end(tempHand), [](const Card *a, const Card *b) {return *a > *b;});
    
    for (int i =1; i<tempHand.size(); i++) {
        if ((tempHand[i]->getValue()+1 == tempHand[i-1]->getValue() || (tempHand[i]->getValue() == 14 && tempHand[i-1]->getValue() == 5))){
            howManyOneSuitStraightCards++;
            if (howManyOneSuitStraightCards > longestStreak) {
                longestStreak = howManyOneSuitStraightCards;
                lastValue = tempHand[i]->getValue();
            }
        }
        else
            howManyOneSuitStraightCards = 1;
    }
    if (longestStreak >= 5) {
        straightFlush = true;
        straight.lastValue = lastValue+longestStreak-1;
    }

}

void Hand::getCards(const vector<Card> &card){
    for (auto i = card.begin(); i!=card.end(); i++) {
        this->hand.push_back(&*i);
        capacity++;
    }
}

void Hand::getCard(const Card &card){
    this->hand.push_back(&card);
    capacity++;
}

void Hand::popCard(){
    this->hand.pop_back();
    capacity--;
}

void Hand::print(){
    for (int i = 0; i<2; i++)
        hand[i]->print();
    std::cout << " ";
    printValue();
}

void Hand::printValue(){
    switch (value){
        case handValue::highcard:
            std::cout << "HIGH CARD    ";
            break;
        case handValue::pair:
            std::cout << "PAIR         ";
            break;
        case handValue::twopairs:
            std::cout << "TWO PAIRS    ";
            break;
        case handValue::set:
            std::cout << "SET          ";
            break;
        case handValue::straight:
        std::cout << "STRAIGHT     ";
            break;
            case handValue::flush:
            std::cout << "FLUSH        ";
            break;
        case handValue::fullhouse:
            std::cout << "FULL HOUSE   ";
            break;
        case handValue::quads:
            std::cout << "QUADS        ";
            break;
        case handValue::straightflush:
            std::cout << "STRAIGHT FLUSH";
            break;
    }
}

void Hand::printBestFive(){
    for (int i = 0; i<5; i++)
        bestFive[i]->print();
    std::cout << " ";
    printValue();
}

bool Hand::operator>(const Hand &hand) const{
    if (this->value != hand.value) {
        for (int i=0; i<bestFive.size(); i++) {
            if (bestFive[i] < hand.bestFive[i])
                return false;
            if (bestFive[i] > hand.bestFive[i])
                return true;
        }
        return false;
    }
    else return this->value > hand.value;
}

bool Hand::operator<(const Hand &hand) const{
    return this->value < hand.value;
}

void Hand::setBestHighCard(){
    bestFive = hand;
    std::sort(std::begin(bestFive), std::end(bestFive), [](const Card *a, const Card *b) {return *a > *b;});
    
    while (bestFive.size()>5)
        bestFive.pop_back();
}

void Hand::setBestSameCards(){
    bestFive = hand;

    int tempRepeatedCards[13][2];
    for (int i =0; i<13; i++)
        for (int j = 0; j<2; j++)
            tempRepeatedCards[i][j] = repeatedCards[i][j];

    cmn::insertionSort(tempRepeatedCards, 13, 0);
    
    if(tempRepeatedCards[0][0] == 2 && tempRepeatedCards[1][0] == 2 && tempRepeatedCards[2][0] == 2)
        cmn::insertionSort(tempRepeatedCards, 3, 1);

    else if(tempRepeatedCards[0][0]+tempRepeatedCards[1][0]+tempRepeatedCards[2][0] == 7){
        cmn::insertionSort(tempRepeatedCards, 3, 1);
        cmn::insertionSort(tempRepeatedCards, 3, 0);
    }
        
    for (int i =0; i<2; i++)
        for (int j=0; j<2; j++)
            sameCards.value[i][j] = tempRepeatedCards[i][j];
    
    if (sameCards.value[0][0] == sameCards.value[1][0] && sameCards.value[0][1]<sameCards.value[1][1]) {
        std::swap(sameCards.value[0][0], sameCards.value[1][0]);
        std::swap(sameCards.value[0][1], sameCards.value[1][1]);
    }
    
    for (int i =0; i<sameCards.value[0][0]; i++) {
        if (bestFive[i]->value != sameCards.value[0][1]) {
            for (int j = i+1; j<7; j++) {
                if (bestFive[j]->value == sameCards.value[0][1]){
                    std::swap(bestFive[i], bestFive[j]);
                    break;
                }
            }
        }
    }
    
    for (int i =sameCards.value[0][0]; i<sameCards.value[0][0]+sameCards.value[1][0]; i++) {
        if (bestFive[i]->value != sameCards.value[1][1]) {
            for (int j = i+1; j<7; j++) {
                if (bestFive[j]->value == sameCards.value[1][1]){
                    std::swap(bestFive[i], bestFive[j]);
                    break;
                }
            }
        }
    }
    
    int amountOfSwaps = sameCards.value[0][0] + sameCards.value[1][0];
    
    if (sameCards.value[1][0] <2)
        amountOfSwaps--;
    
    std::sort(std::begin(bestFive)+amountOfSwaps, std::end(bestFive), [](const Card *a, const Card *b) {return *a > *b;});
    
    while (bestFive.size()>5)
        bestFive.pop_back();
}

void Hand::setBestStraight(){
    bestFive = hand;
    for (int i = 0; i<5; i++) {
        if (bestFive[i]->value != straight.lastValue) {
            for (int j =i+1; j<7; j++) {
                if (bestFive[j]->value == straight.lastValue)
                    std::swap(bestFive[j], bestFive[i]);
            }
        }
        straight.lastValue--;
        if (straight.lastValue == 1)
            straight.lastValue = 14;
    }
    
    while (bestFive.size()>5)
        bestFive.pop_back();
}

void Hand::setBestFlush(){
    vector<const Card *> tempHand;
    tempHand = hand;
    
    for (int i = 0; i<tempHand.size(); i++)
        if (tempHand[i]->color != color.color) {
            tempHand.erase(tempHand.begin()+i);
            i--;
        }
    
    std::sort(std::begin(tempHand), std::end(tempHand), [](const Card *a, const Card *b) {return *a > *b;});
    
    while (bestFive.size()>5)
        bestFive.pop_back();
    
    bestFive = tempHand;
}

void Hand::setBestStraightFlush(){
    vector<const Card*> tempHand = hand;
    
    for (int i =0; i<tempHand.size(); i++)
        if (tempHand[i]->color != color.color){
            tempHand.erase(tempHand.begin()+i);
            i--;
        }
    
    for (int i = 0; i<5; i++) {
        if (tempHand[i]->value != straight.lastValue) {
            for (int j =i+1; j<tempHand.size(); j++) {
                if (tempHand[j]->value == straight.lastValue)
                    std::swap(tempHand[j], tempHand[i]);
            }
        }
        straight.lastValue--;
        if (straight.lastValue == 1)
            straight.lastValue = 14;
    }

    while (tempHand.size()>5)
        tempHand.pop_back();
    
    bestFive = tempHand;
}
