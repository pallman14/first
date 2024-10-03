// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: grammar.h
// Grammar.cpp The program builds a structure of linked lists to store non-terminals, 
// terminals, and their corresponding productions, allowing for grammar parsing 
// and printing results.

#ifndef GRAMMAR_H
#define GRAMMAR_H

#include "non_terminal.h"
#include "terminal.h"
#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <sstream> // Include this for string parsing

using namespace std;

class grammar {
    private:
        non_terminal *n_root; //define the root for the non-terminal linked list
        terminal *t_root; //define the root for the terminal linked list
        non_terminal *start_symbol; //define the start-symbols linked list

        // Checks if a given string represents a non-terminal.
        bool is_non_terminal(string c);
        // Pre-conditions: The string should be a valid symbol
        // Post-condtions: Returns true if the string corresponds to an existing 
        // non-terminal in the grammar.

        // Adds a new non-terminal to the grammar.
        bool add_non_terminal(char c);
        // Pre-conditions: 'c' should be a valid character representing a non-terminal.
        // Post-condtions: Adds the character as a non-terminal in the grammar's linked list if 
        // it doesn't already exist.

        // Adds a new terminal to the grammar.
        bool add_terminal(char c);
        // Pre-conditions: 'c' should be a valid character representing a terminal.
        // Post-condtions: Adds the character as a terminal in the grammar's linked list if 
        // it doesn't already exist.

        // Parses the grammar from a file.
        bool parse_grammar_file(string filepath);
        // Pre-conditions: The file must contain grammar rules in the correct format.
        // Post-condtions: Creates the necessary non-terminals, terminals, and productions.

        // Deletes the entire linked list of non-terminals.
        void delete_non_terminals(non_terminal* &root);
        // Pre-conditions: `root` should point to a valid non-terminal linked list.
        // Post-condtions: Clears all of non-terminal linked list.

        // Deletes the entire linked list of terminals.
        void delete_terminals(terminal* &root);
        // Pre-conditions: `root` should point to a valid terminal linked list.
        // Post-condtions: Clears all of terminal linked list.

        // Adds a production rule.
        bool add_production(string n_term, string stmt);
        // Pre-conditions: `n_term` should be a valid non-terminal symbol,
        // and `stmt` should represent the rhs of the production.
        // Post-condtions: Adds the production rule

        // Cleans the terminal list by removing duplicates or symbols that should be non-terminals.
        void clean_terminal_list();
        // Pre-conditions: Terminal ist cannot be empty.
        // Post-condtions: Removes any terminals that are also present as non-terminals.

        // Finds First() for every non-terminal and terminal
        // set<string> find_first(string symbol);
        int find_first(const std::string &symbol, std::string first_set[], int &size);
        // Pre-conditions: 
        // Post-condtions: 
    public:
        // Constructor to initialize the grammar from a file.
        grammar(string filepath);
        // Pre-conditions: `filepath` should be a valid path to a file containing grammar rules.
        // Post-condtions: Initializes the grammar, including non-terminals, terminals, and productions.
        // Also Parses the file to build the grammar structure.

        // Destructor to free all dynmaically allocated memory
        ~grammar();
        // Pre-conditions: The grammar object must have been created.
        // Post-condtions: Frees all memory allocated for non-terminals, terminals, and productions.

        // Displays the list of terminals in the grammar.
        void display_terminals();
        // Pre-conditions: The terminal list cannot be empty.
        // Post-condtions: Prints the list of terminals.

        // Displays the list of non-terminals in the grammar.
        void display_non_terminals();
        // Pre-conditions: The non-terminal list cannot be empty.
        // Post-condtions: Prints the list of non-terminals.

        // Displays the production rules in the grammar.
        void display_productions();
        // Pre-conditions: The grammar must have non-terminals with productions.
        // Post-condtions: Prints the production rules.

        // Displays the start symbol of the grammar.
        void display_start_symbol();
        // Pre-conditions: The start symbol must have been defined.
        // Post-condtions: Prints the start symbol.

        // Displays all the FIRST() found for terminals and non terminals
        void print_first_sets();
        // Pre-conditions: 
        // Post-condtions: 

};

#endif
