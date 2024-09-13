// Chris, Gorana, Lian, and Price
// GCSC544
// Project: first
// File: production.h
// This file has a constructor to initialize the production object

#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <string>

using namespace std;

class production{
    public:
        string stmt; //production statement is stored as a string
        production *next;

        production(string stmt); //constructor for production class
};

#endif