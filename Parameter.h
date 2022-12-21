#ifndef PROJECT_1_PARAMETER_H
#define PROJECT_1_PARAMETER_H
#include <vector>
#include <string>

using namespace std;

//WHAT IS A PARAMETER??
//things that are within a predicate

//example: SNAP(A,B,C)
//ABC are the parameters while SNAP is the predicate

class Parameter{
private:
    string par_id;

public:
    // Set Parameter ID
    void Set_ID(string ID){
        par_id = ID;
    }

    //getters
    string Get_ID(){ //this function gets the parameters insied the paranetheses!
        //EX: loves(E,F) gets E and F
        return par_id;
        //header.push_back(p.getValue());
    }

    //boolean to check if parameter is surrounded quotes
    bool isConstant(){
        return (par_id.at(0) == '\'') && (par_id.at(par_id.size() - 1) == '\'');
    }

    //toString
    string toString() {
        return par_id;
    }
};
#endif //PROJECT_1_PARAMETER_H
