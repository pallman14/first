// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: terminal.h
// This file has a constructor to initialize the terminal object.

#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>

using namespace std;

class terminal {
    public:
        string sym; //symbol for the terminal
        terminal *next; //pointer to next terminal node

        terminal(string symbol); //constructor for terminal class
};

#endif