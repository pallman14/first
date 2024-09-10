#include "NonTerminal.h"

NonTerminal::NonTerminal(const char* sym) {
    strcpy(symbol, sym);
}

const char* NonTerminal::getSymbol() const {
    return symbol;
}

NonTerminal::~NonTerminal() {
    // No dynamic memory to clean up in this case.
}
