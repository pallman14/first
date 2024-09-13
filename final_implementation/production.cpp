// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: production.cpp
// This file has a constructor to initialize the production object node 
// as part of the linked list

#include "production.h"

production::production(string stmt){
    this->stmt = stmt;
    next = NULL;
}
