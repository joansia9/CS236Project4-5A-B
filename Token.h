#ifndef TOKEN_H
#define TOKEN_H
#include <string>

using namespace std;

enum class TokenType {
    COLON,
    COLON_DASH,
     // TODO: add the other types of tokens
     COMMA, PERIOD, LEFT_PAREN, RIGHT_PAREN, Q_MARK, ADD, MULTIPLY,
     FACTS,
     SCHEMES,
     RULES,
     QUERIES,
     UNDEFINED,
     COMMENT,
     END_OF_FILE,
     ID,
     STRING
};

class Token
{
private:
    // TODO: add member variables for information needed by Token
    TokenType type; //FIXME should this be a string or a tokentype?
    string description; //COLON
    int lineNum; //input line number

    string tokenName;
public:

    //FIXME: should this be private or public?

    Token(TokenType type, string description, int lineNum);

    string toString() ;
    string TokenConverterToString(TokenType type);

    // TODO: add other needed methods
    string getTokenName();

    string getTokenDescription();

    //ADDED FOR PROJECT 2
    TokenType getTokenType();


};

#endif // TOKEN_H


