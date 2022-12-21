#ifndef PROJECT_1_PARSER_H
#define PROJECT_1_PARSER_H

#include <vector>
#include <set>

#include "Predicate.h"
#include "Rule.h"
#include "Token.h"
#include "datalogProgram.h"
#include "Lexer.h"
using namespace std;

class Parser {
private:
    //given from instructions
    vector<Token*> tokens;
    DatalogProgram program;

    //things to add/help
    size_t position = 0;

public:
    // Constructor to assign all objects with a vector of tokens
    Parser(const vector<Token*> t){
        for (auto i : t){
            tokens.push_back(i);
        }
    }

    // Match Tokens
    void match(TokenType t){
        // checks EOF
        if (position >= this->tokens.size()) {
            return;
        }
        if (tokens.at(position)->getTokenType() == TokenType::END_OF_FILE) {
            return;
        }

        //Skip_Comments(); //not expecting a comment
        //comments should be taken care of first

        // Check to see if the tokentype matches
        if (t == tokens.at(position)->getTokenType()) {
            position++;
            Skip_Comments();
            //note: to make faster, we can use a while-loop (saves memory too)
            //while tokens does not = to comments
        } else {
            throw(tokens[position]);
        }
    }

    // Skip Comments
    void Skip_Comments(){
        if (tokens.at(position)->getTokenType() == TokenType::COMMENT) {
            position++;
            Skip_Comments(); //recursive
        }
    }

    DatalogProgram Parse(){
        datalogProgram();
        return program;
    }

    //TODO: GRAMMAR RULES:
    //datalogProgram -> SCHEMES COLON scheme schemeList FACTS COLON factList RULES COLON ruleList QUERIES COLON query queryLIST EOF
    void datalogProgram(){
        Skip_Comments();
        match(TokenType::SCHEMES); //SCHEMES
        match(TokenType::COLON); //COLON
        Parse_Scheme(); //scheme
        Parse_SchemeList(); //schemeList
        match(TokenType::FACTS); //FACTS
        match(TokenType::COLON); //COLON
        Parse_FactList(); //factList
        match(TokenType::RULES); //RULES
        match(TokenType::COLON); //COLON
        Parse_RuleList(); //ruleList
        match(TokenType::QUERIES); //QUERIES
        match(TokenType::COLON); //COLON
        Parse_Query(); //query
        Parse_QueryList(); //queryList
        match(TokenType::END_OF_FILE); //EOF
    }

    //schemeList -> scheme schemeList | lambda
    void Parse_SchemeList(){

        if (tokens.at(position)->getTokenType() == TokenType::ID) {
            Parse_Scheme(); //1. scheme
            Parse_SchemeList(); //2. schemeList
        }
        /*
        //if tokentype = ID, parse the scheme and parse the schemelist
        if (tokens.at(position) -> getTokenType() == TokenType::ID) {

            //1. scheme
            Parse_Scheme();

            //2. schemelist
            Parse_SchemeList();
        }
         */
    }

    //factList -> fact factList | lambda
    void Parse_FactList(){
        if (tokens.at(position)->getTokenType() == TokenType::ID) {
            Parse_Fact(); //1. fact
            Parse_FactList(); //2. factList
        }
    }

    //ruleList -> rule ruleList | lambda
    void Parse_RuleList(){
        if (tokens.at(position)->getTokenType() == TokenType::ID) {
            Parse_Rule(); //1. rule
            Parse_RuleList();// 2. ruleList
        }
    }

    //queryList -> query queryList | lambda
    void Parse_QueryList(){
        if (tokens.at(position)->getTokenType() == TokenType::ID){
            Parse_Query(); //1. query
            Parse_QueryList(); //2. queryList
        }
    }

    //scheme -> ID LEFT_PAREN ID idList RIGHT_PAREN
    void Parse_Scheme(){
        Predicate scheme;
        Parameter parameter;

        //1. ID
        //student
        match(TokenType::ID);
        scheme.Set_ID(tokens.at(position - 1)->getTokenDescription());

        // 2. Left paranthesis
        match(TokenType::LEFT_PAREN);

        //3. ID
        match(TokenType::ID);

        parameter.Set_ID(tokens.at(position - 1)->getTokenDescription());
        scheme.Add_Parameter(parameter);

        // 4. idList
        Parse_IdList(scheme);

        // 5. right parantheses
        match(TokenType::RIGHT_PAREN);

        // Push the scheme
        program.push_Schemes(scheme);

    }

