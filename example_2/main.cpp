#include "Grammar2.h"

int main(int argc, char *argv[]) {
    try {
        if (argc < 2) {
            throw "Usage: ./main <grammar file path>";
        }
        Grammar grammar(argv[1]);

        grammar.displayStartSymbol();
        grammar.displayNonTerminals();
        grammar.displayTerminals();
        grammar.displayProductions();
        // grammar.displayFirstSets();

    } catch (const char *err) {
        cout << err << endl;
    }

    return 0;
}
