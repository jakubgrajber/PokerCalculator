//
//  Card.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 29/12/2021.
//

#ifndef Card_hpp
#define Card_hpp

#include <stdio.h>
#include <iostream>
#include <string>

using std::ostream;

enum eColor {none, spade, club, diamond, heart};

class Card{
private:
    int value;
    eColor color;
public:
    friend class Hand;
    friend class Table;
    Card(){};
    Card(int value, eColor color);
    
    void print() const;
    void printValue() const;
    void printColor() const;

    Card& operator=(std::string input);
    bool operator==(const Card &a) const;
    bool operator!=(const Card &a) const;
    bool operator>(const Card &a) const;
    bool operator<(const Card &a) const;
    
    friend ostream & operator<<(ostream &os, const Card &a);
    
    int getValue() const{return value;}
    eColor getColor() const{return color;}
    
    ~Card(){};
};

#endif /* Card_hpp */
