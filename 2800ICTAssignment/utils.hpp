#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <climits>

extern const int SEED;

int getValidatedInt(const std::string& prompt, int min = INT_MIN, int max = INT_MAX);
std::string getNonEmptyLine(const std::string& prompt);

#endif
