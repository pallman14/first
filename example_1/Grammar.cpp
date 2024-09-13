#include "Grammar.h"

Grammar::Grammar(const char* filename) {
    ifstream infile(filename);
    char line[100];
    numProductions = 0;
    numNonTerminals = 0;
    numTerminals = 0;
    startSymbol = nullptr;

    // Assume at most 10 non-terminals, terminals, and productions for simplicity
    productions = new Production*[10];
    nonTerminals = new NonTerminal*[10];
    terminals = new Terminal*[10];

    while (infile.getline(line, 100)) {
        char lhs[10], rhs[100];
        sscanf(line, "%s -> %[^\n]", lhs, rhs);

        // Set the start symbol from the first production rule
        if (numProductions == 0) {
            startSymbol = new NonTerminal(lhs);
        }

        // Add non-terminal (LHS) to the list if not already present
        bool foundNonTerminal = false;
        for (int i = 0; i < numNonTerminals; ++i) {
            if (strcmp(nonTerminals[i]->getSymbol(), lhs) == 0) {
                foundNonTerminal = true;
                break;
            }
        }
        if (!foundNonTerminal) {
            nonTerminals[numNonTerminals++] = new NonTerminal(lhs);
        }

        // Add production to the list
        productions[numProductions++] = new Production(new NonTerminal(lhs), rhs);
        
        // Parse RHS for terminals and add them if they are not non-terminals
        char* token = strtok(rhs, " ");
        while (token != NULL) {
            bool foundNonTerminalOnRHS = false;

            // Check if the symbol is a non-terminal
            for (int i = 0; i < numNonTerminals; ++i) {
                if (strcmp(nonTerminals[i]->getSymbol(), token) == 0) {
                    foundNonTerminalOnRHS = true;
                    break;
                }
            }

            // If the symbol is not a non-terminal, treat it as a terminal
            if (!foundNonTerminalOnRHS) {
                bool foundTerminal = false;
                for (int i = 0; i < numTerminals; ++i) {
                    if (strcmp(terminals[i]->getSymbol(), token) == 0) {
                        foundTerminal = true;
                        break;
                    }
                }
                if (!foundTerminal) {
                    terminals[numTerminals++] = new Terminal(token);
                }
            }

            token = strtok(NULL, " ");
        }
    }

    infile.close();
}

// Print the list of production rules
void Grammar::printGrammar() {
    cout << "Production Rules:" << endl;
    for (int i = 0; i < numProductions; ++i) {
        cout << productions[i]->getLHS()->getSymbol() << " -> " << productions[i]->getRHS() << endl;
    }
}

// Print the list of terminals
void Grammar::printTerminals() {
    cout << "Terminals: { ";
    for (int i = 0; i < numTerminals; ++i) {
        cout << terminals[i]->getSymbol() << " ";
    }
    cout << "}" << endl;
}

// Print the list of non-terminals
void Grammar::printNonTerminals() {
    cout << "Non-Terminals: { ";
    for (int i = 0; i < numNonTerminals; ++i) {
        cout << nonTerminals[i]->getSymbol() << " ";
    }
    cout << "}" << endl;
}

// Print the start symbol
void Grammar::printStartSymbol() {
    if (startSymbol != nullptr) {
        cout << "Start Symbol: " << startSymbol->getSymbol() << endl;
    }
}

// Destructor to clean up allocated memory
Grammar::~Grammar() {
    for (int i = 0; i < numProductions; ++i) {
        delete productions[i];
    }
    for (int i = 0; i < numNonTerminals; ++i) {
        delete nonTerminals[i];
    }
    for (int i = 0; i < numTerminals; ++i) {
        delete terminals[i];
    }
    delete[] productions;
    delete[] nonTerminals;
    delete[] terminals;
    delete startSymbol;
}
