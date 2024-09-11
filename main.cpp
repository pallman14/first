// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: main.cpp

#include "Grammar.h"

int main() {
    const char* filename = "grammar.txt";
    
    // Create a Grammar object
    Grammar grammar(filename);
    
    // Print the lists and start symbol:
    // Print the start symbol
    grammar.printStartSymbol();  
    // Print non-terminals
    grammar.printNonTerminals();  
    // Print terminals
    grammar.printTerminals();      
    // Print production rules
    grammar.printGrammar();        
    
    return 0;
}
