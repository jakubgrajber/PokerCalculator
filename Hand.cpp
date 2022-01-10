//
//  Hand.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 29/12/2021.
//

#include "Hand.hpp"

void Hand::updateHand(const vector<Card> &card){
    for (auto i = card.begin(); i!=card.end(); i++) {
        this->hand.push_back(&*i);
    }
}
void Hand::updateHand(const Card &card){
    this->hand.push_back(&card);
}

void Hand::print(){
    for (int i = 0; i<hand.size(); i++)
        hand[i]->print();
}
