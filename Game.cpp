//
//  Game.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 01/01/2022.
//

#include "Game.hpp"

using std::cout;
using std::endl;

void waitForUser();

Game::Game(Table *table){
    this->table = table;
}

void Game::randomMode(){
    table->mode = cmn::random;
    while (table->stage != cmn::end) {
        table->message();
        waitForUser();
        table->cardsAssignment();
        table->playersUpdate();
        this->draw();
        table->stageChange();
    }
    waitForUser();
}

void Game::manualMode(){
    table->mode = cmn::manual;
    while (table->stage != cmn::end) {
        table->message();
        table->cardsInput();
        //cards input
        waitForUser();
        table->stageChange();
    }
}

void Game::draw(){
    table->print();
}


void waitForUser(){
    do{
        cout << "Press enter to continue..." << endl;
     } while (std::cin.get() != '\n');
}
