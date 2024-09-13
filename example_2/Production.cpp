#include "Production.h"

// Constructor
Production::Production(string statement) {
    stmt = statement;
    next = nullptr;
}

// Destructor
Production::~Production() {
    // No dynamically allocated members to clean up
}
