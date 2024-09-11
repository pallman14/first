#include "Terminal.h"

// Initializes the terminal symbol with the provided string.
Terminal::Terminal(const char* sym) {
    // Copy the provided symbol into 'symbol'.
    // strcpy is used here for copying the C-style string.
    strcpy(symbol, sym);
}

// Getter for the terminal symbol.
const char* Terminal::getSymbol() const {
    // Return the terminal symbol stored in the 'symbol' array.
    return symbol;
}

//Destructor for the Terminal class.
Terminal::~Terminal() {
    // No dynamic memory to clean up.
}
