// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: grammar.cpp
// Grammar.cpp The program builds a structure of linked lists to store non-terminals, 
// terminals, and their corresponding productions, allowing for grammar parsing 
// and printing results.

#include "grammar.h"

//constructor for grammar class
// Initializes the grammar object with empty non-terminal and termnial roots and
// no start symbol. 
grammar::grammar(string filepath){
    // Root of non-terminal linked list is set to NULL
    n_root = NULL;
    // Root of terminal linked list is set to NULL
    t_root = NULL;
    // Start symbol is initially NULL    
    start_symbol = NULL;
    // Parse the grammar from the specified file
    parse_grammar_file(filepath);
}

//destructor to handle memory allocation
grammar::~grammar(){
    // Delete the linked list of non-terminals
    delete_non_terminals(n_root);
    // Delete the linked list of terminals
    delete_terminals(t_root);
}

//helper function remove white spaces
void remove_white_spaces(std::string &str) {
    size_t pos;
    // Loop through the string and remove all spaces (' ')
    while ((pos = str.find(' ')) != std::string::npos) {
        // Erase one character at the position of the space
        str.erase(pos, 1); 
    }
}

//helper function to find delimiters
bool is_delimiter(char c) {   
    // Returns true if the character is a delimiter, otherwise false
    return (c == '|' || c == ';');  
}

//function to check non terminal
bool grammar::is_non_terminal(string s){
    // Start at the root of the non-terminal list
    non_terminal *n_curr = n_root;
    bool rc = false;
    // traverses linked list to see if s is a non-terminal already
    while (n_curr != NULL) {
        // If the symbol matches, set rc to true and break
        if (n_curr->sym == s) {
            rc = true;
            break;
        }
        // Move to the next non-terminal in the list
        n_curr = n_curr->next;
    }
    // return true if found and false if not
    return rc;
}

//function to add non terminal symbol to the grammar
bool grammar::add_non_terminal(char c){
    // Start at the root of the non-terminal list
    non_terminal *n_curr = n_root;
    bool rc = false;
    
    //checks if root is NULL, if so it creates the first non-terminal
    if (n_root == NULL){
        non_terminal *n_new = new non_terminal(string(1,c)); //string(1,c) converts char to string 
        n_new->next = NULL;
        // Set the new node as the root
        n_root = n_new;
        if (start_symbol == NULL) {
            start_symbol = n_new; //defines the start symbol as the first non-terminal encountered
        }
        rc = true; // Successfully added
    // if the list is not empty
    } else {
        //traverses list to adds non-terminal to end of linked list
        while (n_curr != NULL){
            // check if non-terminal exists
            if (n_curr->sym == string(1, c)) {
                break; // breaks if non terminal already exists
            }
            if (n_curr->next == NULL){
                //adds new non-terminal to linked list
                non_terminal *n_new = new non_terminal(string(1, c));
                n_new->next = NULL; 
                n_curr->next = n_new;
                // successfully added a new non-terminal
                rc = true;
            }
            // Move to the next node in the list
            n_curr = n_curr->next;
        }
    }
    // Return true if a new non-terminal was added, false if it already existed
    return rc;
}

//function to add terminal symbol to the grammar
bool grammar::add_terminal(char c){
    // Start at the root of the terminal list
    terminal *t_curr = t_root;
    bool rc = false;
    // If the list is empty, create the first terminal
    if(t_root == NULL){
        terminal *t_new = new terminal(string(1,c)); // Convert char to string and create a new terminal
        t_new->next = NULL;
        // Set the new terminal as the root
        t_root = t_new;
        // first terminal is added
        rc = true;
    } else {
        // Traverse the list to check if the terminal already exists
        while (t_curr != NULL){
            if (t_curr->sym == string(1,c)){
                // Terminal already exists so it breaks
                break;
            }          
            if (t_curr->next == NULL){
                // Add new terminal at the end of the list
                terminal *t_new = new terminal(string(1,c));
                t_new->next = NULL;
                t_curr->next = t_new;
                rc = true; // It has been added
            }
            // Move to the next node in the list
            t_curr = t_curr->next;
        }  
    }
    // Return true if a new terminal was added, false if it already existed
    return rc;
}

//function to add production
bool grammar::add_production(string n_term, string stmt){
    non_terminal *n_curr = n_root;
    bool rc = false;
    
    // Traverse the non-terminal list to find the matching non-terminal
    while(n_curr != NULL){
        if (n_curr->sym == n_term){
            // Start at the root of the production list for this non-terminal
            production *p_curr = n_curr->p_root;
            // If no productions exist for this non-terminal, add the first one
            if(p_curr == NULL){
                //creates new production node on the same non-terminal node
                production *p_new = new production(stmt); // Create new production
                n_curr->p_root = p_new;  // Set it as teh root production
                rc = true;  
                break;
            }
            // Traverse the production list to check if the production already exists
            while (p_curr != NULL){
                if(p_curr->stmt == stmt){  // If production already exists
                    rc = false;  // set to false
                }
                
                if (p_curr->next == NULL){
                    //adds the statement to the production node.
                    production *p_new = new production(stmt);
                    p_curr->next = p_new;
                    rc = true;  // Production has been added
                    break;
                }
                
                p_curr = p_curr->next;  // Move to the next production
            }
            break;
        }
        n_curr = n_curr->next;  // Move to the next non-terminal
    }

    //break down string to characters to check if each character is non-terminal.
    string term = "";
    for (size_t i = 0; i < stmt.length(); i++) {
        char c = stmt[i];
        term += c; //appends to the string 'term'

        //delimiter functino checks for | and ; 
        if (i == stmt.length() - 1 || is_delimiter(stmt[i + 1])) {
            // If it's not a non-terminal, add its characters as terminals
            if (!is_non_terminal(term)) {
                //for loop that goes through term string by each character
                for (char c : term) {
                    add_terminal(c);  // Add each character as a terminal
                }
            }
            term = "";  // Reset the term for the next part of the production
        }
    }
    // Return true if a new production was added, false if it already existed
    return rc;
}

