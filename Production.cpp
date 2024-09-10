#include "Production.h"

Production::Production(NonTerminal* lhsSymbol, const char* rhsString) {
    lhs = lhsSymbol;
    strcpy(rhs, rhsString);
}

const NonTerminal* Production::getLHS() const {
    return lhs;
}

const char* Production::getRHS() const {
    return rhs;
}

Production::~Production() {
    // Destructor for Production does not need to free the NonTerminal, 
    // assuming it's managed by another class (Grammar).
}
