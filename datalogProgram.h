#ifndef PROJECT_1_DATALOGPROGRAM_H
#define PROJECT_1_DATALOGPROGRAM_H

#include <vector>
#include <set>
#include <sstream>

#include "Predicate.h"
#include "Parameter.h"
#include "Rule.h"
#include "Token.h"
using namespace std;

class DatalogProgram {
private:
    //given in instructions
    vector<Predicate> schemes; //Scheme(#):
    vector<Predicate> facts; //Facts(#):
    vector<Predicate> queries; //Queries(#):
    vector<Rule> rules; //Rules(#):
    set<string> Domains; //Domain(#):

public:
    //push_back (pushing predicates onto the vectors^^)
    void push_Schemes(Predicate scheme){
        schemes.push_back(scheme);
    }
    void push_Facts(Predicate fact){
        facts.push_back(fact);
    }
    void push_Queries(Predicate query){
        queries.push_back(query);
    }
    void push_Rules(Rule rule){
        rules.push_back(rule);
    }
    void push_Domain(string domain){
        Domains.insert(domain);
    }

    //setters

    //getters
    vector<Predicate> Get_Schemes() {
        return schemes;
    }

    // Get Facts
    vector<Predicate> Get_Facts() {
        return facts;
    }

    // Get Rules
    vector<Rule> Get_Rules() {
        return rules;
    }

    // Get Queries
    vector<Predicate> Get_Queries() {
        return queries;
    }



    //printing
    string toString() {

        stringstream out;
        // Printing the schemes vector
        out << "Schemes(" << schemes.size() << "):" << endl;
        for (Predicate scheme : schemes) {
            out << "  " << scheme.toString() << endl;
        }

        // Printing the facts vector
        out << "Facts(" << facts.size() << "):" << endl;
        for (Predicate fact : facts) {
            out << "  " << fact.toString() << "." << endl;
        }

        // Printing the rules vector
        out << "Rules(" << rules.size() << "):" << endl;
        for (Rule rule : rules) {
            out << "  " << rule.toString() << "." << endl;
        }

        // Printing the queries vector
        out << "Queries(" << queries.size() << "):" << endl;
        for (Predicate query : queries) {
            out << "  " << query.toString() << "?" << endl;
        }

        // Printing the domain set list
        out << "Domain(" << Domains.size() << "):" << endl;
        for (std::string s : Domains) {
            out << "  " << s << endl;
        }

        return out.str();
    }

};


/*
string DatalogProgram::getFactsDomain(){
    //return factsDomain; //domain is a set
}
 */

#endif //PROJECT_1_DATALOGPROGRAM_H

/*

 */