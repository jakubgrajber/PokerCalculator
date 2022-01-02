//
//  exc_mainMenu.h
//  PokerCalculator
//
//  Created by Jakub Grajber on 02/01/2022.
//

#ifndef exc_mainMenu_h
#define exc_mainMenu_h
#include <iostream>

using std::cout;
using std::endl;
using std::cin;

class inputError {
public:
    inputError(){}
    void message();
    void clearInput();
};

inline void inputError::message(){
    cout << "\nInput error - you're not supposed to use characters.\n" <<endl;
}

void inputError::clearInput(){
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

class domainError {
private:
    int value;
public:
    domainError(int x = 0) : value(x){}
    void message();
    void clearInput();
};

inline void domainError::message(){
    cout << "\nInput error - invalid value: " << value <<endl;
    cout << endl;
}

void domainError::clearInput(){
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}


#endif /* exc_mainMenu_h */
