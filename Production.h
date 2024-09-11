#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "NonTerminal.h"
#include "Terminal.h"
#include <iostream>

using namespace std;

class Production {
private:
    // Left-hand side of the production rule
    NonTerminal* lhs;
    // Right-hand side of the production rule
    char rhs[100]; 

public:
    // Constructor
    Production(NonTerminal* lhs, const char* rhs);
    // Pre-condition: 'lhs' should be a valid NonTerminal object, 'rhs' should be a valid C-style string
    // Post-condition: Initializes a production rule with the given LHS and RHS

    // getLHS: Returns the NonTerminal object representing the LHS of the production
    const NonTerminal* getLHS() const;
    // Pre-condition: None
    // Post-condition: Returns a pointer to a constant NonTerminal object that represents the LHS

    // getRHS: Returns the right-hand side (RHS) string of the production
    const char* getRHS() const;
    // Pre-condition: None
    // Post-condition: Returns a C-style string representing the RHS of the production

    // Destructor
    ~Production();
    // Pre-condition: None
    // Post-condition: Cleans up resources when a Production object is destroyed
};

#endif
