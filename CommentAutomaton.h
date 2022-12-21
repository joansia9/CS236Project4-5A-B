//
// Created by Joan Siasoyco on 9/21/22.
//

#ifndef PROJECT_1_COMMENTAUTOMATON_H
#define PROJECT_1_COMMENTAUTOMATON_H

#include "Automaton.h"
using namespace std;
class CommentAutomaton: public Automaton{
    //A line comment starts with a hash character (#)
    // and ends at the end of the line or end of the file.
public:
    CommentAutomaton() : Automaton(TokenType::COMMENT){} //calls the base constructor

    void S0(const string& input){
        multilineInc = 0; //used to increment

        if (input.at(index) == '#') { //if you see #
            Continue(); //increment the index/position
            S1(input); //continue
        }
    }

    void S1(const string& input){
        if (input.at(index) != '|') { //if we see |
            Continue(); //increment the index/position
            S2(input); //continue
        } else if (input.at(index) == '|') { //if we see |
            hasMultiline = true; //HAS MULTIPLE LINES
            Continue(); //increment index/position
            S3(input); //here we will increment multiple lines
        }
    }

    void S2(const std::string& input) { //an accept state
        if (input.at(index) != '\n') { //end line
            Continue();
            S2(input); //continue if there are more words in the comments
        } else {
            return;
        }
    }

    void S3(const std::string& input) {
        size_t sizeOfComment = input.size();
        if (index >= sizeOfComment) { //if the index is greater than the size of the comment, it ended
            endFlag = true;
            return;
            /* example:
             * #| hello
             * my name is joan
             * */
        } else if (input.at(index) != '|') { //if we see |
            //CHECKS FOR MULTIPLE LINESSS
            if (input[inputRead] == '\n') {  //if u see a new line
                multilineInc++; //used to increment the lines
            }
            Continue(); //increment index
            S3(input); //recursion
        } else if (input.at(index) == '|') { //if we see | and theres no multiple line
            Continue(); //increase position we just read
            S4(input); //continue
        }
    }

    void S4(const std::string& input) {
        if (input.at(index) == '#') { //if we find #
            Continue();
            return; // accept b/c sets inputRead to non-zero value and quits function
        } else if (input.at(index) == '|') {
            Continue();
            S3(input);
        }else {
            if (input[inputRead] == '\n') {
                S3(input);
            }

            endFlag = true;
            return;
        }
    }
};


#endif //PROJECT_1_COMMENTAUTOMATON_H
