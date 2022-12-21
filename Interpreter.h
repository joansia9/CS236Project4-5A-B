#ifndef PROJECT_1_INTERPRETER_H
#define PROJECT_1_INTERPRETER_H

#include "Header.h"
#include "Database.h"
#include "datalogProgram.h"
#include "Graph.h"
class Interpreter{
private:
    DatalogProgram program;
    Database database;
public:
    //constructor
    Interpreter(DatalogProgram program);

    //destructor
    ~Interpreter()= default;

    //project 5

    void Optimize_Rules(){
        //creating new graph objects
        Graph dependency_graph;
        Graph reversed_dependency_graph;
        vector<Rule> rules_to_go_through;
        vector<vector<unsigned int>> total_pos;
        vector<vector<Rule>> total_rules_to_evaluate;

        //cout << "will run Interpret_Schemes(); " << endl;
        Interpret_Schemes();

        //cout << "will run Interpret_Facts(); " << endl;
        Interpret_Facts();

        //TODO part 1: Build the dependency graph and the reverse dependency grapp

        Build_Graph(dependency_graph, reversed_dependency_graph, rules_to_go_through, total_pos, total_rules_to_evaluate);

        //debug
        /*
        cout << "Reverse Graph" << endl;
        cout << reversed_dependency_graph.toString() << endl;
        good job its working hoe
         */

        // TODO part 2: Run DFS-Forest (in regular numeric order) on the reverse dependency graph to get the post-order
        reversed_dependency_graph.Dfs_Forest();
        vector<unsigned int> post_order = reversed_dependency_graph.Get_Post_Order();

        //debug //WORKS
        /*
        for(auto i : post_order){
            cout << i;
            if (i != post_order.back()){
                cout << ",";
            }
        }
        cout << "\n";
*/

        //TODO part 3: Run DFS-Forest (in reverse post-order) on the forward dependency graph to find the strongly connected components
        dependency_graph.Dfs_Forest_Sccs(post_order);
        vector<set<int>> strongly_connected_comps = dependency_graph.Get_Sccs();

        cout <<"Rule Evaluation" << endl;

        //debug! //WORKS
        /*
        for(auto scc : strongly_connected_comps) {
            cout << "SCC: ";
            for (auto i : scc) {
                cout << "R" << i;
                if (i != *scc.rbegin()) {
                    cout << ",";
                }
            }
            cout << endl;
        }
         */

        //TODO part 4: Evaluate the rules in each component
        //look up the rules in the rule list using the indexes of the strongly connected comps

        for(auto scc : strongly_connected_comps) {
            //store them in a vector called rules_to_evaluate
            vector<Rule> rules_to_evaluate;
            vector<unsigned int> pos;
            for (auto i : scc) {
                rules_to_evaluate.push_back(rules_to_go_through.at(i));
                pos.push_back(i);
            }
            //debug
            /*
            //cout << "SCC: ";
            //for (auto i : scc) {
                //cout << "R" << i;
                //if (i != *scc.rbegin()) {
                    //cout << ",";
                //}
            //}
            //cout << endl;
             */

            total_pos.push_back(pos);
            total_rules_to_evaluate.push_back(rules_to_evaluate);
        } //end of for
        //evaluate these rules here!
        for (unsigned int i = 0; i < total_pos.size(); i++) {
            Interpret_Rules2(total_rules_to_evaluate.at(i), total_pos.at(i));
        }

        //cout << "will run Interpret_Queries(); " << endl;
        Interpret_Queries();
    }

    void Build_Graph(Graph &dependency_graph, Graph &reversed_dependency_graph, vector<Rule> &rules_to_go_through,
             vector<vector<unsigned int>> &total_pos, vector<vector<Rule>> &total_rules_to_evaluate) {
        rules_to_go_through= program.Get_Rules();
        dependency_graph.Set_Size(rules_to_go_through.size());
        reversed_dependency_graph.Set_Size(rules_to_go_through.size());//go through each rule, keep in track of the currRule
        for (unsigned int i = 0; i < rules_to_go_through.size(); i++){
            //cout << "looking at: " << currRule.toString() << endl; //correct looking at the right rules
            //go through predicates of each currRule
            for (Predicate currPredicate : rules_to_go_through.at(i).Get_Predicates()){
                //cout << "inside^ we are looking at: " << currPredicate.Get_ID() << endl; //correct, seeing its predicates
                //look back at the rules thats pointing to the predicates
                for (unsigned int j = 0; j < rules_to_go_through.size(); j++){
                    //cout << "we are comparing back to the rule header which is: " << currRule.Get_PredicateHead().Get_ID() << endl; //correct
                    //if predicate matches the head predicate
                    if(currPredicate.Get_ID() == rules_to_go_through.at(j).Get_PredicateHead().Get_ID()){
                        dependency_graph.Add_Edge(i,j);
                        //cout << dependency_graph.toString() << endl; //WORKING
                        reversed_dependency_graph.Add_Edge(j,i);
                        //cout << reversed_dependency_graph.toString() << endl; //WORKING
                    }
                }
            }
        }
        //print it out!
        cout << "Dependency Graph" << endl;
        cout << dependency_graph.toString();
    }

