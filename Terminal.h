// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: Terminal.h
// This class represents a terminal symbol in the grammar.
// Stores a terminal symbol and allows access to it. 

#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
// For string copy
#include <cstring>

using namespace std;

class Terminal {
private:
    // A character array to store the terminal symbol.
    char symbol[10];

public:
    // Constructor for the Terminal class.
    // Initializes the terminal with the provided symbol.
    Terminal(const char* sym);
    // Pre-conditions: sym must not be nullptr and must be a valid C-style string of length less than 10
    // Post-conditions: The terminal symbol is initialized and stored in the 'symbol' array.

    // Getter function for retrieving the terminal symbol.
    const char* getSymbol() const;
    // Pre-conditions: None.
    // Post-conditions: Returns the stored terminal symbol as a C-style string.

    // Destructor
    ~Terminal();
    // Pre-conditions: none.
    // Post-conditions: Any necessary cleanup is done. 
};

#endif
