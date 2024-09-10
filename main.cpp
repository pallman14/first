#include "Grammar.h"

int main() {
    const char* filename = "grammar.txt";
    
    // Create a Grammar object
    Grammar grammar(filename);
    
    // Print the lists and start symbol
    grammar.printStartSymbol();    // Print the start symbol
    grammar.printNonTerminals();   // Print non-terminals
    grammar.printTerminals();      // Print terminals
    grammar.printGrammar();        // Print production rules
    
    return 0;
}
