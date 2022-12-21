//
// Created by Joan Siasoyco on 9/17/22.
//
#include "Lexer.h"

using namespace std;

//constructors
Lexer::Lexer() {
    CreateAutomata(); //given
}

//destructor
Lexer::~Lexer() {
    // Deallocate tokens memeory
    //clears tokens
    for (size_t i = 0; i < tokens.size(); i++) {
        delete tokens.at(i); //remember to delete elements and pointer
    }
    tokens.clear();
    //clears automata
    for (size_t i = 0; i < automata.size(); i++) {
        delete automata.at(i);
    }
    automata.clear();
}

//pushing back the automatas into vector of automatas
void Lexer::CreateAutomata() {
    automata.push_back(new ColonAutomaton());
    automata.push_back(new ColonDashAutomaton());
    // TODO: Add the other needed automata here
    automata.push_back(new AddAutomaton());
    automata.push_back(new CommaAutomaton());
    automata.push_back(new Left_ParenAutomaton());
    automata.push_back(new MultiplyAutomaton());
    automata.push_back(new PeriodAutomaton());
    automata.push_back(new Q_MarkAutomaton());
    automata.push_back(new Right_ParenAutomaton());
    automata.push_back(new FactsAutomaton());
    automata.push_back(new QueriesAutomaton());
    automata.push_back(new RulesAutomaton());
    automata.push_back(new SchemesAutomaton());
    automata.push_back(new IdAutomaton()); //remember: order this in the end bc itll override facts queries rules etc.
    automata.push_back(new StringAutomaton());
    automata.push_back(new CommentAutomaton());
    automata.push_back(new EOFAutomaton());
}

//TODO: PSEUDOCODE for run function
/*
// set lineNumber to 1
//While there are more characters to tokenize
// loop on input.size() > 0 {
//set MaxRead to 0
//set maxAutomaton to the first automaton in automata

// TODO: you need to handle whitespace inbetween tokens

// Here is the "Parallel" part of the algorithm
//  Each automaton runs with the same input
//foreach automaton in automata {
//inputRead = automaton.start(input)
//if(inputRead > maxRead) {
//setmaxRead to inputRead
//setmaxAutomaton to automaton
//}
//}
//Here is the "Max" part of the algorithm
//if maxRead>0 {
//set newToken to maxAutomaton.CreateToken(...)
//increment lineNumber by maxAutomaton.NewLinesRead()
//add newToken to collection of all tokens
//}
//No automaton accepted input
//Create single character undefined token
//else {
//set maxRead to 1
//set newToken to a new undefined Token
//(with first character of input
//add newToken to collection of all tokens
//}
//Update 'input' by removing character read to create Token remove maxRead characters from input
//}
//}
 */

void Lexer::Run(std::string& input) {
    int lineNum = 1;

    if (input.empty()) {
        newToken = new Token(TokenType::END_OF_FILE, "", lineNum);
        tokens.push_back(newToken);
        return;
    }

// Parallel and Max Alg
    while (input.size() > 0) {
        int maxRead = 0;
        maxAutomaton = automata.at(0);


        // white space
        /*
         * example:
         *
         * hello
         */
        while (isspace(input.at(0))) { //if there is a whitespace in the beginning
            if (input.at(0) == '\n') { //if the first line is an empty line
                lineNum++; //increments line num if we see a new line
            }
            input.erase(0,1); //this will remove the whitespace

            // Check for an empty file
            /*
         * example:
         *
         */
            if (input.empty()) { //if the input is empty
                newToken = new Token(TokenType::END_OF_FILE, "", lineNum);
                tokens.push_back(newToken);
                return;
            }
        }

        // finds the right automata for the input
        for (unsigned int i = 0; i < automata.size(); i++) {  //goes through each automata
            int inputRead = automata.at(i)->Start(input); //increments inputRead

            // Figure out the max automata
            if (inputRead > maxRead) { //if the inputRead > maxRead set maxRead as inputRead
                maxRead = inputRead;
                maxAutomaton = automata.at(i);
            }
        }

        // Check to see if String or Comment are never terminated
        if (maxAutomaton->endFlag == true) {
            maxRead += maxAutomaton->inputRead; //maxread has to be incremented
            //set new token undefined if string or comment are terminated
            newToken = new Token(TokenType::UNDEFINED, input.substr(0, maxRead), lineNum);
            tokens.push_back(newToken);
            //if here is more than 1 line
            if (maxAutomaton->hasMultiline) {
                lineNum += maxAutomaton->multilineInc;
            }
            //set new token as EOF
            newToken = new Token(TokenType::END_OF_FILE, "", lineNum);
            tokens.push_back(newToken);
            return;
        }

        // MAX ALGORITHM
        if (maxRead > 0) {
            string currLine = input.substr(0, maxRead);
            newToken = maxAutomaton->CreateToken(currLine, lineNum);
            //increment lineNumber by maxAutomaton.NewLinesRead()
            lineNum += maxAutomaton->NewLinesRead();
        } else {
            maxRead = 1;
            string currLine = input.substr(0, maxRead);
            //set newToken to a new undefined Token
            newToken = new Token(TokenType::UNDEFINED, currLine, lineNum);
        }
        if (maxAutomaton->hasMultiline) {
            lineNum += maxAutomaton->multilineInc;
        }

        // Update input by removing characters read to create Token
        tokens.push_back(newToken);
        input.erase(0, maxRead);
    }
}

