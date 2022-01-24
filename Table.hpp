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
protected:
    int amountOfPlayers;
    int deckPosition;
    Deck deck;
    cmn::Mode mode;
    cmn::Stage stage;
    std::vector <const Card*> communityCards;
    Player *player;
    std::vector <Card> unusedCards;
private:
    
    void pocketAssignment();
    void pocketCardsInput();
    void messageRandomMode();
    void messageManualMode();
    std::string enterCardName();
    void uniqueCardInput();
    virtual void setTies(int firstIndex);
public:
    friend class Game;
    friend class Variations;
    Table(int amountOfPlayers);
    Table(int amountOfPlayers, Deck &deck, int positionInDeck);
    
    void cardsInput();
    virtual void cardsAssignment();
    virtual void playersUpdate();
    void message();
    void stageChange();
    void stageChange(cmn::Stage &stage);
    virtual void setWinner();
    void setUnusedDeck();
    void print();
    void getWinningPercentage(Player players[]);
    ~Table();
};

#endif /* Table_hpp */
