// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: NonTerminal.cpp

#include "NonTerminal.h"

// Initializes a NonTerminal object with the given symbol.
// Parameters: const char* sym. A string representing the symbol for the non-terminal.
NonTerminal::NonTerminal(const char* sym) {
    // Copy the symbol into the member variable using strcpy
    // Assumes that 'sym' is a valid, null-terminated string
    strcpy(symbol, sym);
}

// Getter function for the non-terminal symbol.
const char* NonTerminal::getSymbol() const {
    // Return the symbol stored in the NonTerminal object.
    return symbol;
}

// No dynamic memory to clean up in this case as of now.
NonTerminal::~NonTerminal() {
    
}
