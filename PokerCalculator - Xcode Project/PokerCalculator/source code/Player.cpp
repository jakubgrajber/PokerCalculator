//
//  Player.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#include "Player.hpp"

Player::Player(){
    winningPercentage = 0.0;
    tiePercentage= 0.0;
    wins = 0;
    ties = 0;
}

void Player::setPercentage(int amountOfVariations){
    winningPercentage = wins / double(amountOfVariations) * 100.00;
    tiePercentage = ties / double(amountOfVariations) * 100.00;
}

void Player::printPercentage(){
    std::cout << std::fixed << std::setprecision(2) << winningPercentage << " % to win, " << tiePercentage << " % to tie.";
}

void Player::resetValues(){
    winningPercentage = 0.0;
    tiePercentage= 0.0;
    wins = 0;
    ties = 0;
}



