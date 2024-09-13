#include "non_terminal.h"

non_terminal::non_terminal(string sym){
    this->sym = sym;
    p_root = NULL;
    next = NULL;
}

non_terminal::~non_terminal(){
    production *p_curr = p_root;
    while(p_curr != NULL){
        production *p_next = p_curr->next;
        delete p_curr;
        p_curr = p_next;
    }
}

void non_terminal::addProduction(string stmt){
    production *p_new = new production(stmt);
    if (p_root == NULL) {
        p_root = p_new;
    } else {
        production *p_curr = p_root;
        while (p_curr->next != NULL){
            p_curr = p_curr->next;
        }
        p_curr->next = p_new;
    }
}