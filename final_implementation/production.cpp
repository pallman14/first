#include "production.h"

production::production(string stmt){
    this->stmt = stmt;
    next = NULL;
}

production::~production(){
    
}