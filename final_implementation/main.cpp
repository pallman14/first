// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: main.cpp
// This file has accepts the argument from the command line, and initializes
// a grammar object, and then displays the start symbol, non terminals, 
// terminals, and production rules.

#include "grammar.h"

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            throw "Usage: ./main <grammar file path>";
        }
        grammar grammar(argv[1]);

        grammar.display_start_symbol();
        grammar.display_non_terminals();
        grammar.display_terminals();
        grammar.display_productions();

    } catch (const char *err) {
        cout << err << endl;
    }

    return 0;
}
