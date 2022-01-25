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
#include <iomanip>

class Table{
private:
    Player *player;
    Deck deck;
    std::vector <const Card*> communityCards;
    
    int amountOfPlayers;
    int deckPosition;

    cmn::Mode mode;
    cmn::Stage stage;
    
    std::vector <Card> unusedCards;
    
    void pocketCardsInput();
    void uniqueCardInput();
    std::string enterCardName();
    void pocketAssignment();
    virtual void setTies(int firstIndex);
    void messageRandomMode();
    void messageManualMode();
public:
    friend class Game;
    friend class Variations;
    
    Table(int amountOfPlayers);
    Table(int amountOfPlayers, Deck &deck, int positionInDeck);
    
    void cardsInput();
    virtual void cardsAssignment();
    virtual void playersUpdate();
    virtual void setWinner();
    void getWinningPercentage(Player players[]);
    void setUnusedDeck();
    void stageChange();
    void stageChange(cmn::Stage &stage);
    void message();
    void print();
    ~Table();
};

#endif /* Table_hpp */
