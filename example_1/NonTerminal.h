#ifndef NONTERMINAL_H
#define NONTERMINAL_H

#include <iostream>
#include <cstring>  // For strcpy, strlen

using namespace std;

class NonTerminal {
private:
    char symbol[10];

public:
    NonTerminal(const char* sym);
    const char* getSymbol() const;
    ~NonTerminal();
};

#endif
