// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: grammar.cpp

#include "Grammar.h"

// Constructor: Reads the grammar from a file and initializes the grammar components 
// (productions, non-terminals, terminals)
Grammar::Grammar(const char* filename) {
    // Open the file containing the grammar
    ifstream infile(filename);
    // store each line of the file
    char line[100];
    // Initialize production counter
    numProductions = 0;
    // Initialize non-terminal counter
    numNonTerminals = 0;
    // Initialize terminal counter
    numTerminals = 0;
    // Initialize the start symbol pointer to nullptr
    startSymbol = nullptr;

    // Allocate space for up to 10 productions, non-terminals, and terminals.
    // This can be adjusted or dynamically expanded for larger grammars.    
    productions = new Production*[10];
    nonTerminals = new NonTerminal*[10];
    terminals = new Terminal*[10];

    // Read the grammar file line by line
    while (infile.getline(line, 100)) {\
        // Store the LHS and RHS of each production rule
        char lhs[10], rhs[100];
        // Extract the LHS and RHS of the production using `sscanf`.
        // This assumes a format like: "LHS -> RHS".
        sscanf(line, "%s -> %[^\n]", lhs, rhs);

        // If this is the first production, set the start symbol to the LHS non-terminal
        if (numProductions == 0) {
            // Start symbol is the first non-terminal
            startSymbol = new NonTerminal(lhs);
        }

        // Check if the LHS is already in the list of non-terminals
        bool foundNonTerminal = false;
        for (int i = 0; i < numNonTerminals; ++i) {
            // We use string compare to check this
            if (strcmp(nonTerminals[i]->getSymbol(), lhs) == 0) {
                // Non-terminal already exists in the list
                foundNonTerminal = true;
                break;
            }
        }
        // If the LHS is a new non-terminal, add it to the list of non-terminals
        if (!foundNonTerminal) {
            nonTerminals[numNonTerminals++] = new NonTerminal(lhs);
        }

        // Create a new Production and add it to the list of productions
        productions[numProductions++] = new Production(new NonTerminal(lhs), rhs);
        
        // Parse RHS for terminals and add them if they are not non-terminals
        // Tokenize the RHS by spaces to get individual symbols
        char* token = strtok(rhs, " ");
        while (token != NULL) {
            bool foundNonTerminalOnRHS = false;

            // Check if the current token is a non-terminal            
            for (int i = 0; i < numNonTerminals; ++i) {
                if (strcmp(nonTerminals[i]->getSymbol(), token) == 0) {
                    // The token is a non-terminal
                    foundNonTerminalOnRHS = true;
                    break;
                }
            }

            // If the symbol is not a non-terminal, treat it as a terminal
            if (!foundNonTerminalOnRHS) {
                bool foundTerminal = false;
                // Check if the terminal is already in the list of terminals
                for (int i = 0; i < numTerminals; ++i) {
                    if (strcmp(terminals[i]->getSymbol(), token) == 0) {
                        // Terminal already exists in the list
                        foundTerminal = true;
                        break;
                    }
                }
                // If the token is a new terminal, add it to the list of terminals
                if (!foundTerminal) {
                    terminals[numTerminals++] = new Terminal(token);
                }
            }
            // Get the next token/symbol from the RHS
            token = strtok(NULL, " ");
        }
    }
    // Close the grammar file after reading all productions
    infile.close();
}

// Print the list of production rules in the format "LHS -> RHS"
void Grammar::printGrammar() {
    cout << "Production Rules:" << endl;
    for (int i = 0; i < numProductions; ++i) {
        // For each production, print its LHS and RHS
        cout << productions[i]->getLHS()->getSymbol() << " -> " << productions[i]->getRHS() << endl;
    }
}

// Print the list of terminal symbols in the grammar
void Grammar::printTerminals() {
    cout << "Terminals: { ";
    for (int i = 0; i < numTerminals; ++i) {
        // Print each terminal symbol
        cout << terminals[i]->getSymbol() << " ";
    }
    cout << "}" << endl;
}

// Print the list of non-terminal symbols in the grammar
void Grammar::printNonTerminals() {
    cout << "Non-Terminals: { ";
    for (int i = 0; i < numNonTerminals; ++i) {
        // Print each non-terminal symbol
        cout << nonTerminals[i]->getSymbol() << " ";
    }
    cout << "}" << endl;
}

// Print the start symbol
void Grammar::printStartSymbol() {
    if (startSymbol != nullptr) {
        // Print the start symbol
        cout << "Start Symbol: " << startSymbol->getSymbol() << endl;
    }
}

// Destructor: Clean up allocated memory 
// (productions, non-terminals, terminals, and start symbol)
Grammar::~Grammar() {
    // Delete each production in the productions array
    for (int i = 0; i < numProductions; ++i) {
        delete productions[i];
    }
    // Delete each non-terminal in the nonTerminals array
    for (int i = 0; i < numNonTerminals; ++i) {
        delete nonTerminals[i];
    }
    // Delete each terminal in the terminals array
    for (int i = 0; i < numTerminals; ++i) {
        delete terminals[i];
    }
    // Delete the arrays themselves
    delete[] productions;
    delete[] nonTerminals;
    delete[] terminals;
    // Delete the start symbol
    delete startSymbol;
}
