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
        Variations variations(this->table->amountOfPlayers, this->table->deck, this->table->deckPosition);
        variations.mode = cmn::random;
        
        table->message();
        waitForUser();
        
        table->cardsAssignment();
        table->playersUpdate();
        
        table->setUnusedDeck();
        
        variations.combine(table->unusedCards, this->table->stage);
        
        table->getWinningPercentage(variations.player);
        
        this->draw();
        //variations.printUnusedDeck();
        
        if (table->stage == cmn::river)
            table->setWinner();
        
        table->stageChange();
    }
    waitForUser();
}

void Game::manualMode(){
    table->mode = cmn::manual;
    while (table->stage != cmn::end) {
        
        table->message();
        table->cardsInput();
        
        table->cardsAssignment();
        table->playersUpdate();
        
        Variations variations(this->table->amountOfPlayers, this->table->deck, this->table->deckPosition);
        variations.mode = cmn::manual;
        
        table->setUnusedDeck();
        
        variations.combine(table->unusedCards, this->table->stage);
        
        table->getWinningPercentage(variations.player);
        
        this->draw();
        if (table->stage == cmn::river)
            table->setWinner();
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
