//
// Created by Joan Siasoyco on 9/18/22.
//

#ifndef PROJECT_1_PERIODAUTOMATON_H
#define PROJECT_1_PERIODAUTOMATON_H


#include "Automaton.h"

class PeriodAutomaton : public Automaton {
public:
    PeriodAutomaton() : Automaton(TokenType::PERIOD) {}  // Call the base constructor

    void S0(const std::string& input){
        if (input[index] == '.') {
            inputRead = 1;
        }
    }
};

#endif //PROJECT_1_PERIODAUTOMATON_H
