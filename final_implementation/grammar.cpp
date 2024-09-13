// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: grammar.cpp

#include "grammar.h"

//constructor for grammar class
grammar::grammar(string filepath){
    n_root = NULL;
    t_root = NULL;
    start_symbol = NULL;

    parse_grammar_file(filepath);
}

//destructor to handle memory allocation
grammar::~grammar(){
    delete_non_terminals(n_root);
    delete_terminals(t_root);
}

//helper function remove white spaces
void remove_white_spaces(std::string &str) {
    size_t pos;
    while ((pos = str.find(' ')) != std::string::npos) {
        str.erase(pos, 1); 
    }
}

//helper function to find delimiters
bool is_delimiter(char c) {   
    return (c == '|' || c == ';');  
}

//function to check if non terminal
bool grammar::is_non_terminal(string s){
    non_terminal *n_curr = n_root;
    bool rc = false;
    // traverses linked list to see if s is a non-terminal already
    while (n_curr != NULL) {
        if (n_curr->sym == s) {
            rc = true;
            break;
        }
        n_curr = n_curr->next;
    }
    return rc;
}

//function to add non terminal
bool grammar::add_non_terminal(char c){
    non_terminal *n_curr = n_root;
    bool rc = false;
    
    //checks if root is NULL
    if (n_root == NULL){
        non_terminal *n_new = new non_terminal(string(1,c)); //string(1,c) converts char to string
        n_new->next = NULL;
        n_root = n_new;
        if (start_symbol == NULL) {
            start_symbol = n_new; //defines the start symbol as the first non-terminal encountered
        }
        rc = true;
    } else {
        //traverses list to add non-terminal to end of linked list
        while (n_curr != NULL){

            if (n_curr->sym == string(1, c)) {
                break; // breaks if non terminal already exists
            }
        
            if (n_curr->next == NULL){
                //adds new non-terminal to linked list
                non_terminal *n_new = new non_terminal(string(1, c));
                n_new->next = NULL; 
                n_curr->next = n_new;
                rc = true;
            }
            
            n_curr = n_curr->next;
        }
    }
    return rc;
}

//function to add terminal
bool grammar::add_terminal(char c){
    terminal *t_curr = t_root;
    bool rc = false;

    if(t_root == NULL){
        terminal *t_new = new terminal(string(1,c));
        t_new->next = NULL;
        t_root = t_new;
        rc = true;
    } else {
        while (t_curr != NULL){
            if (t_curr->sym == string(1,c)){
                break;
            }

            if (t_curr->next == NULL){
                terminal *t_new = new terminal(string(1,c));
                t_new->next = NULL;
                t_curr->next = t_new;
                rc = true;
            }

            t_curr = t_curr->next;
        }  
    }
    return rc;
}

//function to add production
bool grammar::add_production(string n_term, string stmt){
    non_terminal *n_curr = n_root;
    bool rc = false;

    while(n_curr != NULL){
        if (n_curr->sym == n_term){
            production *p_curr = n_curr->p_root;

            if(p_curr == NULL){
                //creates new production node on the same non-terminal node
                production *p_new = new production(stmt);
                n_curr->p_root = p_new;
                rc = true;
                break;
            }

            while (p_curr != NULL){
                if(p_curr->stmt == stmt){
                    rc = false;
                }

                if (p_curr->next == NULL){
                    //adds the statement to the production node.
                    production *p_new = new production(stmt);
                    p_curr->next = p_new;
                    rc = true;
                    break;
                }
                
                p_curr = p_curr->next;
            }
            break;
        }
        n_curr = n_curr->next;
    }

    //break down string to characters to check if each character is non-terminal.
    string term = "";
    for (size_t i = 0; i < stmt.length(); i++) {
        char c = stmt[i];

        term += c; //appends to the string 'term'

        //delimiter functino checks for | and ; 
        if (i == stmt.length() - 1 || is_delimiter(stmt[i + 1])) {
            
            if (!is_non_terminal(term)) {
                //for loop that goes through term string by each character
                for (char c : term) {
                    add_terminal(c);
                }
            }
            term = "";
        }
    }

    return rc;
}

//function to delete non-terminals
void grammar::delete_non_terminals(non_terminal* &root){
    while(root != NULL){
        non_terminal *n_next = root->next;
        delete root;
        root = n_next;
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
    return true;
}

//function to display start symbol
void grammar::display_start_symbol() {
    if (start_symbol != NULL ) {
        cout << "Start Symbol: " << start_symbol->sym << endl;
    } else {
        cout << "No start symbol defined." << endl;
    }
}

//function to display non-terminals
void grammar::display_non_terminals() {
    non_terminal *n_curr = n_root;
    cout << "Non-Terminals: { ";
    while (n_curr != NULL) {
        cout << n_curr->sym << " ";
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
    while (n_curr != NULL) {
        cout << n_curr->sym << " -> ";
        production *p_curr = n_curr->p_root;
        while (p_curr != NULL) {
            cout << p_curr->stmt;
            if (p_curr->next != NULL) {
                cout << " | ";
            }
            p_curr = p_curr->next;
        }
        cout << ";" << endl;
        n_curr = n_curr->next;
    }
}

//function to clean terminal lists
void grammar::clean_terminal_list() {
    terminal *t_curr = t_root;
    terminal *t_prev = NULL;

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

