//
// Created by Joan Siasoyco on 9/18/22.
//

#include "Right_ParenAutomata.h"

void Right_ParenAutomaton::S0(const std::string& input) {
    if (input[index] == ')') {
        inputRead = 1;
    }
}
