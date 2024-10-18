// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: non_terminal.h
// This file has a constructor to initialize the non-terminal object. Destructor to
// clear memory. And an a function to add a production to the list of productions.

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

        non_terminal(string sym); //constructor for non_terminal class

        ~non_terminal(); //destructor because we store productions

        void addProduction(string stmt); //function to add production string
};

#endif
