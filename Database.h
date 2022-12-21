//
// Created by Joan Siasoyco on 11/10/22.
//

#ifndef PROJECT_1_DATABASE_H
#define PROJECT_1_DATABASE_H

#include <map>
#include "Relation.h"
#include "Header.h"
#include "Tuple.h"

class Database {

private:
    map<string, Relation> database; //makes a map of the relations!

public:
    map<string, Relation> Get_Database() {
        return database;
    }

    Relation Get_Relation(string name) {
        return database.at(name);
    }

    Relation Add_Relation(string name, Header header) { //adding a column
        //create a new column
        Relation new_Relation(name, header);

        //add the new column to the database
        database.insert({name, new_Relation}); //map of relations

        //return new database
        return new_Relation;
    }

    void Add_Tuple(string name, Tuple tuple) { //adding a row to a column
        database.at(name).Add_Tuple(tuple);
    }

};

#endif //PROJECT_1_DATABASE_H
