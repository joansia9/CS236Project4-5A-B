#include <string>
#include <iostream>
#include <sstream>
#include "Token.h"

using namespace std;

Token::Token(TokenType type, string description, int lineNum){
    this->type = type;
    this->description = description;
    this->lineNum = lineNum;
}

string Token::TokenConverterToString(TokenType type) {
    switch(type) {
        case TokenType::COLON: return  "COLON";
        case TokenType::COLON_DASH: return "COLON_DASH";
        case TokenType::COMMA: return "COMMA";
        case TokenType::PERIOD: return "PERIOD";
        case TokenType::Q_MARK: return  "Q_MARK";
        case TokenType::LEFT_PAREN: return  "LEFT_PAREN";
        case TokenType::RIGHT_PAREN: return  "RIGHT_PAREN";
        case TokenType::MULTIPLY: return "MULTIPLY";
        case TokenType::ADD: return "ADD";
        case TokenType::SCHEMES: return "SCHEMES";
        case TokenType::FACTS: return  "FACTS";
        case TokenType::RULES: return "RULES";
        case TokenType::QUERIES: return "QUERIES";
        case TokenType::ID: return "ID";
        case TokenType::STRING: return  "STRING";
        case TokenType::COMMENT: return  "COMMENT";
        case TokenType::END_OF_FILE: return  "EOF";
        case TokenType::UNDEFINED: return  "UNDEFINED";
    }
    return "UNDEFINED";
}

string Token::toString() {
    stringstream out;
    out << "(" << TokenConverterToString(type) << "," << "\"" << description << "\"" << "," << lineNum << ")" << endl;
    return out.str();
} //(COLON, ":", 2)

//getters:
string Token::getTokenName() {
    return TokenConverterToString(type);
}

string Token::getTokenDescription(){
    return description;
}

TokenType Token::getTokenType(){
    return type;
}
