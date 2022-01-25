//
//  TableVariations.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 20/01/2022.
//

#include "TableVariations.hpp"

Variations::Variations(int amountOfPlayers, Deck &deck, int positionInDeck) : Table(amountOfPlayers, deck, positionInDeck){
    amountOfVariations = 0;
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
            assignVariationCards();
            counter++;
            playersUpdate();
            setWinner();
            clearVariationCards();
            playersReset();
        }
        setFamily(unusedCards);
    }
    amountOfVariations = counter;
    setWinningPercentage();
    positionInDeck.clear();
    variation.clear();
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

void Variations::cardsAssignment(cmn::Stage stage){
    cmn::Stage tempStage = cmn::pocket;
    deckPosition =0;
    do {
        switch (tempStage) {
            case cmn::pocket:
                if (mode == cmn::manual)
                    deckPosition = 0;
                pocketAssignment();
                break;
            case cmn::flop:
                if (mode == cmn::manual)
                    deckPosition = amountOfPlayers*2;
                cardsAssignment(3);
                break;
            case cmn::turn:
                if (mode == cmn::manual)
                    deckPosition = amountOfPlayers*2 +3;
                cardsAssignment(1);
                break;
            default:
                break;
        }
        stageChange(tempStage);
    } while (tempStage <=stage);
}

void Variations::cardsAssignment(int limit){
    for (int i=0;i<limit ; i++) {
        communityCards.push_back(&deck[deckPosition]);
        for (int j=0; j<amountOfPlayers; j++)
            player[j].hand.getCard(deck[deckPosition]);
        deckPosition++;
    }
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

void Variations::setWinner(){
    int winnerIndex = 0;
    bool tie = false;
    
    for (int i=1;i<amountOfPlayers; i++) {
        if (player[i].hand.value > player[winnerIndex].hand.value){
            winnerIndex = i;
            tie = false;
        }
        else if (player[i].hand.value == player[winnerIndex].hand.value) {
            for (int j =0; j<5; j++) {
                if (*player[i].hand.bestFive[j] > *player[winnerIndex].hand.bestFive[j]) {
                    winnerIndex = i;
                    tie = false;
                    break;
                }
                if (*player[i].hand.bestFive[j] < *player[winnerIndex].hand.bestFive[j]){
                    break;
                }
                if (j==4)
                    tie = true;
            }
        }
        
    }
    if (!tie)
        player[winnerIndex].addWin();
    else
        setTies(winnerIndex);
}

void Variations::setTies(int firstIndex){
    vector<int> tiedIndex;
    tiedIndex.push_back(firstIndex);
    
    for (int i =firstIndex+1; i<amountOfPlayers; i++) {
        if (player[i].hand.value == player[firstIndex].hand.value)
            for (int j =0; j<5; j++){
                if (player[i].hand.bestFive[j]->getValue() != player[firstIndex].hand.bestFive[j]->getValue()) {
                    break;
                }
                if (j==4)
                    tiedIndex.push_back(i);
            }
    }
    for(int i: tiedIndex)
        player[i].addTie();
    
}

void Variations::playersUpdate(){
    for (int i = 0; i<amountOfPlayers; i++)
        player[i].hand.updateQualifiers();
}

void Variations::playersReset(){
    for (int i = 0; i<amountOfPlayers; i++)
        player[i].hand.resetQualifiers();
}

void Variations::setWinningPercentage(){
    for (int i =0; i<amountOfPlayers; i++)
        player[i].setPercentage(amountOfVariations);
}

void Variations::printUnusedDeck(){
    for(const Card &i : unusedCards)
        i.print();
}

void Variations::showVariant(){
    for (Card *i : variation)
        i->print();
    std::cout << endl;
}


