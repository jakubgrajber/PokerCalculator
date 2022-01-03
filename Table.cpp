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
    for (int i =0; i<3; i++)
        flop[i] = nullptr;
    turn = nullptr;
    river = nullptr;
    
}

void Table::pocketAssignment(){
    for (int i =0; i<amountOfPlayers; i++) {
        for (int j=0; j<2; j++) {
            player[i].getCard(deck[deckPosition++]);
        }
    }
}

void Table::flopAssignment(){
    deckPosition++;
    for (int i=0; i<3; i++) {
        flop[i] = &deck[deckPosition++];
    }
}

void Table::turnAssignment(){
    deckPosition++;
    turn = &deck[deckPosition++];
}
void Table::riverAssignment(){
    deckPosition++;
    river = &deck[deckPosition++];
}

void Table::print(){
for (int i =0; i<amountOfPlayers; i++) {
    std::cout << "Player " << i+1 << ": ";
    player[i].print();
    std::cout << std::endl;
    }
    std::cout << std::endl;
    
    if (flop[0] != nullptr) {
        std::cout << "FLOP: ";
        for (int i=0; i<3; i++) {
            flop[i]->print();
        }
    }
    if (turn != nullptr) {
        std::cout << "  TURN: ";
        turn->print();
    }
    if (river!= nullptr) {
        std::cout << "  RIVER: ";
        river->print();
    }
    std::cout << std::endl;
}

Table::~Table(){
    delete [] player;
}


