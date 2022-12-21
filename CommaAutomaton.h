//
// Created by Joan Siasoyco on 9/18/22.
//

#ifndef PROJECT_1_COMMAAUTOMATON_H
#define PROJECT_1_COMMAAUTOMATON_H

#include "Automaton.h"

/*
 * A line comment starts with a hash character (#)
 * and ends at the end of the line or end of the file.
 */


class CommaAutomaton : public Automaton
{
public:
    CommaAutomaton() : Automaton(TokenType::COMMA) {} //Call the base constructor

    void S0(const std::string& input){
        if (input[index] == ',') {
            inputRead = 1;
        }
    }
};


#endif //PROJECT_1_COMMAAUTOMATON_H
