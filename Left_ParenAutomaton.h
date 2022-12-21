//
// Created by Joan Siasoyco on 9/18/22.
//

#ifndef PROJECT_1_LEFT_PARENAUTOMATON_H
#define PROJECT_1_LEFT_PARENAUTOMATON_H


#include "Automaton.h"

class Left_ParenAutomaton : public Automaton {
public:
    Left_ParenAutomaton() : Automaton(TokenType::LEFT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input){
        if (input[index] == '(') {
            inputRead = 1;
        }
    }
};

#endif // COLONAUTOMATON_H

