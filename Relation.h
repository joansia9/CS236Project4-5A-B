#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <set>

#include "Header.h"
#include "Tuple.h"

using namespace std;

#ifndef PROJECT_1_RELATION_H
#define PROJECT_1_RELATION_H
class Relation{
private:
    string name;
    Header header;
    set<Tuple> tuples;
public:
    //constructors
    Relation() = default;
    Relation(string name, Header header) : name(name), header(header) {}

    //getters
    string Get_Name() {
        return name;
    }
    unsigned int Get_Size() {
        return tuples.size();
    }
    Header Get_Header(){
        return header;
    }
    set<Tuple> Get_Tuples(){
        return tuples;
    }

    //setters
    void Set_Tuples(set<Tuple> tuples) {
        this->tuples = tuples;
    }

    //adders
    void Add_Tuple(Tuple t) {
        tuples.insert(t);
    }

    //print function
    string toString() {
        stringstream o;
        for (Tuple t : tuples) {
            if (t.size() > 0) {
                o << " " << t.toString(header) << endl;
            }
            //this wil output A and X in A='bob', X='jane'

            //  A='bob', X='jane'
            //  A='frankk', X='mary'
            //  A='jane', X='frankk'
            //  A='john', X='john'
            //  A='mary', X='bob'
        }

        return o.str();
    }

    //unary
    Relation select(int position, string value) {
        //purpose: finds all the tuples that have a constant value in a certain column
        //parameter: takes 2 parameters -> a position and value
        //result: different number of rows
            // the given position would need to have a value equal to the given value for that tuple

        Relation output(name, header); //create an output with name and header copied over from input
        Tuple tuple;

        //unsigned int tuple_size = tuples.size();
        for (Tuple tuple : tuples) { //go through each row...
            //gets the tuple value of the position desired
            string selected_tuple_value = tuple.Get_TupleValue(position);
            if (selected_tuple_value == value) { //if the tuple value = the value we want...
                output.Add_Tuple(tuple); //add the tuple to the output...

            }
        }
        return output; //returns a relation with different amount of rows!
    }
    Relation select( int position1, int position2) {
        //purpose: finds all the tuples that have the same value in 2 different columns
        //as long as both columns have the same value
        //parameter: takes 2 parameters: both positions
        //result: different number of rows
        // the 2 positions in a tuple would need to have equal values

        //cout << "in select function" << endl;

        Relation output(name, header); //create an output with name and header copied over from input

        //check: if the columns are in bounds
        if (position1 >= header.size() || position2 >= header.size()){ //if the position is greater or equal to size
            throw "out of bound"; //it is out of bound
        }

        for (Tuple tuple : tuples) { //go through each row (the set of tuples)
            if (tuple.Get_TupleValue(position1) == tuple.Get_TupleValue(position2)) { //if the tuple values are the same in both positions
                output.Add_Tuple(tuple); //add the tuple to the relation
            }
        }

        return output; //returns a new relation (ex) X='a' Y = 'a'
    }
    Relation project(vector<int> columnsToProject) { //column positions

        //purpose: changes the number and order of columns in a relation
        //result: either the same number or fewer columns
        //function: changes the header and all tuples in the relation
        //parameter: list of positions of the columns that should be included in the result (columns to be kept)

        Header new_Header; //create a new Header vector

        // Update columnNames with the selcted columns (passed in the function)
        int column_to_parse_through = columnsToProject.size();

        //
        for (int i = 0; i < column_to_parse_through; i++) {
            string currHeader = header.Find_Header(i); //currHeader = the header we want to find
            new_Header.Add_Header(currHeader);
        }

        Relation output(name, new_Header);

        // Update rows at the selected columns (passed in the function)

        for (auto tuple : tuples) { //go through selected rows
            Tuple new_Tuple; //create a new tuple

            for (auto i : columnsToProject) {
                string currTuple = tuple.Get_TupleValue(i);
                new_Tuple.Add_TupleValue(currTuple); //add tuple
            }

            output.Add_Tuple(new_Tuple); //add tuple to relation
        }

        return output;
    }
    Relation rename(vector<string> header) {
        //purpose: changes the header of the relation
        //result: same tuples as the original (and columns and rows should not be changed)
        //parameter: position, and new name
        //function: replacing the entire list of attributes is easier and avoids issues with name conflicts

        Header new_header(header); //assigns input as a new header

        Relation output(name, new_header);
        output.Set_Tuples(tuples);

        return output;
    }


