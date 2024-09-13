#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <string>

using namespace std;

class production{
    public:
        string stmt;
        production *next;

        production(string stmt);

        ~production();
};

#endif