//
//  Deck.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 29/12/2021.
//

#include "Deck.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> distrib(0,51);

eColor intToColor(int x){
    switch (x){
        case 0:
            return spade;
        case 1:
            return club;
        case 2:
            return diamond;
        case 3:
            return heart;
        default:
            return spade;
    }
}

Deck::Deck(){
    int valueOfCardInSuit;
    int numberOfCardsInDeck = 0;
    
    for (int suit = 0; suit <4; suit++) {
        valueOfCardInSuit = 2;
        for (int i = valueOfCardInSuit; i<=SUIT_SIZE+1; i++) {
            this->card[numberOfCardsInDeck++] = Card(i, intToColor(suit));
        }
    }
}

void Deck::shuffleDeck(){
    std::shuffle(&card[0], &card[52], std::mt19937(distrib(gen)));
}

const Card & Deck::operator[](int index) const {
    return card[index];
}

void Deck::print(){
    for (int i=0; i<DECK_SIZE; i++) {
        this->card[i].print();
        std::cout<<std::endl;
    }
}