    //Your 'Relation' class uses a vector to store its tuples, and you're manually sorting them.
    // This is almost always done INEFFICIENTLY.
    //you should use 'set<Tuple>' and implement the 'bool Tuple::operator<(const Tuple& other) const' function

    //how the join is supposed to work:
    //joining 3 or more relations
    //A(w,x,y,z) :- B(w), C(w), D(y), E(z)
    //1. take the first relation and start that as your "result"
    //2. join the result with the second relation and store the result
    //3. Join the result with the third relation and store the result
    //4. join the result with the fourth relation and store the result



    Relation Natural_Join(Relation &relation_to_join) {
        //type: a function of the relation class
        //input: another relation to join with
        //returns: the joined relation

        map<int, int> matched_headers;
        set<int> unique;
        Header joined_headers;

        Relation relation1 = *this;
        Relation relation2 = relation_to_join;

        Header first_header = relation1.Get_Header();
        Header second_header = relation2.Get_Header();

        string first_name = relation1.Get_Name();
        string second_name = relation2.Get_Name();


        //join aspects
        //1. combine the 2 Headers
        joined_headers = Join_Headers(relation1, relation2, matched_headers, unique);

        //create a new relation
        Relation output(first_name + second_name, joined_headers);

        //2. Go through every pair of tuples
        output.Join_Rows(relation1, relation2, matched_headers, unique, output);

        return output;
    }

   Header Join_Headers(Relation &relation1, Relation &relation2, map <int, int> &matched_headers, set<int> &unique) const {
        Header joined_headers;

        Header headers1 = relation1.Get_Header();
        Header headers2 = relation2.Get_Header();
        int size_of_relation1 = headers1.Get_Size();
        int size_of_relation2 = headers2.Get_Size();

        bool isMatched;

        for (int i = 0; i < size_of_relation2; i++) {
            string currheader2 = headers2.Find_Header(i);

            isMatched = false;

            for (int j = 0; j < size_of_relation1; j++) {
                string currheader1 = headers1.Find_Header(j);

                //cout << "seeing if: " << currheader2 << " and " << currheader1 << " match " << endl;

                if (currheader1 == currheader2) {

                    //cout << " it matches and adding it position1 " << j << " and position2 " << i << endl;

                    isMatched = true;
                    matched_headers.insert({j, i});
                }
            }
            if (!isMatched) {  //if they dont match
                //cout << " it does not match so adding position2: " << i << " will be added to unique columns set " << endl;
                unique.insert(i);
            }
        }
            //debugging purposes:
            /*
            cout << "before header1 was: " << endl;
            vector<string> currHeader = header1.Get_Attributes();
            for (unsigned int i = 0; i < currHeader.size(); i++) {
                cout << "header1 in position: " << i << " is " << currHeader.at(i) << endl;
            }
            cout << "before joined_header was: " << endl;
            vector<string> currjoined_header = joined_header.Get_Attributes();
            for (unsigned int i = 0; i < currjoined_header.size(); i++) {
                cout << "header1 in position: " << i << " is " << currjoined_header.at(i) << endl;
            }
             */

            joined_headers = headers1;

            //debugging purposes:
            /*
            cout << "after: " << endl;
            vector<string> currHeader2 = header1.Get_Attributes();
            for (unsigned int i = 0; i < currHeader2.size(); i++) {
                cout << "header1 in position: " << i << " is " << currHeader2.at(i) << endl;
            }
            cout << "after joined_header was: " << endl;
            vector<string> currjoined_header2 = joined_header.Get_Attributes();
            for (unsigned int i = 0; i < currjoined_header2.size(); i++) {
                cout << "header1 in position: " << i << " is " << currjoined_header2.at(i) << endl;
            }
             */

            for (unsigned int unique_col_position : unique) {
                string unique_header = headers2.Find_Header(unique_col_position);
                joined_headers.Add_Header(unique_header);
            }
            //debugging purposes
            /*
            cout << "joined headers are: ";
            for (unsigned int i = 0; i < joined_header.size(); i++) {
                cout << joined_header.Find_Header(i) << " ";
            }
            cout << endl;
             */

        return joined_headers;
    }


