#include "FindSupport.hpp"
#include <iostream>

int VectorCheck(std::vector<char>& symbols, char ch) {
    for (unsigned int i = 0; i < symbols.size(); i++){
        if (symbols[i] == ch) return i;
    }
    return -1;
}

void MakeStopList(std::vector<int>& shift, std::vector<char>& symbols, const std::string& pattern) {// Создание стоп-листа
    int l = pattern.length();
    shift.clear();
    symbols.clear();
    shift.push_back(l);
    symbols.push_back('*');
    

    for (int i = l-2; i >= 0; i--) {
        if (VectorCheck(symbols, pattern[i]) == -1) {
            shift.push_back(l-i-1);
            symbols.push_back(pattern[i]);
        }
    }

    if (VectorCheck(symbols, pattern[l-1]) == -1) {
        shift.push_back(l);
        symbols.push_back(pattern[l-1]);
    }

    return;
}