#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include <iostream>
#include <cstring>  // For strcpy, strlen

using namespace std;

class NonTerminal {
private:
    // Array to store the symbol for the non-terminal (max length 10)
    char symbol[10];

public:
    // Constructor: Initializes a NonTerminal object with the given symbol.
    NonTerminal(const char* sym);
    // Preconditions: 'sym' must be a valid, null-terminated C-style string (max length 9 characters).
    // Postconditions: Creates a NonTerminal object with the provided symbol.

    // Getter function for the non-terminal symbol.
    const char* getSymbol() const;
    // Preconditions: None.
    // Postconditions: Returns the C-string representing the non-terminal symbol.

    // Destructor: Cleans up the NonTerminal object.
    ~NonTerminal();
    // Preconditions: None.
    // Postconditions: The NonTerminal object is safely destroyed. No dynamic memory needs to be cleaned up
};

#endif