    //fact -> ID LEFT_PAREN STRING stringList RIGHT_PAREN PERIOD
    void Parse_Fact(){
        Predicate fact;
        Parameter parameter;

        //1. ID
        match(TokenType::ID);
        fact.Set_ID(tokens.at(position-1)->getTokenDescription());

        //2. Left parentheses
        match(TokenType::LEFT_PAREN);

        //3. string
        match(TokenType::STRING);
        program.push_Domain(tokens.at(position-1)->getTokenDescription());

        parameter.Set_ID(tokens.at(position-1)->getTokenDescription());
        fact.Add_Parameter(parameter);

        //4. stringList
        Parse_StringList(fact);

        //5. right parentheses
        match(TokenType::RIGHT_PAREN);

        //6. period
        match(TokenType::PERIOD);

        //Push onto vectors of facts
        program.push_Facts(fact);
    }

    // rule  ->  headPredicate COLON_DASH predicate predicateList PERIOD
    void Parse_Rule(){
        Predicate ruleHead;
        Predicate rules;
        Rule rule;

        //1. headPredicate
        headPredicate(ruleHead);

        rule.set_PredicateHead(ruleHead);

        //2. COLON DASH
        match(TokenType::COLON_DASH);

        //3. predicate
        Parse_Predicate(rules);

        rule.push_Predicate(rules);

        //4. predicateList
        Parse_PredicateList(rule);

        //5. Period
        match(TokenType::PERIOD);

        //push onto vector
        program.push_Rules(rule);
    }

    // query  ->  predicate Q_MARK
    void Parse_Query(){
        Predicate query;

        //1. predicate
        Parse_Predicate(query);

        //2. Q_Mark
        match(TokenType::Q_MARK);

        program.push_Queries(query);
    }

    //headPredicate -> ID LEFT_PAREN ID idList RIGHT_PAREN
    void headPredicate(Predicate& predicate){
        Parameter param;

        //1. ID
        match(TokenType::ID);
        predicate.Set_ID(tokens.at(position-1)->getTokenDescription());

        //2. Left_paren
        match(TokenType::LEFT_PAREN);

        //3. ID
        match(TokenType::ID);

        param.Set_ID(tokens.at(position-1)->getTokenDescription());
        predicate.Add_Parameter(param);

        //4. idList
        Parse_IdList(predicate);

        //5. right_paren
        match(TokenType::RIGHT_PAREN);
    }

    // predicate  ->  ID LEFT_PAREN parameter parameterList RIGHT_PAREN
    void Parse_Predicate(Predicate& predicate){
        //1. ID
        match(TokenType::ID);

        predicate.Set_ID(tokens.at(position-1)->getTokenDescription());

        //2. Left Paren
        match(TokenType::LEFT_PAREN);

        //3. Parameter
        Parse_Parameter(predicate);

        //4. ParameterList
        Parse_ParameterList(predicate);

        //5. right paren
        match(TokenType::RIGHT_PAREN);
    }

    // predicateList  ->  COMMA predicate predicateList | lambda
    void Parse_PredicateList(Rule& rule){
        //1. comma
        if (tokens.at(position)->getTokenType() == TokenType::COMMA){
            Predicate p;

            //1. comma
            match(TokenType::COMMA);

            //2. predicate
            Parse_Predicate(p);

            // Push to vector of predicates in rule
            rule.push_Predicate(p);

            //3.  predicate list
            Parse_PredicateList(rule);
        }
    }

    //parameterList
    void Parse_ParameterList(Predicate& predicate){
        if (tokens.at(position)->getTokenType() == TokenType::COMMA) {
            match(TokenType::COMMA);

            Parse_Parameter(predicate);
            Parse_ParameterList(predicate);
        }
    }

    //stringList
    void Parse_StringList(Predicate& predicate){
        if (tokens.at(position)->getTokenType() == TokenType::COMMA) {
            Parameter p;

            // 1. comma
            match(TokenType::COMMA);

            //2. string
            match(TokenType::STRING);

            // Adding Parameter
            program.push_Domain(tokens.at(position-1)->getTokenDescription());
            p.Set_ID(tokens.at(position-1)->getTokenDescription());
            predicate.Add_Parameter(p);

            Parse_StringList(predicate);
        }
    }

    //idList
    void Parse_IdList(Predicate& predicate){
        if (tokens.at(position)->getTokenType() == TokenType::COMMA) {
            Parameter p;

            //1. comma
            match(TokenType::COMMA);

            //2 ID
            match(TokenType::ID);

            p.Set_ID(tokens.at(position - 1)->getTokenDescription());
            predicate.Add_Parameter(p);

            //3. idList
            Parse_IdList(predicate);
        }
    }

    // parameter  ->  STRING | ID
    void Parse_Parameter(Predicate& predicate){
// Check for string
        if (tokens.at(position)->getTokenType() == TokenType::STRING) {
            //1. String
            match(TokenType::STRING);
            //OR

            //2. ID
        } else if (tokens.at(position)->getTokenType() == TokenType::ID) {
            match(TokenType::ID);
        }

        // Add Parameter
        Parameter parameter;

        parameter.Set_ID(tokens.at(position-1)->getTokenDescription());
        predicate.Add_Parameter(parameter);
    }

};

#endif //PROJECT_1_PARSER_H
