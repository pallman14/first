#include "Grammar2.h"

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

// Display non-terminals in reverse order
void Grammar::displayNonTerminals() {
    cout << "Non-Terminals: { ";
    printNonTerminalsReverse(nonTerminalRoot);  // Start the recursive printing
    cout << "}" << endl;
}

// Recursive function to print non-terminals in reverse order
void Grammar::printNonTerminalsReverse(NonTerminal *current) {
    if (current == nullptr) return;

    // Recursively print the next non-terminal first
    printNonTerminalsReverse(current->next);

    // Then, print the current non-terminal
    cout << current->symbol << " ";
}

// Display terminals in reverse order
void Grammar::displayTerminals() {
    cout << "Terminals: { ";
    printTerminalsReverse(terminalRoot);  // Start the recursive printing
    cout << "}" << endl;
}

// Recursive function to print terminals in reverse order
void Grammar::printTerminalsReverse(Terminal *current) {
    if (current == nullptr) return;

    // Recursively print the next terminal first
    printTerminalsReverse(current->next);

    // Then, print the current terminal
    cout << current->symbol << " ";
}

// Display productions in reverse order for all non-terminals
void Grammar::displayProductions() {
    NonTerminal *current = nonTerminalRoot;
    while (current != nullptr) {
        cout << current->symbol << " -> ";
        printProductionsReverse(current->prodsRoot);  // Recursively print productions in reverse order
        cout << ";" << endl;
        current = current->next;
    }
}

// Recursive function to print productions in reverse order
void Grammar::printProductionsReverse(Production *current) {
    if (current == nullptr) return;

    // Recursively print the next production first
    printProductionsReverse(current->next);

    // Then, print the current production
    cout << current->stmt;
    if (current->next != nullptr) cout << " | ";
}

// Display start symbol
void Grammar::displayStartSymbol() {
    if (startSymbol != nullptr) {
        cout << "Start Symbol: " << startSymbol->symbol << endl;
    }
}

// First set placeholder (implement logic)
string Grammar::first(char c) {
    return "";  // Placeholder for first set logic
}

// Display first sets (placeholder for now)
void Grammar::displayFirstSets() {
    NonTerminal *current = nonTerminalRoot;
    while (current != nullptr) {
        cout << "First(" << current->symbol << ") = " << first(current->symbol) << endl;
        current = current->next;
    }
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
