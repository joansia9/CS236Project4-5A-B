#ifndef PROJECT_1_PREDICATE_H
#define PROJECT_1_PREDICATE_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "Parameter.h"

using namespace std;

class Predicate {
private:
    vector<Parameter> parameters;
    string pred_id;

    //Now what is a predicate?
    //A predicate is the snap in snap(a,b,c)

public:
    // Add parameter to the paramteres vector
    void Add_Parameter(Parameter p) {
        parameters.push_back(p);
    }

    // Set Predicate ID
    void Set_ID(string ID) {
        pred_id = ID;
    }

    //getters
    string Get_ID(){
        return pred_id;
    }
    vector<Parameter> Get_Parameters() {
        return parameters;
    }

    //toString
    string toString() {
        stringstream out;

        string seperate = "";
        out << pred_id << "("; //loves
        for (Parameter currParam: parameters) {
            out << seperate << currParam.toString();
            seperate = ",";
        }
        out << ")";

        return out.str();

        //will print: loves(A,X)
    }

    vector<string> Get_String_Parameters() const
    {
        vector<string> parameters_strings;
        for(auto parameter: this->parameters)
        {
            parameters_strings.push_back(parameter.Get_ID());
        }

        return parameters_strings;
    }
};
#endif //PROJECT_1_PREDICATE_H