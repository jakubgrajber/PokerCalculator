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

void Table::pocketAssignment(){
    for (int i =0; i<amountOfPlayers; i++) {
        for (int j=0; j<2; j++)
            player[i].hand.updateHand(deck[deckPosition++]);
    }
}

void Table::flopAssignment(){
    deckPosition++;
    for (int i=0; i<3; i++) {
        communityCards.push_back(&deck[deckPosition++]);
    }
}

void Table::turnRiverAssignment(){
    deckPosition++;
    communityCards.push_back(&deck[deckPosition++]);
}

void Table::print(){
for (int i =0; i<amountOfPlayers; i++) {
    std::cout << "Player " << i+1 << ": ";
    player[i].print();
    std::cout << std::endl;
    }
    std::cout << std::endl;
    
    if (communityCards.size()>0) {
        std::cout << "FLOP: ";
        for (int i=0; i<3; i++) {
            communityCards[i]->print();
        }
    }
    if (communityCards.size()>3) {
        std::cout << "  TURN: ";
        communityCards[3]->print();
    }
    if (communityCards.size()>4) {
        std::cout << "  RIVER: ";
        communityCards[4]->print();
    }
    std::cout << std::endl;
}

Table::~Table(){
    delete [] player;
}