//print tokens
string Lexer::printTokens(){
    ostringstream save;
    string output= ""; //initialized

    int totalNumOfTokens = tokens.size();

    /*
    while(!tokens.empty()){
        save << tokens.front()->toString()<< endl;
        tokens.erase(tokens.begin());
    }
     */

    for (size_t i = 0; i < tokens.size(); i++){
        save << tokens.at(i)->toString();
    }

    save << "Total Tokens = " << totalNumOfTokens;
    output = save.str();
    return output;
}

//getters
vector<Token*>Lexer::getTokens() {
    return tokens;
}

//notes!
/*
 // TODO: convert this pseudo-code with the algorithm into actual C++ code
    //set line number to 1
    int lineNum = 1;
    //while there are more characters to tokenize
    while (input.size() > 0) { //CORRECT
        //set max read to 0
        int maxRead = 0;
        //set max Automaton to the first automaton in automata
        maxAutomaton = automata.at(0);
        //you need to handle whitespace in between tokens
        while(isspace(input.at(0))){ //if there is a white space at the first character of input
            if(input.at(0) == '\n') {// whitespace
                lineNum++; //continues
            } //CORRECT
            input.erase(0,1); //remove whitespace
        } //here is the "Parallel" part of the algorithm
        //Each automaton runs with the same input fo each automaton in automata {
        for (unsigned int i = 0; i < automata.size(); i++) {
            //input Read = automaton to start
            int inputRead = automata.at(i)->Start(input); //remember me: syntax!
            if (inputRead > maxRead) {
                //set maxRead to inputRead
                maxRead = inputRead;
                //set maxAutomaton to automaton
                maxAutomaton = automata.at(i);
            }
        }
        if (maxRead > 0){ //Here is the "Max" part of the algorithm
            //string tokenString = input.substr(0, maxRead); //assign tokenString to entire string
            //input.erase(0,maxRead);
            //Token *newToken = maxAutomaton->CreateToken(tokenString, lineNum);
            //increment lineNumber by maxAutomaton.NewLinesRead()
            newToken = maxAutomaton->CreateToken(input.substr(0, maxRead), lineNum);
            lineNum += maxAutomaton->NewLinesRead(); //declared in Automaton.h
            //add newToken to collection of all tokens
            //tokens.push_back(newToken); //(because it is a vector)
        } else { //No automaton accepted input so create single character undefined token
            //set maxRead to 1
            maxRead = 1;
            //FIXME: set newTokens to a new undefined Token (with first character of input)
            newToken = new Token(TokenType::UNDEFINED, (input.substr(0, maxRead)), lineNum);
            //add newToken to collection of all tokens
            //tokens.push_back(newToken);
        } //correct up to here
        //update 'input' by removing characters read to create token
        // remove maxRead characters from input
        tokens.push_back(newToken);
        input.erase(0, maxRead);
    }
    newToken = new Token(TokenType::END_OF_FILE, "", lineNum);
    tokens.push_back(newToken);
}
 */
