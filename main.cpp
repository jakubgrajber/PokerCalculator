//
//  main.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 28/12/2021.
//

#include <iostream>
#include "Deck.hpp"
#include "Card.hpp"

int main() {
    Deck mainDeck;
    mainDeck.print();
    std::cout<<std::endl;
    
    Card test = mainDeck[4];
    
    test.print();
    return 0;
}
