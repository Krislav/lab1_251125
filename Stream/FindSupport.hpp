#pragma once
#include <vector>
#include <string>

int VectorCheck(std::vector<char>& symbols, char ch);
void MakeStopList(std::vector<int>& shift, std::vector<char>& symbols, const std::string& pattern);