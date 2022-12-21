//
// Created by Joan Siasoyco on 9/21/22.
//

#ifndef PROJECT_1_RULESAUTOMATON_H
#define PROJECT_1_RULESAUTOMATON_H

#include "Automaton.h"

using namespace std;

class RulesAutomaton : public Automaton {
public:
    RulesAutomaton() : Automaton(TokenType::RULES){}

    void S0(const string& input){
        if (input[index] == 'R') {
            Continue();
            S1(input);
        } else {
            Serr();
        }
    }

    void S1(const string& input) {
        if (input[index] == 'u') {
            Continue();
            S2(input);
        } else {
            Serr();
        }
    }

    void S2(const string& input){
        if (input[index] == 'l') {
            Continue();
            S3(input);
        } else {
            Serr();
        }
    }

    void S3(const string& input) {
        if (input[index] == 'e') {
            Continue();
            S4(input);
        } else {
            Serr();
        }
    }

    void S4(const string& input){
        if (input[index] == 's') {
            Continue();
        } else {
            Serr();
        }
    }
};



#endif //PROJECT_1_RULESAUTOMATON_H
