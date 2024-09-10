// Chris, Gorana, Lian, and Price  9/6/2024
// program: first
// File: first.h


#ifndef first_H
#define first_H

#include <string>
#include <unordered_map>
#include <vector>

class productions {
    private:
	// Dictionary to store productions
	std::unordered_map<char, std::vector<std::string>> productionRules;  

    public:
	// Reads grammar from a file
	void readGrammar();
	// Pre-conditions:
	// Post-conditions:

	// Stores productions in a data structure (dictionary?)
	void storeProductions();
	// Pre-conditions:
	// Post-conditions:

	// Prints the stored productions
	void printProductions();
	// Pre-conditions:
	// Post-conditions:
};

#endif
