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
    
    for (int i=0; i<13 ;i++)
        repeatedCards[i] = 0;
    
    capacity = 0;
}

void Hand::updateHand(const vector<Card> &card){
    for (auto i = card.begin(); i!=card.end(); i++) {
        this->hand.push_back(&*i);
        capacity++;
    }
}
void Hand::updateHand(const Card &card){
    this->hand.push_back(&card);
    capacity++;
}

void Hand::checkPocket(){
    checkRepeated(0, 1);
    checkColor(0, 1);
    checkStraight(0, 1);
    setValue();
//    std::cout << std::endl;
//    for (int i=0; i<13; i++) {
//        std::cout << repeatedCards[i] << " ";
//    }
//    std::cout << std::endl;
//    for (int i=0; i<13; i++) {
//        std::cout << *repeatedCardsSorted[i] << " ";
//    }
//    std::cout << std::endl;
}
void Hand::checkFlop(){
    checkRepeated(2, 4);
    checkColor(2, 4);
    checkStraight(2, 4);
    setValue();
}

void Hand::checkTurn(){
    checkRepeated(5, 5);
    checkColor(5, 5);
    checkStraight(5, 5);
    setValue();
}
void Hand::checkRiver(){
    checkRepeated(6, 6);
    checkColor(6, 6);
    checkStraight(6, 6);
    setValue();
}


void Hand::setValue(){
    if (color.isComplete && straight.isComplete)
        value = handValue::straightflush;
    else if (*repeatedCardsSorted[0] == 4)
        value = handValue::quads;
    else if (*repeatedCardsSorted[0] == 3 && *repeatedCardsSorted[1] >= 2)
        value = handValue::fullhouse;
    else if (color.isComplete)
        value = handValue::flush;
    else if (straight.isComplete)
        value = handValue::straight;
    else if (*repeatedCardsSorted[0] == 3)
        value = handValue::set;
    else if (*repeatedCardsSorted[0] == 2 && *repeatedCardsSorted[1] == 2)
        value = handValue::twopairs;
    else if (*repeatedCardsSorted[0] == 2)
        value = handValue::pair;
    else
        value = handValue::highcard;
}

void Hand::checkRepeated(int start, int stop){
    for (int i=start; i<=stop; i++)
        repeatedCards[hand[i]->Card::getValue() - 2]++;
    
    for (int i = 0; i < 13; i++)
        repeatedCardsSorted[i] = &repeatedCards[i];
    std::sort(std::begin(repeatedCardsSorted), std::end(repeatedCardsSorted), [](int* a, int* b) { return *a > *b; });
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
            }
        }
        if (color.amountOfHearts == 5 || color.amountOfDiamonds == 5 || color.amountOfClubs == 5 || color.amountOfSpades == 5)
            color.isComplete = true;
    }
}

void Hand::checkStraight(int start, int stop){
    if (!straight.isComplete){
        for (int i=start; i<=stop; i++)
            straight.cardFlag[hand[i]->getValue()-1] = true;
        if (straight.cardFlag[13]) {
            straight.cardFlag[0] = true;
        }
        int howManyStraightCards = 0;
        for (int i = 0; i < 14; i++)
        {
            if (straight.cardFlag[i])
                howManyStraightCards++;
            else
                howManyStraightCards = 0;
            if (howManyStraightCards == 5){
                straight.isComplete = true;
                break;
            }
        }
    }
}



void Hand::print(){
    for (int i = 0; i<2; i++)
        hand[i]->print();
    std::cout << " ";
    printHandValue();
}

void Hand::printHandValue(){
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
            std::cout << "STRAIGH FLUSH";
            break;
    }
}

