//
//  Common.cpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 12/01/2022.
//

#include "Common.hpp"
using namespace::cmn;

void cmn::stageToDomain(Stage stage, int &start, int &stop){
    switch (stage) {
        case pocket:
            start = 0;
            stop = 1;
            break;
        case flop:
            start = 2;
            stop = 4;
            break;
        case turn:
            start = stop = 5;
            break;
        case river:
            start = stop = 6;
            break;
        default:
            break;
    }
}
