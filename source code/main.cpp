//
//  main.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 28/12/2021.
//

#include <iostream>
#include <cstdlib>
#include "Game.hpp"
#include "exc_mainMenu.h"
#include <vector>
#include <string>

using std::vector;
using std::cout;
using std::endl;
using std::cin;

void mainMenu();
void randomMode();
void manualMode();
void newLine(int value);
void getNumOfPlayers(int &x);
int getSelection(int min, int max);


int main() {
    mainMenu();
    return 0;
}

void mainMenu(){
    bool isMenuActive = true;
    int selector;
    
    cout << "Welcome to the Poker Calculator!" << endl;
    
    while (isMenuActive) {
        selector =0;
        cout << "Please select a mode: " << endl;
        cout << "1. Randomly generated tables." << endl;
        cout << "2. Manual data input." << endl;
        cout << "3. QUIT" << endl;
        
        try {
            selector = getSelection(1,3);
        } catch (domainError & de) {
            de.message();
        } catch (inputError & ie){
            ie.message();
            ie.clearInput();
        }
        
        switch (selector) {
            case 1:
            {
                randomMode();
                break;
            }
            case 2:
            {
                manualMode();
                break;
            }
            case 3:
            {
                return;
            }
        }
        
        selector = 0;
        while(true)
        {
            cout << "Do you want to try again?" << endl;
            cout << "1. Yes" << endl;
            cout << "2. No. QUIT" << endl;
            try {
                selector = getSelection(1, 2);
            } catch (domainError &de) {
                de.message();
                de.clearInput();
            } catch (inputError &ie){
                ie.message();
                ie.clearInput();
            }
            if (selector == 1)
                break;
            if (selector == 2)
                return;
        }
    }
}

void randomMode(){
    newLine(1);
    int numOfPlayers;
    getNumOfPlayers(numOfPlayers);
    
    cin.ignore();
    Table mainTable(numOfPlayers);
    Game randGame(&mainTable);
    randGame.randomMode();
    
    newLine(1);
}
void manualMode(){
    newLine(1);
    int numOfPlayers;
    getNumOfPlayers(numOfPlayers);

    cin.ignore();
    Table mainTable(numOfPlayers);
    Game manualGame(&mainTable);
    manualGame.manualMode();
}

void newLine(int amount){
    for (int i=0; i<amount; i++)
        cout << "\n";
    cout << "-------------------------------------------------------------------------------------------" << endl;
    for (int i=0; i<amount; i++)
        cout << "\n";
}

void getNumOfPlayers(int &numOfPlayers){
    numOfPlayers = 0;
    
    while (numOfPlayers==0) {
        cout << "Enter the number of players (up to 10): ";
        try {
            numOfPlayers = getSelection(2, 10);
        } catch (domainError & de) {
            de.message();
            de.clearInput();
        } catch (inputError & ie){
            ie.message();
            ie.clearInput();
        }
    }
}

int getSelection(int min, int max){
    int selector;
    cin >> selector;
    if (!cin.good())
        throw inputError();
    if (!(selector >= min && selector <= max))
        throw domainError(selector);
    return selector;
}
