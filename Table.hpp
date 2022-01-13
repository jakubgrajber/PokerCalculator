//
//  Table.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#ifndef Table_hpp
#define Table_hpp

#include <memory>
#include "Player.hpp"
#include "Deck.hpp"
#include <vector>
#include "Common.hpp"
#include "exc_inputCards.h"
#include <string>




class Table{
private:
    Player *player;
    Deck deck;
    std::vector <const Card*> communityCards;
    
    cmn::Mode mode;
    cmn::Stage stage;
    
    int amountOfPlayers;
    int deckPosition;
    
    void pocketAssignment();
    void pocketCardsInput();
    void messageRandomMode();
    void messageManualMode();
    std::string enterCardName();
public:
    friend class Game;
    
    Table(int amountOfPlayers);
    
    void cardsInput();
    void cardsAssignment();
    void playersUpdate();
    void message();
    void stageChange();
    
    void print();
    ~Table();
};

#endif /* Table_hpp */
