// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: terminal.cpp
// This file has a constructor to initialize the terminal object. 

#include "terminal.h"

terminal::terminal(string symbol){
    this->sym = symbol;
    next = NULL;
}