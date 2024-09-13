#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <cstring>

using namespace std;

class Terminal {
private:
    char symbol[10];

public:
    Terminal(const char* sym);
    const char* getSymbol() const;
    ~Terminal();
};

#endif
