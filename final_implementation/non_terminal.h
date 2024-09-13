#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include "production.h"
#include <iostream>
#include <string>

using namespace std;

class non_terminal{
    public:
        string sym;
        production *p_root;
        non_terminal *next;

        non_terminal(string sym);

        ~non_terminal();

        void addProduction(string stmt);
};

#endif