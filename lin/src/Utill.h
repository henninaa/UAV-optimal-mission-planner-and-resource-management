#pragma once

#include <vector>
#include <string>
#include <sstream>



bool isInVector(std::vector<std::string> vec, std::string var);
bool isInVector(std::vector<std::uint64_t> vec, uint64_t var);

int strToInt(std::string str);
uint64_t strToInt64(std::string str);
double strToDouble(std::string);
bool strToBool(std::string);

std::string boolToStr(bool var);

std::vector<std::string> splitStringByLine(std::string str);

bool isNumeric(std::string str);