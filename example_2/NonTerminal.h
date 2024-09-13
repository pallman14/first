#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include "Production.h"
#include <iostream>

class NonTerminal {
    public:
        char symbol;  // The symbol for this non-terminal
        Production *prodsRoot;  // Linked list of production rules
        NonTerminal *next;  // Next non-terminal in the list

        // Constructor to initialize the non-terminal with the given symbol
        NonTerminal(char symbol);

        // Destructor to clean up production rules
        ~NonTerminal();

        // Add a production to this non-terminal
        void addProduction(string stmt);
};

#endif
