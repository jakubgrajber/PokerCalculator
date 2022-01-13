//
//  exc_inputCards.h
//  PokerCalculator
//
//  Created by Jakub Grajber on 13/01/2022.
//

#ifndef exc_inputCards_h
#define exc_inputCards_h

using std::cout;
using std::endl;
using std::cin;

class inputCardsError {
public:
    inputCardsError(){}
    void message();
    void clearInput();
};

inline void inputCardsError::message(){
    cout << "\nInput error - you've entered an incorrect formula.\n" <<endl;
}

inline void inputCardsError::clearInput(){
    cin.clear();
    cin.ignore(INT_MAX, '\n');
}

#endif /* exc_inputCards_h */
