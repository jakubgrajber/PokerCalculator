//
//  Game.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 01/01/2022.
//

#include "Game.hpp"

void waitForUser();

Game::Game(Table *table){
    this->copyTable = table;
}

void Game::setup(){
    std::cout << "Show the pocket cards. ";
    waitForUser();
    copyTable->pocketAssignment();
    copyTable->pocket();
    this->draw();
    
    std::cout << "Show the flop. ";
    waitForUser();
    copyTable->flopAssignment();
    copyTable->flop();
    this->draw();
    
    std::cout << "Show the turn. ";
    waitForUser();
    copyTable->turnRiverAssignment();
    copyTable->turn();
    this->draw();
    
    std::cout << "Show the river. ";
    waitForUser();
    copyTable->turnRiverAssignment();
    copyTable->river();
    this->draw();
    
    waitForUser();
}

void Game::draw(){
    copyTable->print();
}

void waitForUser(){
    do{
        std::cout << "Press enter to continue..." << std::endl;
     } while (std::cin.get() != '\n');
}
