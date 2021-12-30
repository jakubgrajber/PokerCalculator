//
//  Table.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#include "Table.hpp"

Table::Table(int amountOfPlayers){
    player = new Player[amountOfPlayers];
}

Table::~Table(){
    delete [] player;
}


