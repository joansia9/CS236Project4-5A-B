//
// Created by Joan Siasoyco on 9/22/22.
//

#ifndef PROJECT_1_STRINGAUTOMATON_H
#define PROJECT_1_STRINGAUTOMATON_H
    // std::cin, std::cout
#include <iostream>
#include <sstream>
#include "Automaton.h"
using namespace std;

/*
 * A string is a sequence of characters enclosed in single quotes.
 * White space (space, tab, etc.) is not skipped when inside a string.
 * Two adjacent single quotes within a string denote an apostrophe.
 * The line number for a string token is the line where the string begins.
 * If a string is not terminated
 * (end of file is encountered before the end of the string),
 * the token becomes an undefined token.

The 'value' of a token printed to the output is the sequence of input characters that form the token.
 For a string token this means that two adjacent single quotes in the input are
 printed as two adjacent single quotes in the output.
 (In other words,
 don't convert two adjacent single quotes
 in a string to just one apostrophe in the output.)

 maybe get a next()
 void next() {
        if (curr() == '\n')
        newLinesRead++;
        inputRead++;
        index++;
    }

    char curr() {
        if (endOfFile())
            throw "Attempting to read past the file";
        return input.at(index);
    }

 */

class StringAutomaton : public Automaton {
public:
    StringAutomaton() : Automaton(TokenType::STRING){}

    void S0(const string& input) {
        multilineInc = 0; //to increment multiple lines
        if (input[index] == '\'') { //match '
            inputRead++;
            index++;
            S1(input);
        } else {
            Serr();
        }
    }

//'joan'
    void S1(const string& input){
        size_t sizeOfString = input.size();
        if (index >= sizeOfString) { //if this isn't the last input value
            endFlag = true;
            return;
        } else if (input[index] == '\'') { // if find another '
            Continue();
            S2(input); //go to accept state
        } else {
            //checks if there are multiple lines
            if (input.at(inputRead) == '\n') {
                hasMultiline = true;
                multilineInc++;
            }
            Continue();
            S1(input); //stay in input 1
        }
        /*
         * To check for newlines inside strings:
         * if input[index] == "\n"
         *    newline++
         *    do something (move to new state?)
         *
         */
    }

    void S2(const string& input) {
        if (input[index] == '\'') { //if you find another '
            Continue();//continue AND
            S1(input); //go back to S1
        } else {
            return; //or else return
        }
    }
};
#endif //PROJECT_1_STRINGAUTOMATON_H

