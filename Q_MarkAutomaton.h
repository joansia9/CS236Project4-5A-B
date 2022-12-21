//
// Created by Joan Siasoyco on 9/18/22.
//

#ifndef PROJECT_1_Q_MARKAUTOMATON_H
#define PROJECT_1_Q_MARKAUTOMATON_H


#include "Automaton.h"

class Q_MarkAutomaton : public Automaton
{
public:
    Q_MarkAutomaton() : Automaton(TokenType::Q_MARK) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // COLONAUTOMATON_H


