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
    int amountOfVariations;
    
    void setTies(int firstIndex);
public:
    Variations(int amountOfPlayers, Deck &deck, int positionInDeck);
    
    void combine(std::vector <Card> &unusedCards, cmn::Stage stage);
    void setFamily(std::vector <Card> &unusedCards);
    int whichPositionChange(std::vector <Card> &unusedCards);
    
    void cardsAssignment(cmn::Stage stage);
    void cardsAssignment(int limit);
    void assignVariationCards();
    void clearVariationCards();
    void setWinner();
    void playersUpdate();
    void playersReset();
    void setWinningPercentage();
    void printUnusedDeck();
    void showVariant();
    
    int getAmountOfVariations(){return amountOfVariations;}
};


#endif /* TableVariations_hpp */
