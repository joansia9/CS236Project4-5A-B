#ifndef AUTOMATON_H
#define AUTOMATON_H
#include "Token.h"

//PeriodAutomation.h (child)
//type = PERDIOD;

//commaAutomaton.h (child)
//type = COMMA;

class Automaton
{
protected:
    //protected is private but for parent classes
    size_t index = 0;
    int newLines = 0;  //correct
    TokenType type; //correct


public:
    int inputRead = 0; //correct
    Automaton() : Automaton(TokenType::UNDEFINED) {}

    Automaton(TokenType type) { this->type = type; } //correct

    virtual ~Automaton() = default;
    // Start the automaton and return the number of characters read
    //   read == 0 indicates the input was rejected
    //   read  > 0 indicates the input was accepted

    int Start(const std::string& input) {
        newLines = 0; //should this be here?
        inputRead = 0; //correct
        index = 0; // clear this value
        S0(input); //correct
        return inputRead; //correct
    }

    // Every subclass must define this method
    virtual void S0(const std::string& input) = 0;


    Token* CreateToken(std::string input, int lineNumber) {
        return new Token(type, input, lineNumber); }

    int NewLinesRead() const { return newLines; }

    void Serr() {
        inputRead = 0; //reject state
    }

    //bools
    bool endFlag = false;
    bool hasMultiline = false;
    int multilineInc = 0;

    //helper functions (for reading purposes)
    void Continue(){
        index++;
        inputRead++;
    }
};

#endif // AUTOMATON_H

