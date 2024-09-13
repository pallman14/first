#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>

using namespace std;

class terminal {
    public:
        string sym;
        terminal *next;

        terminal(string symbol);

        ~terminal();
};

#endif