    void Interpret_Rules2(vector<Rule> rules_to_evaluate, vector<unsigned int> pos) {
        bool isChanged = true;
        unsigned int loops = 0;

        unsigned int i = 0;

        //print before evaluate
        stringstream ss;
        for (unsigned int j = 0; j < pos.size(); j++){
            ss << "R" << pos.at(j);
            if (j != pos.size() - 1) {
                ss << ",";
            }
        }
        cout << "SCC: " << ss.str() << endl;

        while (isChanged) { //for the count
            isChanged = false;

            for (Rule currRule : rules_to_evaluate) { //going through the set of rules

                vector<Relation> relations_to_join; //fixed the looping problem by defining the vector HERE (we want to keep building the vector of relations to join here!)

                //tools to access the head predicate and its predicates
                vector<Predicate> predicates_in_currRule = currRule.Get_Predicates();
                Predicate head_predicate = currRule.Get_PredicateHead();
                string head_predicate_name = head_predicate.Get_ID();

                //tools to access the database
                Relation relation_in_database = database.Get_Relation(head_predicate_name); //match from head
                set<Tuple>joined_relation_tuples = relation_in_database.Get_Tuples();

                Relation joined_relation; //output
                //size_t start_size = database.Get_Relation(currRule.Get_PredicateHead().Get_ID()).Get_Size();

                //cout << "1 Evaluate the predicates on the right-hand side of the rule:" << endl;
                for (Predicate currPredicate : predicates_in_currRule) { //looping through each predicate
                    //push it onto the vector of relations to join
                    //cout << "evaluating predicate: " << currPredicate.Get_ID() << " and adding it onto currPredicate " << endl;
                    relations_to_join.push_back(Interpret_Predicate(currPredicate));
                }

                //cout << "2 Join the relations that result after the unary operations" << endl;
                joined_relation = Join_Relations(relations_to_join);

                //cout << "3 Project the columns that appear in the head predicate:" << endl;
                cout << currRule.toString() << "." << endl;

                joined_relation = Compare_And_Project(joined_relation, head_predicate);

                //cout << "4 Rename the relation to make it union-compatible:" << endl;
                joined_relation = joined_relation.rename(relation_in_database.Get_Header().Get_Attributes());

                //cout << "5 Union with the relation in the database:" << endl;
                for (Tuple currTuple: joined_relation.Get_Tuples()) {
                    if (joined_relation_tuples.find(currTuple) == joined_relation_tuples.end()) {
                        isChanged = true;
                        cout << " " << currTuple.toString(relation_in_database.Get_Header()) << endl;
                    }
                    database.Add_Tuple(head_predicate_name, currTuple);
                } //end of currTuple
                //FIXME
                if(rules_to_evaluate.size() == 1) {
                    if (!isSelfloop(rules_to_evaluate.at(0))) {
                        isChanged = false;
                    }
                }
                i++; //debug
            } // end of currRule loop
            loops++; //project 4
        } //end of while loop
        cout << loops << " passes: " << ss.str() << endl;
    }

    bool isSelfloop(Rule rule){
        for(Predicate currPred : rule.Get_Predicates()){
            if (currPred.Get_ID() == rule.Get_PredicateHead().Get_ID()) {
                return true;
            }
        }
        return false;
    }

    //==============================================================================

