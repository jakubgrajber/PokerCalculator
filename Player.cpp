//
//  Player.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#include "Player.hpp"

void Player::getCard(const Card &card){
    hand.push_back(card);
    amountOfCards++;
}

void Player::print(){
    for (int i =0; i<amountOfCards; i++){
        hand[i].print();
    }
}