//function to delete non-terminals
void grammar::delete_non_terminals(non_terminal* &root){
    // Traverses the linked list
    while(root != NULL){
        non_terminal *n_next = root->next;  // Save the next node
        delete root; // Delete the current node
        root = n_next;  // Move to the next node
    }
}

//function to delete terminals
void grammar::delete_terminals(terminal* &root){
    while (root != NULL){
        terminal *t_next = root->next;
        delete root;
        root = t_next;
    }
}

//function to parse grammar file - tokenize characters, add terminals, add non-terminals, etc
bool grammar::parse_grammar_file(string filepath){
    ifstream file(filepath); //open file 

    //error if file can't be opened
    if(!file.is_open()){
        throw "Error opening grammar file. Check if it exists";
    }

    string line; //line variable to take input line by line
    // read file line by line
    while (getline(file, line)) {
        //remove white spaces since they're not part of grammar or language
        remove_white_spaces(line);

        //find arrow in the line
        size_t arrowPos = line.find("->");

        //find semicolon in the line
        size_t semicolonPos = line.find(";");

        //within the line, if these positions encountered, it skips it.
        if (arrowPos == string::npos || semicolonPos == string::npos) continue; 

        //gets non-terminal - all the characters before the arrow
        string nonTerminal = line.substr(0, arrowPos);
        // Add the non-terminal characters to the grammar
        for (char c : nonTerminal) {
            add_non_terminal(c);
        }

        //gets right hand side - all characters after arrow and before semicolon
        string rhs = line.substr(arrowPos + 2, semicolonPos - (arrowPos + 2));

        size_t pos = 0;

        //traverse rhs characters to add production. skips | symbols
        while ((pos = rhs.find("|")) != string::npos) {
            string production = rhs.substr(0, pos); //get production till position
            add_production(nonTerminal, production); //add production till | symbol
            rhs.erase(0, pos + 1);  //removes the production once processed
        }

        if (!rhs.empty()) {
            add_production(nonTerminal, rhs); //as long as rhs is not empty, add the production to the non-terminal linked list of productions
        }
    }

    file.close();
    clean_terminal_list(); //cleans lists with duplicates of terminals
    // Return true indicating successful parsing
    return true;
}

//function to display start symbol
void grammar::display_start_symbol() {
    if (start_symbol != NULL ) {
        cout << "Start Symbol: " << start_symbol->sym << endl;  // Print start symbol
    } else {
        cout << "No start symbol defined." << endl;  // Error message if no start symbol
    }
}

//function to display non-terminals
void grammar::display_non_terminals() {
    non_terminal *n_curr = n_root;
    cout << "Non-Terminals: { ";
    // Traverse the list and print each non-terminal
    while (n_curr != NULL) {
        cout << n_curr->sym << " ";  // Print non-terminal
        // Move to the next non-terminal in the list
        n_curr = n_curr->next;
    }
    cout << "}" << endl;
}

//function to display terminals
void grammar::display_terminals() {
    terminal *t_curr = t_root;
    cout << "Terminals: { ";
    while (t_curr != NULL) {
        cout << t_curr->sym << " ";
        t_curr = t_curr->next;
    }
    cout << "}" << endl;
}

//function to display productions
void grammar::display_productions() {
    non_terminal *n_curr = n_root;
    // Traverse the list of non-terminals
    while (n_curr != NULL) {
        cout << n_curr->sym << " -> ";  // Print the non-terminal symbol followed by ->
        production *p_curr = n_curr->p_root;  // Start at the root of the production list
        // Traverse
        while (p_curr != NULL) {
            cout << p_curr->stmt;  // Print the production stmt
            if (p_curr->next != NULL) {  // If there are more productions
                cout << " | ";  //separate them with a |
            }
            p_curr = p_curr->next;  // Move to the next production
        }
        cout << ";" << endl;
        n_curr = n_curr->next;  // Move to the next non-terminal in the list
    }
}

//function to clean terminal lists
void grammar::clean_terminal_list() {
    terminal *t_curr = t_root;  // Start at the root of the terminal list
    terminal *t_prev = NULL;  // Pointer to previous node in the list
    
    // traverse the terminal list
    while (t_curr != NULL) {
        if (is_non_terminal(t_curr->sym)) {
            if (t_prev == NULL) {
                t_root = t_curr->next;
                delete t_curr;
                t_curr = t_root;
            } else {
                t_prev->next = t_curr->next;
                delete t_curr;
                t_curr = t_prev->next;
            }
        } else {
            t_prev = t_curr;
            t_curr = t_curr->next;
        }
    }
}

