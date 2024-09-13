#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "non_terminal.h"
#include "terminal.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class grammar {
    private:
        non_terminal *n_root; //define the root for the non-terminal linked list
        terminal *t_root; //define the root for the terminal linked list
        non_terminal *start_symbol; //define the start-symbols linked list

        bool is_non_terminal(string c);
        bool add_non_terminal(char c);
        bool add_terminal(char c);
        bool parse_grammar_file(string filepath);

        void delete_non_terminals(non_terminal* &root);
        void delete_terminals(terminal* &root);

        bool add_production(string n_term, string stmt);

        void clean_terminal_list();
    public:
        grammar(string filepath);

        ~grammar();

        void display_terminals();

        void display_non_terminals();

        void display_productions();

        void display_start_symbol();
};

#endif