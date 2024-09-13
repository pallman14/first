#include "NonTerminal.h"

// Constructor
NonTerminal::NonTerminal(char symbol) {
    this->symbol = symbol;
    prodsRoot = nullptr;
    next = nullptr;
}

// Destructor to clean up production rules
NonTerminal::~NonTerminal() {
    Production *current = prodsRoot;
    while (current != nullptr) {
        Production *nextProd = current->next;
        delete current;
        current = nextProd;
    }
}

// Add a production to the non-terminal
void NonTerminal::addProduction(string stmt) {
    Production *newProd = new Production(stmt);
    if (prodsRoot == nullptr) {
        prodsRoot = newProd;
    } else {
        Production *current = prodsRoot;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newProd;
    }
}
