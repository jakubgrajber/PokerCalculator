//
//  Table.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 30/12/2021.
//

#include "Table.hpp"


Table::Table(int amountOfPlayers){
    if(amountOfPlayers>10)
        amountOfPlayers =10;
    
    player = new Player[amountOfPlayers];
    this->amountOfPlayers = amountOfPlayers;
    deckPosition = 0;
    stage = cmn::pocket;
}

void Table::playersUpdate(){
    for (int i = 0; i<amountOfPlayers; i++)
        player[i].hand.updateQualifiers(this->stage);
}

void Table::cardsInput(){
    switch (this->stage) {
        case cmn::pocket:
            pocketCardsInput();
            break;
        default:
            break;
    }
}

void Table::pocketCardsInput(){
    Card tempCard;
    bool isUnique;
    for(int i =0; i<amountOfPlayers; i++){
        std::cout << "Player " << i+1 <<": ";
        for (int j =0 ; j<2; j++){
            while (!isUnique) {
                tempCard = enterCardName();
                isUnique = true;
                for (int i =0; i<deckPosition; i++) {
                    if(tempCard == deck[i]){
                        isUnique = false;
                        break;
                    }
                }
                std::cout<<"This card is already chosen." << std::endl;
            }
            deck.card[deckPosition] = tempCard;
            deck[deckPosition++].print();
        }
    }
}

void Table::cardsAssignment(){
    int limit = 0;
    switch (this->stage) {
        case cmn::pocket:
            pocketAssignment();
            break;
        case cmn::flop:
            limit=3;
            break;
        case cmn::turn: case cmn::river:
            limit=1;
            break;
        default:
            break;
    }
    deckPosition++;
    for (int i=0;i<limit ; i++) {
        communityCards.push_back(&deck[deckPosition]);
        for (int i=0; i<amountOfPlayers; i++)
            player[i].hand.getCard(deck[deckPosition]);
        deckPosition++;
    }
}

void Table::pocketAssignment(){
    for (int i =0; i<amountOfPlayers; i++) {
        for (int j=0; j<2; j++)
            player[i].hand.getCard(deck[deckPosition++]);
    }
}

void Table::message(){
    switch (this->mode) {
        case cmn::random:
            messageRandomMode();
            break;
        case cmn::manual:
            messageManualMode();
            break;
        default:
            break;
    }
}

void Table::messageRandomMode(){
    switch (this->stage) {
        case cmn::pocket:
            std::cout << "Show the pocket cards. ";
            break;
        case cmn::flop:
            std::cout << "Show the flop. ";
            break;
        case cmn::turn:
            std::cout << "Show the turn. ";
            break;
        case cmn::river:
            std::cout << "Show the river. ";
            break;
        default:
            break;
    }
}

void Table::messageManualMode(){
    switch (this->stage) {
        case cmn::pocket:
            std::cout << "A K Q J T 9 8 7 6 5 4 3 2" << std::endl;
            std::cout << "♠︎ - S, ♣︎ - C, ♦︎ - D, ♥︎ - H" << std::endl;
            std::cout << "e.g. for |7♦︎| enter 7D" << std::endl;
            std::cout << "Enter pocket cards for each player. ";
            break;
        case cmn::flop:
            std::cout << "Enter flop cards into the game. ";
            break;
        case cmn::turn:
            std::cout << "Select turn card.  ";
            break;
        case cmn::river:
            std::cout << "Select river card.  ";
            break;
        default:
            break;
    }
}



void Table::print(){
for (int i =0; i<amountOfPlayers; i++) {
    std::cout << "Player " << i+1 << ": ";
    player[i].print();
    std::cout << std::endl;
    }
    std::cout << std::endl;
    
    if (communityCards.size()>0) {
        std::cout << "FLOP: ";
        for (int i=0; i<3; i++) {
            communityCards[i]->print();
        }
    }
    if (communityCards.size()>3) {
        std::cout << "  TURN: ";
        communityCards[3]->print();
    }
    if (communityCards.size()>4) {
        std::cout << "  RIVER: ";
        communityCards[4]->print();
    }
    std::cout << std::endl;
}

void Table::stageChange(){
    switch (stage) {
        case cmn::pocket:
            stage=cmn::flop;
            break;
        case cmn::flop:
            stage=cmn::turn;
            break;
        case cmn::turn:
            stage=cmn::river;
            break;
        case cmn::river:
            stage=cmn::end;
            break;
        default:
            break;
    }
}

std::string Table::enterCardName(){
    std::string input;
    while (!input.size()) {
        try {
            std::cin>>input;
            if (input.size()!=2)
                throw inputCardsError();
            for (int i =0; i<2; i++)
                if(!isdigit(input[i]))
                    input[i] = toupper(input[i]);
            if (input[0] != 'A' && input[0] != 'K' && input[0] != 'Q' && input[0] != 'J' && input[0] != 'T' && !isdigit(input[0]))
                throw inputCardsError();
            if (input[1] != 'S' && input[1] != 'C' && input[1] != 'H' && input[1] != 'D')
                throw inputCardsError();
        } catch (inputCardsError & error) {
            error.message();
            error.clearInput();
            input = "";
        }
    }
    return input;
}

Table::~Table(){
    delete [] player;
}



