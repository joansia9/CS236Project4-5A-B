//
// Created by Joan Siasoyco on 9/22/22.

#ifndef PROJECT_1_IDAUTOMATON_H
#define PROJECT_1_IDAUTOMATON_H

#include "Automaton.h"
#include <cctype>
using namespace std;

/*
 * An identifier is a letter followed by zero or more letters or digits,
 * and is not a keyword (Schemes, Facts, Rules, Queries).
Note that for the input "1stPerson" the scanner would find two tokens:
 an 'undefined' token made from the character "1"
 and an 'identifier' token made from the characters "stPerson".
 */

class IdAutomaton : public Automaton {
public:
    IdAutomaton() : Automaton(TokenType::ID) {
        type = TokenType::ID;
    }
    void S0(const string& input) {
        if (isalpha(input[index])) {
            Continue();
            S1(input);
        }
    }

    void S1(const string& input) {
        if(isalpha(input[index])) {
            Continue();
            S1(input);
        } else if (isdigit(input[index])){
            Continue();
            S1(input);
        }
    }
};

#endif //PROJECT_1_IDAUTOMATON_H
