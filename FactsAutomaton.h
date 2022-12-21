//
// Created by Joan Siasoyco on 9/21/22.
//

#ifndef PROJECT_1_FACTSAUTOMATON_H
#define PROJECT_1_FACTSAUTOMATON_H

#include "Automaton.h"

using namespace std;
class FactsAutomaton : public Automaton {
public:
    FactsAutomaton() : Automaton(TokenType::FACTS){}

    void S0(const string& input){
        if (input[index] == 'F') {
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }

    void S1(const string& input) {
        if (input[index] == 'a') {
            Continue();
            S2(input);
        } else {
            Serr();
        }
    }
    void S2(const string& input){
        if (input[index] == 'c') {
            Continue();
            S3(input);
        } else {
            Serr();
        }
    }
    void S3(const string& input) {
        if (input[index] == 't') {
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


#endif //PROJECT_1_FACTSAUTOMATON_H
