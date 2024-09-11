// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: grammar.h
// The Grammar class represents a context-free grammar, storing production rules, terminals, non-terminals, and the start symbol.
// It stores the overall structure of a grammar, including productions, non-terminals, terminals, and start symbols.

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "Production.h"
#include "NonTerminal.h"
#include "Terminal.h"
#include <iostream>
#include <fstream>

using namespace std;

class Grammar {
private:
    // Array of pointers to Production objects (stores all production rules)
    Production** productions;
    // Array of pointers to NonTerminal objects (stores all non-terminals)
    NonTerminal** nonTerminals;
    // Array of pointers to Terminal objects (stores all terminals)
    Terminal** terminals;
    // Number of productions stored in the grammar
    int numProductions;
    // Number of non-terminals in the grammar
    int numNonTerminals;
    // Number of terminals in the grammar
    int numTerminals;
    // The start symbol of the grammar
    NonTerminal* startSymbol;

public:
    // Constructor: Reads the grammar from a file and initializes grammar components.
    Grammar(const char* filename);
    // Pre-conditions: The file specified by the filename must exist and contain correctly formatted production rules.
    // Expected format for each rule looks like: LHS -> RHS.
    // Post-conditions: All non-terminals, terminals, and production rules are stored in their respective arrays.
    // The start symbol is set to the LHS of the first production rule.

    // Prints the production rules in the format "LHS -> RHS".
    void printGrammar();
    // Pre-conditions: The grammar must have been initialized, and production rules must be stored.
    // Post-conditions: Prints all the production rules of the grammar.

    //Prints the list of terminals in the grammar.
    void printTerminals(); 
    //Pre-conditions: The grammar must have been initialized, and terminals must be stored.
    //Post-conditions: Prints the list of terminal symbols enclosed in curly braces.

    // Prints the list of non-terminals in the grammar.
    void printNonTerminals();  
    // Pre-conditions: The grammar must have been initialized, and non-terminals must be stored.
    // Post-conditions: Prints the list of non-terminal symbols enclosed in curly braces.

    // Prints the start symbol of the grammar.
    void printStartSymbol();           
    // Pre-conditions: The grammar must have been initialized, and the start symbol must have been set.
    // Post-conditions: Prints the start symbol of the grammar.

    // Destructor: Cleans up dynamically allocated memory (productions, non-terminals, terminals, and start symbol).
    ~Grammar();
    // Pre-conditions: The grammar object has been initialized and allocated memory for its components.
    // Post-conditions: All dynamically allocated memory for productions, non-terminals, terminals, and the start symbol is freed.
};

#endif
