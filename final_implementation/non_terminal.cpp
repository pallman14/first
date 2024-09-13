// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: non_terminal.cpp
// This file has a constructor to initialize the non-terminal object. Destructor to
// clear memory. And an a function to add a production to the list of productions.

#include "non_terminal.h"

// Constructor
non_terminal::non_terminal(string sym){
    // Set the non-terminal symbol to the string.
    this->sym = sym;
    // Initialize the root of the production list as NULL.
    p_root = NULL;
    // Initialize the next pointer in the linked list to NULL
    next = NULL;
}

// Destructor
non_terminal::~non_terminal(){
    // Start from the root of the production list.
    production *p_curr = p_root;
    // Traverse the list of productions and delete each production.
    while(p_curr != NULL) {
        // Store the next production before deleting the current one.
        production *p_next = p_curr->next;
        delete p_curr;    // Delete current production.
        p_curr = p_next;  // Move to next production.
    }
}

// Adds a production to the non-terminal's list of productions.
void non_terminal::addProduction(string stmt){
    production *p_new = new production(stmt); // Create a new production node with the given statement.
    // If the production list is empty
    if (p_root == NULL) {
        // make the new production the root.
        p_root = p_new;
    } else {
        // Traverse to the end of the production list.
        production *p_curr = p_root;
        while (p_curr->next != NULL){
            p_curr = p_curr->next;
        }
        // Append the new production to the end of the list.
        p_curr->next = p_new;
    }
}
