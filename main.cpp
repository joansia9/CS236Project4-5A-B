#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    //why is the check not workin?

     string file = argv[1];
     ifstream input(file);

     stringstream in;

    input.open(file);
    in << input.rdbuf();
    input.close();

    string myFile = in.str();

    //DIAGRAM
    //LEXER -> tokens -> PARSER -> datalog program -> INTERPRETER (Rule evaluation -> Query evaluation)

    //runs the lexer (project 1)
    //PURPOSE: scanner that CREATED tokens out of characters inputed from a file
    Lexer lexer;
    lexer.Run(myFile);

    try {
        // Run Parser (project 2)
        //PURPOSE: checks the order of the tokens and then made a datalog program container
        Parser parser(lexer.getTokens());
        DatalogProgram program = parser.Parse();
        // cout << "Success!" << endl;
        // cout << program.toString();

        // Run Interpreter (project 3)
        //PURPOSE: you made a database and an interpreter that ANSWERED QUERIES using just the given facts
        Interpreter interpreter(program);
        //interpreter.run();

        //Rule Evaluation (will run when running the interpreter) (project 4)
        // rules generation more tuples
        //these new tuples are just as valid as the tuples created from the facts when it comes to answering queries and even making more tuples
        //you need to code this "rule evaluation" process to create more tuples
        //the same as project 3

        //project 5
        interpreter.Optimize_Rules();

        // Catch Errors
    } catch (Token* errorToken) {
        cout << "Failure!" << endl << "  " << errorToken -> toString();
    }


    return 0;
}