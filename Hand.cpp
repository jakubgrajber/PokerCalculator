//
//  Hand.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 29/12/2021.
//

#include "Hand.hpp"

void Hand::updateHand(const vector<Card>& card){
    for (auto i =card.begin(); i!=card.end(); i++) {
        this->hand.push_back(*i);
    }
}

void Hand::print(){
    for (auto i = this->hand.begin(); i!=this->hand.end(); i++)
        i->print();
}
