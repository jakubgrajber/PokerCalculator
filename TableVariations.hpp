//
//  TableVariations.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 20/01/2022.
//

#ifndef TableVariations_hpp
#define TableVariations_hpp

#include <stdio.h>
#include "Table.hpp"
#include <vector>
#include <algorithm>

class Variations : public Table{
private:
    std::vector<Card *> variation;
    std::vector<int> positionInDeck;
    int sizeOfVariations;
    bool hasMoreVariations;
public:
    Variations(int amountOfPlayers, Deck &deck, int positionInDeck);
    
    
    void printUnusedDeck();
    
    void cardsAssignment(cmn::Stage stage);
    void cardsAssignment(int limit);
    void assignVariationCards();
    void clearVariationCards();
    void combine(std::vector <Card> &unusedCards, cmn::Stage stage);
    void setFamily(std::vector <Card> &unusedCards);
    void showVariant();
    int whichPositionChange(std::vector <Card> &unusedCards);
    void setWinner();
    void playersUpdate();
    void playersReset();
    
};


#endif /* TableVariations_hpp */
