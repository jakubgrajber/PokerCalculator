//
//  Table.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#include "Table.hpp"

Table::Table(int amountOfPlayers){
    if(amountOfPlayers>10)
        amountOfPlayers =10;
    player = new Player[amountOfPlayers];
    this->amountOfPlayers = amountOfPlayers;
    deckPosition = 0;
    
}

void Table::cardsAssignment(){
    for (int i =0; i<amountOfPlayers; i++) {
        for (int j=0; j<2; j++) {
            player[i].getCard(deck[deckPosition++]);
        }
    }
}
void Table::print(){
for (int i =0; i<amountOfPlayers; i++) {
    player[i].print();
    std::cout << std::endl;
    }
}

Table::~Table(){
    delete [] player;
}


