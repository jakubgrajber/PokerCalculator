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

void Table::cardsInput(){
    int limit =0;
    switch (this->stage) {
        case cmn::pocket:
            pocketCardsInput();
            return;
        case cmn::flop:
            limit = 3;
            break;
        case cmn::turn: case cmn::river:
            limit =1;
            break;
        default:
            return;
    }
    for (int i=0; i<limit; i++)
        uniqueCardInput();
    std::cin.ignore(INT_MAX, '\n');
}

void Table::pocketCardsInput(){
    for(int i =0; i<amountOfPlayers; i++){
        std::cout << "\nPlayer " << i+1 <<": ";
        for (int j =0 ; j<2; j++)
            uniqueCardInput();
        std::cin.ignore(INT_MAX, '\n');
    }
}
void Table::uniqueCardInput(){
    Card tempCard;
    bool isUnique = false;
    while (!isUnique) {
        tempCard = enterCardName();;
        isUnique = true;
        for (int i = 0; i<deckPosition; i++) {
            if (tempCard == deck[i]) {
                isUnique = false;
                std::cout << tempCard << " is already chosen." << std::endl;
                break;
            }
        }
    }
    deck.card[deckPosition++] = tempCard;
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
            if (input[0] - '0' < 2)
                throw inputCardsError();
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

void Table::cardsAssignment(){
    int limit = 0;
    switch (this->stage) {
        case cmn::pocket:
            if (mode == cmn::manual)
                deckPosition =0;
            pocketAssignment();
            break;
        case cmn::flop:
            if (mode == cmn::manual)
                deckPosition = amountOfPlayers*2;
            limit=3;
            break;
        case cmn::turn:
            if (mode == cmn::manual)
                deckPosition = amountOfPlayers*2 + 3;
            limit=1;
            break;
        case cmn::river:
            if (mode == cmn::manual)
                deckPosition =amountOfPlayers*2 +4;
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

void Table::playersUpdate(){
    for (int i = 0; i<amountOfPlayers; i++)
        player[i].hand.updateQualifiers(this->stage);
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
            std::cout << "\nA K Q J T 9 8 7 6 5 4 3 2" << std::endl;
            std::cout << "♠︎ - S, ♣︎ - C, ♦︎ - D, ♥︎ - H" << std::endl;
            std::cout << "\ne.g. for |7♦︎| enter 7D or 7d" << std::endl;
            std::cout << "Enter pocket cards for each player. " << std::endl;
            break;
        case cmn::flop:
            std::cout << "\nEnter flop cards into the game. " << std::endl;
            break;
        case cmn::turn:
            std::cout << "\nSelect turn card.  " << std::endl;
            break;
        case cmn::river:
            std::cout << "\nSelect river card.  " << std::endl;
            break;
        default:
            break;
    }
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

void Table::print(){
    std::cout << std::endl;
for (int i =0; i<amountOfPlayers; i++) {
    std::cout << "Player " << i+1 << ": ";
    if (stage == cmn::river)
        player[i].hand.printBestFive();
    else
        player[i].hand.print();
    std::cout << std::endl;
    }
    
    if (communityCards.size()>0) {
        std::cout << "\nFLOP: ";
        for (int i=0; i<3; i++)
            communityCards[i]->print();
    }
    if (communityCards.size()>3) {
        std::cout << "  TURN: ";
        communityCards[3]->print();
    }
    if (communityCards.size()>4) {
        std::cout << "  RIVER: ";
        communityCards[4]->print();
    }
    if (communityCards.size()>0)
        std::cout<<std::endl;
}

void Table::setWinner(){
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
                    tie = false;
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
}

void Table::setTies(int firstIndex){
    vector<int> tiedIndex;
    tiedIndex.push_back(firstIndex);
    
    for (int i =firstIndex+1; i<amountOfPlayers; i++) {
        if (player[i].hand.value == player[firstIndex].hand.value)
            for (int j =0; j<5; j++){
                if (player[i].hand.bestFive[j]->value != player[firstIndex].hand.bestFive[j]->value) {
                    break;
                }
                if (j==4)
                    tiedIndex.push_back(i);
            }
    }
    std::cout<< "Players with numbers ";
    for(int i: tiedIndex){
        std::cout<< i+1;
        if (i != *(end(tiedIndex)-1))
            std::cout<< ", ";
    }
    std::cout << " tied." << std::endl;
    
}

Table::~Table(){
    delete [] player;
}