    void Interpret_Rules() {
        //cout << "Rule Evaluation" << endl;

        //we want to keep in track of the relations we want to join
        vector<Rule> rules_to_go_through = program.Get_Rules();

        //implement bool of whether datalog program was changed or not
        bool isChanged = true;
        unsigned int loops = 0;

        unsigned int i = 0;

        while (isChanged) { //for the count
            isChanged = false;

            for (Rule currRule : rules_to_go_through) { //going through the set of rules

                vector<Relation> relations_to_join; //fixed the looping problem by defining the vector HERE (we want to keep building the vector of relations to join here!)

                //tools to access the head predicate and its predicates
                vector<Predicate> predicates_in_currRule = currRule.Get_Predicates();
                Predicate head_predicate = currRule.Get_PredicateHead();
                string head_predicate_name = head_predicate.Get_ID();

                //tools to access the database
                Relation relation_in_database = database.Get_Relation(head_predicate_name); //match from head
                set<Tuple>joined_relation_tuples = relation_in_database.Get_Tuples();

                Relation joined_relation; //output
                //size_t start_size = database.Get_Relation(currRule.Get_PredicateHead().Get_ID()).Get_Size();

                //cout << "1 Evaluate the predicates on the right-hand side of the rule:" << endl;
                for (Predicate currPredicate : predicates_in_currRule) { //looping through each predicate
                    //push it onto the vector of relations to join
                    //cout << "evaluating predicate: " << currPredicate.Get_ID() << " and adding it onto currPredicate " << endl;
                    relations_to_join.push_back(Interpret_Predicate(currPredicate));
                }

                //cout << "2 Join the relations that result after the unary operations" << endl;
                joined_relation = Join_Relations(relations_to_join);

                //cout << "3 Project the columns that appear in the head predicate:" << endl;
                cout << currRule.toString() << "." << endl;

                joined_relation = Compare_And_Project(joined_relation, head_predicate);

                //cout << "4 Rename the relation to make it union-compatible:" << endl;
                joined_relation = joined_relation.rename(relation_in_database.Get_Header().Get_Attributes());

                //cout << "5 Union with the relation in the database:" << endl;
                for (Tuple currTuple: joined_relation.Get_Tuples()) {
                    if (joined_relation_tuples.find(currTuple) == joined_relation_tuples.end()) {
                        isChanged = true;
                        cout << " " << currTuple.toString(relation_in_database.Get_Header()) << endl;
                    }
                    database.Add_Tuple(head_predicate_name, currTuple);
                } //end of currTuple
                i++;
            } // end of currRule loop
            loops++;
        } //end of while loop
        cout << "\nSchemes populated after " << loops << " passes through the Rules.\n" << endl;
    }

    Relation Join_Relations(vector<Relation> &relations_to_join) {//if relation_to_join were A B C D
        Relation joined_relation = relations_to_join.at(0); //A
        for (unsigned int i = 1; i < relations_to_join.size(); i++) { //4
            //cout << "relation we want to join:\n" << relations_to_join.at(i).toString() << endl;
            //implementing natural join
            joined_relation = joined_relation.Natural_Join(relations_to_join.at(i));
            //A = A |x| B
            //A |x| B = A |x| B |x| C
            //A |x| B |x| C = A |x| B |x| C |x| D
            //final result: A |x| B |x| C |x| D

        }
        return joined_relation;
    }
    //projects the vector of positions!! (taken care of from project 3)
    Relation Compare_And_Project(Relation& joined_relation, Predicate& head_predicate) {
        vector<string> joined_relations_columns = joined_relation.Get_Header().Get_Attributes();
        vector<string> head_predicate_columns = head_predicate.Get_String_Parameters();
        vector<int> positions_of_columns_to_project;

        //compare the columns names (E,F) and if they are the same, project the position of the joined_relation columns (the output proceeding steps 1 and 2)
        for (unsigned int i = 0; i < head_predicate_columns.size(); i++) { //go through the head pred column
            for (unsigned int j = 0; j < joined_relations_columns.size(); j++) { //joined column
                if(head_predicate_columns.at(i) == joined_relations_columns.at(j)) {
                    positions_of_columns_to_project.push_back(j);
                }
            }
        }
        //projects the vector of positions!! (taken care of from projec3)
        joined_relation = joined_relation.project(positions_of_columns_to_project);

        return joined_relation;
        //loop 1:
        //input 2: returns f(1,2) and f(4,3)

        //loop 2:
        //input2: returns

        //loop 3:
        //input2:
    }

    //===============================================================================
    void run(){
        //1. Process the schemes (same as the last project) DONE
        //2. Process the facts (same as the last project) DONE
        //3. Evaluate the rules (new code)
        //4. Evaluate the queries (same as the last project) DONE

        //cout << "will run Interpret_Schemes(); " << endl;
        Interpret_Schemes();

        //cout << "will run Interpret_Facts(); " << endl;
        Interpret_Facts();

        //cout << "will run Interpret_Rules(); " << endl;
        Interpret_Rules();

        //cout << "will run Interpret_Queries(); " << endl;
        Interpret_Queries();

    }

    void Interpret_Schemes(){
        //takes care of headers
        //goes through each scheme one at a time
        vector<Predicate> scheme_to_go_through = program.Get_Schemes();

        //gets loves then hates
        for (Predicate currScheme : scheme_to_go_through) { //go through
            Header header; //creates new header vector

            //gets E,F then C,D
            //gets the vector of parameters in the scheme and its size
            vector <Parameter> scheme_parameters = currScheme.Get_Parameters();
            unsigned int scheme_parameter_size = scheme_parameters.size();

            //go through each scheme
            for (unsigned int i = 0; i < scheme_parameter_size; i++ ) {

                //find the current header
                Parameter currParameter = scheme_parameters.at(i);
                string currHeader = currParameter.Get_ID();

                //add current header to the header vector
                header.Add_Header(currHeader);
            }

            //find the current relation
            string currRelation = currScheme.Get_ID();

            //add the relation to the database
            database.Add_Relation(currRelation, header); //adding the header to the current scheme in the database!
        }
    }

