//
//  Game.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 01/01/2022.
//

#include "Game.hpp"

Game::Game(Table *table){
    this->copyTable = table;
}

void Game::setup(){
    copyTable->cardsAssignment();
}

void Game::draw(){
    copyTable->print();
}
