#ifndef PRODUCTION_H
#define PRODUCTION_H

#include "NonTerminal.h"
#include "Terminal.h"
#include <iostream>

using namespace std;

class Production {
private:
    NonTerminal* lhs;
    char rhs[100];  // C-style array for storing the RHS of the production.

public:
    Production(NonTerminal* lhs, const char* rhs);
    const NonTerminal* getLHS() const;
    const char* getRHS() const;
    ~Production();
};

#endif
