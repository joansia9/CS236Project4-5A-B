//
// Created by Joan Siasoyco on 9/18/22.
//

#ifndef PROJECT_1_RIGHT_PARENAUTOMATA_H
#define PROJECT_1_RIGHT_PARENAUTOMATA_H


#include "Automaton.h"

class Right_ParenAutomaton : public Automaton
{
public:
    Right_ParenAutomaton() : Automaton(TokenType::RIGHT_PAREN) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // COLONAUTOMATON_H