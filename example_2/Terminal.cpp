#include "Terminal.h"

// Constructor
Terminal::Terminal(char symbol) {
    this->symbol = symbol;
    next = nullptr;
}

// Destructor
Terminal::~Terminal() {
    // No dynamically allocated members to clean up
}
