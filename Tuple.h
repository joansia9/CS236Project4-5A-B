#ifndef PROJECT_1_TUPLE_H
#define PROJECT_1_TUPLE_H

#include "Header.h"

#include <vector>
#include <string>
#include <sstream>

class Tuple{
private:
    vector<string> tuples;

public:
    Tuple() = default;
    Tuple (vector<string> values) : tuples(values) { }

    bool operator< (const Tuple t) const {
        return tuples < t.tuples;
    }

    //gets the size
    int size() {
        return tuples.size();
    }

    //gets the tuple value
    string Get_TupleValue(int position) {
        int size = tuples.size();

        if (position > size) {
            throw "Out of bounds";
        }
        return tuples.at(position);
    }

    //adds the tuple values
    void Add_TupleValue(string value) {
        tuples.push_back(value);
    }

    //helper function
    string at(int index) {
        if (index >= size()) {
            throw "Tuple : Index Out of Bounds!";
        }
        return tuples.at(index);
    }

    //print function
    string toString(Header header) {
        if (size() != header.size()) {
            throw "Tuple size has to equal Header size!";
        }
        stringstream o;
        string space = "";
        for (int i = 0; i < size(); i++) {
            o << space << " " << header.Find_Header(i) << "=" << Get_TupleValue(i);
            space = ",";
        }
        return o.str();

        //this will output ='bob', ='jane' in A='bob', X='jane'

        //  A='bob', X='jane'
        //  A='frankk', X='mary'
        //  A='jane', X='frankk'
        //  A='john', X='john'
        //  A='mary', X='bob'

    }

};

#endif //PROJECT_1_TUPLE_H
