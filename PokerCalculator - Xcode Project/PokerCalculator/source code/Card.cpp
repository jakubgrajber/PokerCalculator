//
//  Card.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 29/12/2021.
//

#include "Card.hpp"

eColor charToColor(char input);
char charToValue(char input);
char valueToChar(int value);
std::string colorToChar(eColor input);

Card::Card(int value, eColor color){
    this->value = value;
    this->color = color;
}

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
        case 1:
            std::cout << "♠︎|";
            break;
        case 2:
            std::cout << "♣︎|";
            break;
        case 3:
            std::cout << "♦︎|";
            break;
        case 4:
            std::cout << "♥︎|";
            break;
        default:
            break;
    }
}

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

bool Card::operator!=(const Card &a) const{
    return !this->operator==(a);
}

bool Card::operator>(const Card &a) const {
    return (this->value > a.value);
}

bool Card::operator<(const Card &a) const {
    return (this->value < a.value);
}

ostream & operator<<(ostream &os, const Card &card){
    os << "|" << valueToChar(card.value) << colorToChar(card.color) << "|";
    return os;
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

char charToValue(char input){
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

char valueToChar(int value){
    if (value <10) {
        return value + '0';
    }
    else{
        switch (value) {
            case 10:
                return 'T';
                break;
            case 11:
                return 'J';
                break;
            case 12:
                return 'Q';
                break;
            case 13:
                return 'K';
                break;
            case 14:
                return 'A';
                break;
            default:
                return ' ';
                break;
        }
    }
}

std::string colorToChar(eColor color){
    switch (color) {
        case spade:
            return "♠︎";
            break;
        case heart:
            return "♥︎";
            break;
        case diamond:
            return "♦︎";
            break;
        case club:
            return "♣︎";
            break;
        default:
            return " ";
            break;
    }
}
