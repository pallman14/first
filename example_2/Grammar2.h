#ifndef GRAMMAR2_H
#define GRAMMAR2_H

#include "NonTerminal.h"
#include "Terminal.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Grammar {
    private:
        NonTerminal *nonTerminalRoot;
        Terminal *terminalRoot;
        NonTerminal *startSymbol;

        // Helper functions
        bool isTerminalChar(char c);
        bool isNonTerminalChar(char c);
        bool addNonTerminal(char c);
        bool addTerminal(char c);
        bool parseGrammarFile(string filepath);

        void deleteNonTerminals(NonTerminal* &root);
        void deleteTerminals(Terminal* &root);

        // Helper functions for recursive printing
        void printNonTerminalsReverse(NonTerminal *current);
        void printTerminalsReverse(Terminal *current);
        void printProductionsReverse(Production *current);

        bool addProduction(char nonterm, string stmt);  // Declaration of addProduction
        string first(char c);  // Declaration of first method

    public:
        // Constructor: Load and parse the grammar
        Grammar(string filepath);

        // Destructor: Clean up memory
        ~Grammar();

        // Display terminals
        void displayTerminals();

        // Display non-terminals
        void displayNonTerminals();

        // Display productions
        void displayProductions();

        // Display the start symbol
        void displayStartSymbol();

        // Compute and display the first sets
        void displayFirstSets();
};

#endif