    void Interpret_Facts() {
        //takes care of rows
        //goes through rows
        //for input 9, size should be 10
        vector <Predicate> rows_to_go_through = program.Get_Facts();

        for (Predicate currFact : rows_to_go_through) {
            Tuple tuple; //creates new tuple vector

            //goes through the things in the rows!
            //EX: loves('bob','jane'); should go through bob and jane (should always be size = 2)
            vector <Parameter> tuple_parameters_to_go_through = currFact.Get_Parameters();
            unsigned int tuple_parameter_size = tuple_parameters_to_go_through.size();

            //go through the tuples
            for (unsigned int i = 0; i < tuple_parameter_size; i++) {

                //get the current tuple name
                Parameter currParameter = tuple_parameters_to_go_through.at(i);
                string currTuple = currParameter.Get_ID();

                //add current tuple to the tuple vector
                tuple.Add_TupleValue(currTuple);
            }

            //get the current Fact name
            string currRelation = currFact.Get_ID();

            //add the fact
            database.Add_Tuple(currRelation, tuple);//adding the new tuple to the database
        }
    }

    void Interpret_Queries() {
        cout << "\nQuery Evaluation" << endl;

        vector <Predicate> queries_to_go_through = program.Get_Queries();
        int size_of_queries = queries_to_go_through.size();
        for (int i = 0; i < size_of_queries; i++) { //goes through the queries in the program
            //each query gets a copy of the relation in teh databse with the same name as the query
            //interpreting the query means understanding what the query's parameters want from this relation and....
            //morphing the relation copy into a smallr resulting relation using select, project, and rename functions we implemented in the Relations class

            Predicate currQuery = queries_to_go_through.at(i);
            cout << currQuery.toString() << "?";

            //helper function
            Relation output = Interpret_Predicate(currQuery);

            int output_size = output.Get_Size();

            if (output_size == 0) { //if theres nothing in the schemes, facts, rules or queries
                cout << " " << "No" << endl;
            } else { //if theres something
                cout << " " << "Yes(" << output_size << ")" << endl;
            }

            cout << output.toString();
        }
    }

    Relation Interpret_Predicate (Predicate predicate) {
        //output to return
        string pred_ID = predicate.Get_ID(); //gets the predicate name
        Relation output = database.Get_Relation(pred_ID); //result should have the inputted predicate ID (value)

        //remember me: ways to avoid pointers, make empty vectors lol

        //empty vectors
        //empty vectors to keep in track of whats seen
        map<string, unsigned int> seen;
        string seen_Values = "";

        //empty vectors to keep in track of whats not seen
        vector<int> unseen_Columns; //columns we have not seen
        vector<string> unseen_Headers; //headers we have not seen

        unsigned int col_position = 0; //to keep in track of columns we've seen

        vector<Parameter> tuples_in_predicate = predicate.Get_Parameters();
        unsigned int predicate_size = tuples_in_predicate.size(); //for the for loops

        //SELECT
        for (unsigned int i = 0; i < predicate_size; i++) { //goes through each tuple from the predicate
            Parameter currParameter = tuples_in_predicate.at(i);
            string new_parameter = currParameter.Get_ID(); //gets each parameters ID

            if (currParameter.isConstant()) { //if it is a '
                //uptdate the output by selecting the column
                output = output.select(col_position, new_parameter);    // select type 1 (position, value)

            } else { ////If the parameters/ll is a variable. have we seen the same variable before in this same auerv?
                //using the map of seen
                //map functions
                //.find(key) accesses
                //.end
                if (seen.find(new_parameter) != seen.end()) {
                    //update the output by selecting the columns
                    output = output.select(col_position, seen.at(new_parameter));   // select type 2 (position, position)
                    // mark it as seen
                } else {
                    seen.insert({new_parameter, col_position});
                    unseen_Columns.push_back(col_position);
                    unseen_Headers.push_back(new_parameter);
                }
            }
            col_position++;
        }

        // PROJECT
        //using a vector of the indexes at which variables were first seen, project out one column for each variable trom the relation
        output = output.project(unseen_Columns); //remember we are projecting positions

        // RENAME
        //using a vector of all variables found (with no duplicates), rename the relation's header column names to the query variables
        output = output.rename(unseen_Headers); //remember that renaming changes the header

        return output;
    }
};

Interpreter::Interpreter(DatalogProgram program) : program(program) {}

#endif //PROJECT_1_INTERPRETER_H


////if (database.Get_Relation(currRule.Get_PredicateHead().Get_ID()).Get_Tuples().find(currTuple) == database.Get_Relation(currRule.Get_PredicateHead().Get_ID()).Get_Tuples().end()) {
//