#ifndef TERMINAL_H
#define TERMINAL_H

class Terminal {
    public:
        char symbol;  // The symbol for this terminal
        Terminal *next;  // Next terminal in the list

        // Constructor
        Terminal(char symbol);

        // Destructor
        ~Terminal();
};

#endif
