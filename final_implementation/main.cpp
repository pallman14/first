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
