//
//  Table.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#include "Table.hpp"

Table::Table(int amountOfPlayers){
    player = new Player[amountOfPlayers];
    this->amountOfPlayers = amountOfPlayers;
    deckPosition = 0;
    
}

void Table::cardsAssignment(){
    for (int i =0; i<amountOfPlayers; i++) {
    }
}

Table::~Table(){
    delete [] player;
}


