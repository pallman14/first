#include "Terminal.h"

Terminal::Terminal(const char* sym) {
    strcpy(symbol, sym);
}

const char* Terminal::getSymbol() const {
    return symbol;
}

Terminal::~Terminal() {
    // No dynamic memory to clean up.
}
