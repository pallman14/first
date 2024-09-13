#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <string>

using namespace std;

class Production {
    public:
        string stmt;  // The right-hand side of the production
        Production *next;  // Link to the next production (if any)

        // Constructor to initialize the production
        Production(string statement);

        // Destructor
        ~Production();
};

#endif
