//
//  TableVariations.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 20/01/2022.
//

#include "TableVariations.hpp"

Variations::Variations(int amountOfPlayers, Deck &deck, int positionInDeck) : Table(amountOfPlayers, deck, positionInDeck){
}

void Variations::printUnusedDeck(){
    for(const Card &i : unusedCards)
        i.print();
}

void Variations::combine(std::vector <Card> &unusedCards, cmn::Stage originalStage){
    this->stage = cmn::river;
    cardsAssignment(originalStage);
    
    switch (originalStage) {
        case cmn::pocket:
            sizeOfVariations = 5;
            break;
        case cmn::flop:
            sizeOfVariations = 2;
            break;
        case cmn::turn:
            sizeOfVariations = 1;
            break;
        default:
            return;
    }
    int startingPosition = 0;
    for (int i =0; i<sizeOfVariations; i++) {
        positionInDeck.push_back(startingPosition);
        variation.push_back(&unusedCards[startingPosition++]);
    }
    int counter = 0;
    
    hasMoreVariations = true;
    
    while (hasMoreVariations) {
        startingPosition = positionInDeck[sizeOfVariations-1];
        for (int i = startingPosition; i<unusedCards.size(); i++) {
            variation[sizeOfVariations-1] = &unusedCards[i];
            positionInDeck[sizeOfVariations-1]++;
            counter++;
            assignVariationCards();
            playersUpdate();
            this->print();
            setWinner();
            clearVariationCards();
            playersReset();
            showVariant();
        }
        setFamily(unusedCards);
    }
    std::cout << counter << std::endl;
    positionInDeck.clear();
    variation.clear();
}

void Variations::showVariant(){
    for (Card *i : variation)
        i->print();
    std::cout << endl;
}

void Variations::setFamily(std::vector <Card> &unusedCards){
    int positionToChange = whichPositionChange(unusedCards);
    
    if (positionToChange < 0) {
        hasMoreVariations = false;
        return;
    }
    
    positionInDeck[positionToChange]++;
    variation[positionToChange] = &unusedCards[positionInDeck[positionToChange]];
    
    for (int i = positionToChange + 1; i < sizeOfVariations; i++) {
        positionInDeck[i] = positionInDeck[i-1] + 1;
        variation[i]= &unusedCards[positionInDeck[i]];
    }
}

int Variations::whichPositionChange(std::vector <Card> &unusedCards){
    int positionToChange = -1;
    int counter = 2;
    for (int i = sizeOfVariations-2; i>=0; i--)
        if (positionInDeck[i] + counter++ != unusedCards.size()) {
            positionToChange = i;
            break;
        }
    return positionToChange;
}

void Variations::assignVariationCards(){
    for (int i = 0 ; i<amountOfPlayers; i++)
        for (Card *x : variation)
            player[i].hand.getCard(*x);
}

void Variations::clearVariationCards(){
    for (int i = 0 ; i<amountOfPlayers; i++)
        for (int j =0; j<sizeOfVariations;j++)
            player[i].hand.popCard();
}

void Variations::cardsAssignment(cmn::Stage stage){
    cmn::Stage tempStage = cmn::pocket;
    deckPosition =0;
    do {
        switch (tempStage) {
            case cmn::pocket:
                if (mode == cmn::manual)
                    deckPosition =0;
                pocketAssignment();
                break;
            case cmn::flop:
                if (mode == cmn::manual)
                    deckPosition = amountOfPlayers*2;
                cardsAssignment(3);
                break;
            case cmn::turn:
                if (mode == cmn::manual)
                    deckPosition = amountOfPlayers*2 + 3;
                cardsAssignment(4);
                break;
            case cmn::river:
                if (mode == cmn::manual)
                    deckPosition =amountOfPlayers*2 +4;
                cardsAssignment(5);
                break;
            default:
                break;
        }
        stageChange(tempStage);
    } while (tempStage <= stage);
}

void Variations::cardsAssignment(int limit){
    for (int i=0;i<limit ; i++) {
        communityCards.push_back(&deck[deckPosition]);
        for (int i=0; i<amountOfPlayers; i++)
            player[i].hand.getCard(deck[deckPosition]);
        deckPosition++;
    }
}

void Variations::setWinner(){
    int winner_index = 0;
    bool tie = false;
    
    for (int i=1;i<amountOfPlayers; i++) {
        if (player[i].hand.value > player[winner_index].hand.value){
            winner_index = i;
            tie = false;
        }
        else if (player[i].hand.value == player[winner_index].hand.value) {
            for (int j =0; j<5; j++) {
                if (*player[i].hand.bestFive[j] > *player[winner_index].hand.bestFive[j]) {
                    winner_index = i;
                    tie = false;
                    break;
                }
                if (*player[i].hand.bestFive[j] < *player[winner_index].hand.bestFive[j]){
                    break;
                }
                if (j==4)
                    tie = true;
            }
        }
        
    }
    if (!tie)
        std::cout << "\nPlayer #" << winner_index+1 << " is the winner"<< std::endl;
    else
        setTies(winner_index);
    
    player[winner_index].hand.print();
    for (int i = 0; i<5; i++){
        player[winner_index].hand.bestFive[i]->print();
    }
    std::cout << std::endl;
}

void Variations::playersUpdate(){
    for (int i = 0; i<amountOfPlayers; i++)
        player[i].hand.updateQualifiers();
}

void Variations::playersReset(){
    for (int i = 0; i<amountOfPlayers; i++)
        player[i].hand.resetQualifiers();
}


