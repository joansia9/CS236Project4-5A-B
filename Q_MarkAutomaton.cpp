//
// Created by Joan Siasoyco on 9/18/22.
//

#include "Q_MarkAutomaton.h"

void Q_MarkAutomaton::S0(const std::string& input) {
    if (input[index] == '?') {
        inputRead = 1;
    }
    else {
        Serr();
    }
}