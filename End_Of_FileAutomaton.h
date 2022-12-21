//
// Created by Joan Siasoyco on 9/21/22.
//

#ifndef PROJECT_1_END_OF_FILEAUTOMATON_H
#define PROJECT_1_END_OF_FILEAUTOMATON_H

#include "Automaton.h"

using namespace std;

class EOFAutomaton : public Automaton {
public:
    EOFAutomaton() : Automaton(TokenType::END_OF_FILE){
        type = TokenType::END_OF_FILE;
    }

    void S0(const string& input){
        return;
    }
};


#endif //PROJECT_1_END_OF_FILEAUTOMATON_H
