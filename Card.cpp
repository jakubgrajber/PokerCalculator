//
//  Card.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 29/12/2021.
//

#include "Card.hpp"


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
        {
            std::cout << "♠︎|";
            break;
        }
        case 1:
        {
            std::cout << "♣︎|";
            break;
        }
        case 2:
        {
            std::cout << "♦︎|";
            break;
        }
        case 3:
        {
            std::cout << "♥︎|";
            break;
        }
        case error: {
            std::cout << "color error";
            break;
        }
    }
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
