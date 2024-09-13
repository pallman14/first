#include "Grammar.h"

// Constructor
Grammar::Grammar(string filepath) {
    nonTerminalRoot = nullptr;
    terminalRoot = nullptr;
    startSymbol = nullptr;

    parseGrammarFile(filepath);
}

// Destructor to clean up dynamically allocated memory
Grammar::~Grammar() {
    deleteNonTerminals(nonTerminalRoot);
    deleteTerminals(terminalRoot);
}

// Parses the grammar from the file
bool Grammar::parseGrammarFile(string filepath) {
    ifstream file(filepath);
    if (!file.is_open()) {
        throw "Error opening grammar file.";
    }

    char currentNonTerminal = '\0';
    string currentProduction = "";

    char ch;
    while (file.get(ch)) {
        // If we encounter a non-terminal (e.g., 'A -> ...')
        if (currentNonTerminal == '\0' && isNonTerminalChar(ch)) {
            addNonTerminal(ch);
            if (startSymbol == nullptr) {
                startSymbol = nonTerminalRoot;  // First non-terminal is the start symbol
            }
            currentNonTerminal = ch;
        } else if (currentNonTerminal != '\0') {
            if (ch == '|' || ch == ';') {
                addProduction(currentNonTerminal, currentProduction);  // Use of addProduction
                currentProduction = "";
                if (ch == ';') {
                    currentNonTerminal = '\0';
                }
            } else if (isTerminalChar(ch) || isNonTerminalChar(ch)) {
                currentProduction += ch;
            }
        }
    }
    file.close();
    return true;
}

// Adds a production to the given non-terminal
bool Grammar::addProduction(char nonterm, string stmt) {
    NonTerminal *current = nonTerminalRoot;
    while (current != nullptr && current->symbol != nonterm) {
        current = current->next;
    }

    if (current == nullptr) return false;

    current->addProduction(stmt);

    for (char c : stmt) {
        if (isTerminalChar(c)) addTerminal(c);
    }
    return true;
}

// Display first sets (depends on the `first` method)
void Grammar::displayFirstSets() {
    NonTerminal *current = nonTerminalRoot;
    while (current != nullptr) {
        cout << "First(" << current->symbol << ") = " << first(current->symbol) << endl;  // Using first()
        current = current->next;
    }
}

// Placeholder for first set logic
string Grammar::first(char c) {
    // Implement first set computation logic
    string firstSet = "";  // Placeholder logic
    return firstSet;
}

// Helper to check if a character is a terminal
bool Grammar::isTerminalChar(char c) {
    return islower(c) || c == '&';
}

// Helper to check if a character is a non-terminal
bool Grammar::isNonTerminalChar(char c) {
    return isupper(c);
}

// Add a non-terminal to the list
bool Grammar::addNonTerminal(char c) {
    NonTerminal *current = nonTerminalRoot;
    while (current != nullptr) {
        if (current->symbol == c) return false;  // Non-terminal already exists
        current = current->next;
    }

    NonTerminal *newNonTerminal = new NonTerminal(c);
    newNonTerminal->next = nonTerminalRoot;
    nonTerminalRoot = newNonTerminal;
    return true;
}

// Add a terminal to the list
bool Grammar::addTerminal(char c) {
    Terminal *current = terminalRoot;
    while (current != nullptr) {
        if (current->symbol == c) return false;  // Terminal already exists
        current = current->next;
    }

    Terminal *newTerminal = new Terminal(c);
    newTerminal->next = terminalRoot;
    terminalRoot = newTerminal;
    return true;
}

/* Adds a production to the given non-terminal
bool Grammar::addProduction(char nonterm, string stmt) {
    NonTerminal *current = nonTerminalRoot;
    while (current != nullptr && current->symbol != nonterm) {
        current = current->next;
    }

    if (current == nullptr) return false;

    current->addProduction(stmt);

    for (char c : stmt) {
        if (isTerminalChar(c)) addTerminal(c);
    }
    return true;
}*/

// Display non-terminals
void Grammar::displayNonTerminals() {
    NonTerminal *current = nonTerminalRoot;
    cout << "Non-Terminals: { ";
    while (current != nullptr) {
        cout << current->symbol << " ";
        current = current->next;
    }
    cout << "}" << endl;
}

// Display terminals
void Grammar::displayTerminals() {
    Terminal *current = terminalRoot;
    cout << "Terminals: { ";
    while (current != nullptr) {
        cout << current->symbol << " ";
        current = current->next;
    }
    cout << "}" << endl;
}

// Display productions
void Grammar::displayProductions() {
    NonTerminal *current = nonTerminalRoot;
    while (current != nullptr) {
        cout << current->symbol << " -> ";
        Production *prod = current->prodsRoot;
        while (prod != nullptr) {
            cout << prod->stmt;
            if (prod->next != nullptr) cout << " | ";
            prod = prod->next;
        }
        cout << ";" << endl;
        current = current->next;
    }
}

// Display start symbol
void Grammar::displayStartSymbol() {
    if (startSymbol != nullptr) {
        cout << "Start Symbol: " << startSymbol->symbol << endl;
    }
}

/* First set logic
string Grammar::first(char c) {
    // Placeholder for first set logic
}*/

/* Display first sets
void Grammar::displayFirstSets() {
    NonTerminal *current = nonTerminalRoot;
    while (current != nullptr) {
        cout << "First(" << current->symbol << ") = " << first(current->symbol) << endl;
        current = current->next;
    }
}*/

// Clean up non-terminals
void Grammar::deleteNonTerminals(NonTerminal* &root) {
    while (root != nullptr) {
        NonTerminal *next = root->next;
        delete root;
        root = next;
    }
}

// Clean up terminals
void Grammar::deleteTerminals(Terminal* &root) {
    while (root != nullptr) {
        Terminal *next = root->next;
        delete root;
        root = next;
    }
}


/*bool Grammar::addProduction(char nonterm, string stmt) {
    // Find the non-terminal in the list
    NonTerminal *nt_curr = nonTerminalRoot;
    bool rc = false;  // Return code to indicate whether a new production was added

    // Traverse the non-terminal list
    while (nt_curr != nullptr) {
        // If the non-terminal matches, handle the productions
        if (nt_curr->symbol == nonterm) {
            Production *prod_curr = nt_curr->prodsRoot;

            // If the non-terminal has no productions yet, add the first one
            if (prod_curr == nullptr) {
                Production *newProd = new Production(stmt);
                nt_curr->prodsRoot = newProd;  // Add the new production
                rc = true;  // New production added
                break;
            }

            // Traverse the productions list of the non-terminal
            while (prod_curr != nullptr) {
                // Check if the production already exists
                if (prod_curr->stmt == stmt) {
                    // Production already exists, do nothing
                    return false;
                }

                // If we reach the end of the list, add a new production
                if (prod_curr->next == nullptr) {
                    Production *newProd = new Production(stmt);
                    prod_curr->next = newProd;  // Link the new production
                    rc = true;  // New production added
                    break;
                }

                // Move to the next production in the list
                prod_curr = prod_curr->next;
            }
            break;  // Exit once the correct non-terminal is found and processed
        }

        // Move to the next non-terminal in the list
        nt_curr = nt_curr->next;
    }

    return rc;
}
*/