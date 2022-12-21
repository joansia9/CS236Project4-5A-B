//
// Created by Joan Siasoyco on 9/18/22.
//

#ifndef PROJECT_1_MULTIPLYAUTOMATON_H
#define PROJECT_1_MULTIPLYAUTOMATON_H


#include "Automaton.h"

class MultiplyAutomaton : public Automaton
{
public:
    MultiplyAutomaton() : Automaton(TokenType::MULTIPLY) {}  // Call the base constructor

    void S0(const std::string& input){
        if (input[index] == '*') {
            inputRead = 1;
        }
        else {
            Serr();
        }
    }
};

#endif // COLONAUTOMATON_H


