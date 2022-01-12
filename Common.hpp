//
//  Common.hpp
//  PokerCalculator
//
//  Created by Jakub Grajber on 12/01/2022.
//

#ifndef Common_hpp
#define Common_hpp

#include <stdio.h>

namespace cmn {

enum Stage {pocket, flop, turn, river, end};
enum Mode {manual, random};
void stageToDomain(Stage stage, int &start, int &stop);
}

#endif /* Common_hpp */
