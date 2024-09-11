#include "Production.h"

// Constructor for the Production class
// This initializes a production rule with a LHS non-terminal and a RHS string
Production::Production(NonTerminal* lhsSymbol, const char* rhsString) {
    // Assign LHS NonTerminal object
    lhs = lhsSymbol
    // Copy the RHS string into the 'rhs' array
    strcpy(rhs, rhsString);
}

// Returns a pointer to the NonTerminal object representing the LHS of the production rule
const NonTerminal* Production::getLHS() const {
    // Return the NonTerminal object for the LHS
    return lhs;
}

// Returns the RHS of the production rule as a C-style string
const char* Production::getRHS() const {
    // Return the RHS string
    return rhs;
}

// Destructor for the Production class
Production::~Production() {
  
}
