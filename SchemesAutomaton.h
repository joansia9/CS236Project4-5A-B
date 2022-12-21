//
// Created by Joan Siasoyco on 9/22/22.
//

#ifndef PROJECT_1_SCHEMESAUTOMATON_H
#define PROJECT_1_SCHEMESAUTOMATON_H
#include "Automaton.h"
using namespace std;

class SchemesAutomaton : public Automaton {
public:
    SchemesAutomaton() : Automaton(TokenType::SCHEMES){}

    void S0(const string& input){
        if (input[index] == 'S') {
            Continue();
            S1(input);
        } else {
            Serr();
        }
    }

    void S1(const string& input) {
        if (input[index] == 'c') {
            Continue();
            S2(input);
        } else {
            Serr();
        }
    }
    void S2(const string& input){
        if (input[index] == 'h') {
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
    void S4(const string& input) {
        if (input[index] == 'm') {
            Continue();
            S5(input);
        } else {
            Serr();
        }
    }
    void S5(const string& input){
        if (input[index] == 'e') {
            Continue();
            S6(input);
        } else {
            Serr();
        }
    }
    void S6(const string& input){
        if (input[index] == 's') {
            Continue();
        } else {
            Serr();
        }
    }
};
#endif //PROJECT_1_SCHEMESAUTOMATON_H
