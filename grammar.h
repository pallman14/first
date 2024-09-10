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
    Production** productions;
    NonTerminal** nonTerminals;
    Terminal** terminals;
    int numProductions;
    int numNonTerminals;
    int numTerminals;
    NonTerminal* startSymbol;

public:
    Grammar(const char* filename);
    void printGrammar();               // Prints the production rules
    void printTerminals();             // Prints the list of terminals
    void printNonTerminals();          // Prints the list of non-terminals
    void printStartSymbol();           // Prints the start symbol
    ~Grammar();
};

#endif