    void Join_Rows (Relation &relation1, Relation &relation2, map<int,int> &matched_headers, set<int> &unique, Relation &output){
        Tuple joined_tuple;
        set<Tuple> relation1_tuples = relation1.Get_Tuples();
        set<Tuple> relation2_tuples = relation2.Get_Tuples();


        for (Tuple currTuple1 : relation1_tuples){ //loop through tuple1

            for (Tuple currTuple2 : relation2_tuples) { //loop through tuple2

                //a. See if you can combine the tuples
                if (isJoinable(currTuple1, currTuple2, matched_headers)){ //compare tuple1 and tuple2

                    //Does every column that is supposed to match actually match?
                    joined_tuple = Join_Tuples(currTuple1, currTuple2, unique); //join if they are the same

                    //b. If the tuples can be combined, then combine them
                    output.Add_Tuple(joined_tuple); //add it to the output
                }
            }
        }
    }


    Tuple Join_Tuples(Tuple &t1, Tuple &t2, set<int> &unique) {
        Tuple new_tuple;
        new_tuple = t1;

        for (unsigned int unique_column_position : unique) {
            string tuple_to_join = t2.at(unique_column_position);

            new_tuple.Add_TupleValue(tuple_to_join);
        }
        return new_tuple;
    }


    bool isJoinable(Tuple& t1, Tuple& t2, map<int, int>& matched_headers){
        for (auto &pair: matched_headers){
            string tuple1 = t1.at(pair.first);
            string tuple2 = t2.at(pair.second);

            if (tuple1 != tuple2){
                return false;
            }
        }
        return true;
    }
};
#endif //PROJECT_1_RELATION_H


//Relations on a set
/*
 * Binary pairs: both elements are from the same set
 * A relation on a set A is a (binary) relation from A to A
 *
 * Binary Relation: elements are 2-tuples and both parts of the tuple are from the set A!
 *
 * Unary: select, project, rename
 *
 * Binary: union, intersection, concatenation, cartesian produce, natural join
 *
 * Equivalent relation "acts" like "equal to" means that the relation satisfies three special propertieis: reflex, symmetric, transitive
 *
 * Antisymmetric: a relation R on a set A is antisymmetric if it is never tru that both (a,b) and (b,a) ar ein R for a different from b
 *
 * Directed Graph (digraph): Set of vertices V and set of graph E that connect vertices.
 * Let the vertices be the set A and the graph be the ordered pair in R
 */

//reflexive
/*
 * for each a
 *  add edge (a,a)
 */

//Symmetric
/*
 * for each a
 *  for each b
 *      if (a,b) then add (b,a)
 */

//transitive: if a is related to b, and if b is related to c, then a is related to c
/*
 * for each a
 *  for each b
 *      for each c
 */

//Closures: Unary operators for relations on a set
/*
 * State a property, call it P, that you'd like a relation, call it R, to have
 * Create a new relation, call it R', from the old relation by adding tuples: R' should satisfy the property, R' should be a subset of R, and R' should be as small as possible
 *
 */
