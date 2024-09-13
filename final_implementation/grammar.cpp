#include "grammar.h"

grammar::grammar(string filepath){
    n_root = NULL;
    t_root = NULL;
    start_symbol = NULL;

    parse_grammar_file(filepath);
}

grammar::~grammar(){
    delete_non_terminals(n_root);
    delete_terminals(t_root);
}

bool grammar::is_non_terminal(string s){
    non_terminal *n_curr = n_root;
    bool rc = false;
    while (n_curr != NULL) {
        if (n_curr->sym == s) {
            rc = true;
            break;
        }
        n_curr = n_curr->next;
    }
    return rc;
}

bool grammar::add_non_terminal(char c){
    non_terminal *n_curr = n_root;
    bool rc = false;

    if (n_root == NULL){
        non_terminal *n_new = new non_terminal(string(1,c));
        n_new->next = NULL;
        n_root = n_new;
        if (start_symbol == NULL) {
            start_symbol = n_new;
        }
        rc = true;
    } else {
        while (n_curr != NULL){

            if (n_curr->sym == string(1, c)) {
                break; 
            }
        
            if (n_curr->next == NULL){
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

bool is_delimiter(char c) {
    return (c == '|' || c == ';');  
}

bool grammar::add_production(string n_term, string stmt){
    non_terminal *n_curr = n_root;
    bool rc = false;

    while(n_curr != NULL){
        if (n_curr->sym == n_term){
            production *p_curr = n_curr->p_root;

            if(p_curr == NULL){
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

    string term = "";
    for (size_t i = 0; i < stmt.length(); i++) {
        char c = stmt[i];

        term += c;

        if (i == stmt.length() - 1 || is_delimiter(stmt[i + 1])) {
            
            if (!is_non_terminal(term)) {
                for (char c : term) {
                    add_terminal(c);
                }
            }
            term = "";
        }
    }

    return rc;
}

void grammar::delete_non_terminals(non_terminal* &root){
    while(root != NULL){
        non_terminal *n_next = root->next;
        delete root;
        root = n_next;
    }
}

void grammar::delete_terminals(terminal* &root){
    while (root != NULL){
        terminal *t_next = root->next;
        delete root;
        root = t_next;
    }
}

//Helper Function
void remove_white_spaces(std::string &str) {
    size_t pos;
    while ((pos = str.find(' ')) != std::string::npos) {
        str.erase(pos, 1); 
    }
}

bool grammar::parse_grammar_file(string filepath){
    ifstream file(filepath);

    if(!file.is_open()){
        throw "Error opening grammar file. Check if it exists";
    }

    string line;
    while (getline(file, line)) {

        remove_white_spaces(line);

        size_t arrowPos = line.find("->");
        size_t semicolonPos = line.find(";");

        if (arrowPos == string::npos || semicolonPos == string::npos) continue; 

        
        string nonTerminal = line.substr(0, arrowPos);
        for (char c : nonTerminal) {
            add_non_terminal(c);
        }

        string rhs = line.substr(arrowPos + 2, semicolonPos - (arrowPos + 2));

        
        size_t pos = 0;
        while ((pos = rhs.find("|")) != string::npos) {
            string production = rhs.substr(0, pos);
            add_production(nonTerminal, production);
            rhs.erase(0, pos + 1);  
        }

        if (!rhs.empty()) {
            add_production(nonTerminal, rhs);
        }
    }

    file.close();
    clean_terminal_list();
    return true;
}

void grammar::display_start_symbol() {
    if (start_symbol != NULL ) {
        cout << "Start Symbol: " << start_symbol->sym << endl;
    } else {
        cout << "No start symbol defined." << endl;
    }
}

void grammar::display_non_terminals() {
    non_terminal *n_curr = n_root;
    cout << "Non-Terminals: { ";
    while (n_curr != NULL) {
        cout << n_curr->sym << " ";
        n_curr = n_curr->next;
    }
    cout << "}" << endl;
}

void grammar::display_terminals() {
    terminal *t_curr = t_root;
    cout << "Terminals: { ";
    while (t_curr != NULL) {
        cout << t_curr->sym << " ";
        t_curr = t_curr->next;
    }
    cout << "}" << endl;
}

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