//
// Created by Joan Siasoyco on 9/18/22.
//

#ifndef PROJECT_1_ADDAUTOMATON_H
#define PROJECT_1_ADDAUTOMATON_H


#include "Automaton.h"

class AddAutomaton : public Automaton
{
public:
    AddAutomaton() : Automaton(TokenType::ADD) {}  // Call the base constructor

    void S0(const std::string& input){
        if (input[index] == '+') {
            inputRead = 1;
        }
    }
};

#endif // COLONAUTOMATON_H

