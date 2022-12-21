#ifndef LEXER_H
#define LEXER_H
#pragma once
#include <fstream>
#include <iostream>
#include <list>
#include <vector>
#include "Automaton.h"
#include "Token.h"

//automatons!
#include "ColonAutomaton.h"
#include "ColonDashAutomaton.h"
#include "PeriodAutomaton.h"
#include "QueriesAutomaton.h"
#include "End_Of_FileAutomaton.h"
#include "AddAutomaton.h"
#include "CommaAutomaton.h"
#include "Left_ParenAutomaton.h"
#include "MultiplyAutomaton.h"
#include "PeriodAutomaton.h"
#include "Q_MarkAutomaton.h"
#include "Right_ParenAutomata.h"
#include "FactsAutomaton.h"
#include "IDAutomaton.h"
#include "CommentAutomaton.h"
#include "RulesAutomaton.h"
#include "SchemesAutomaton.h"
#include "StringAutomaton.h"

using namespace std;

class Lexer
{
private:
    std::vector<Automaton*> automata;
    std::vector<Token*> tokens;
    // TODO: add any other private methods here (if needed)

    Token *newToken;
    void CreateAutomata();
    Automaton *maxAutomaton;
public:
    Lexer(); //default
    ~Lexer(); //destroys automaton (machine) vectors AND the token vectors
    void Run(string& input); //runs the input

    // TODO: add other public methods here
    string printTokens(); //printing TOTAL tokens

    //cool friend function
    friend ostream& operator<<(ostream& os, Lexer& myLexer){
        os << myLexer.printTokens();
        return os;
    }

    vector<Token*> getTokens();
    //vector<Token*> getTokens()

};

#endif // LEXER_H
