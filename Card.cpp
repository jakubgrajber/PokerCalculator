//
//  Card.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 29/12/2021.
//

#include "Card.hpp"

eColor charToColor(char input);
int charToValue(char input);

Card::Card(int value, eColor color){
    this->value = value;
    this->color = color;
}

//Card::Card(const Card &a){
//    this->value = a.value;
//    this->color = a.color;
//}

void Card::print() const{
    this->printValue();
    this->printColor();
}

void Card::printValue() const{
    if (value < 10)
        std::cout << "|" << value;
    else{
        switch (value)
        {
            case 10:
            {
                std::cout << "|T";
                break;
            }
            case 11:
            {
                std::cout << "|J";
                break;
            }
            case 12:
            {
                std::cout << "|Q";
                break;
            }
            case 13:
            {
                std::cout << "|K";
                break;
            }
            case 14:
            {
                std::cout << "|A";
                break;
            }
        }
    }
}

void Card::printColor() const{
    switch (color)
    {
        case 0:
            std::cout << "♠︎|";
            break;
        case 1:
            std::cout << "♣︎|";
            break;
        case 2:
            std::cout << "♦︎|";
            break;
        case 3:
            std::cout << "♥︎|";
            break;
    }
}

//Card& Card::operator=(Card &card){
//    this->value = card.value;
//    this->color = card.color;
//
//    return *this;
//}

Card& Card::operator=(std::string input){
    if (isdigit(input[0])) {
        value = input[0] - '0';
        color = charToColor(input[1]);
    }
    else{
        value = charToValue(input[0]);
        color = charToColor(input[1]);
    }
    
    return *this;
}

bool Card::operator==(const Card &a) const {
    return ((this->value == a.value) && (this->color == a.color));
}

bool Card::operator<(const Card &a) const {
    return (this->value < a.value);
}

bool Card::operator>(const Card &a) const {
    return (this->value > a.value);
}

eColor charToColor(char input){
    switch (input) {
        case 'S':
            return spade;
            break;
        case 'D':
            return diamond;
            break;
        case 'H':
            return heart;
            break;
        case 'C':
            return club;
            break;
        default:
            return spade;
            break;
    }
}

int charToValue(char input){
    switch (input) {
        case 'A':
            return 14;
            break;
        case 'K':
            return 13;
            break;
        case 'Q':
            return 12;
            break;
        case 'J':
            return 11;
            break;
        case 'T':
            return 10;
        default:
            return 0;
            break;
    }
}
