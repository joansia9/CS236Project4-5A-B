//
// Created by Joan Siasoyco on 9/21/22.
//

#ifndef PROJECT_1_QUERIESAUTOMATON_H
#define PROJECT_1_QUERIESAUTOMATON_H

#include "Automaton.h"
using namespace std;
class QueriesAutomaton : public Automaton {
public:
    QueriesAutomaton() : Automaton(TokenType::QUERIES){}

    void S0 (const string& input){
        if (input[index] == 'Q') {
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }
    void S1(const string& input){
        if (input[index] == 'u') {
            inputRead++;
            index++;
            S2(input);
        } else {
            Serr();
        }
    }
    void S2(const string& input){
        if (input[index] == 'e') {
            inputRead++;
            index++;
            S3(input);
        } else {
            Serr();
        }
    }
    void S3(const string& input){
        if (input[index] == 'r') {
            inputRead++;
            index++;
            S4(input);
        } else {
            Serr();
        }
    }
    void S4(const string& input){
        if (input[index] == 'i') {
            inputRead++;
            index++;
            S5(input);
        } else {
            Serr();
        }
    }
    void S5(const string& input){
        if (input[index] == 'e') {
            inputRead++;
            index++;
            S6(input);
        } else {
            Serr();
        }
    }


    void S6(const string& input) {
        if (input[index] == 's') {
            inputRead++;
            index++;
        } else {
            Serr();
        }
    }

};


#endif //PROJECT_1_QUERIESAUTOMATON_H
