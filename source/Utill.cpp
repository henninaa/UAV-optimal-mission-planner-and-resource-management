
#include <vector>
#include <string>
#include "Utill.h"


bool isInVector(std::vector<std::string> vec, std::string var) {

	

	for (std::vector<std::string>::iterator it = vec.begin(); it != vec.end(); it++) {

		if (*it == var) return true;

	}

	return false;
}
/*
bool isInVector(std::vector<uint64_t> vec, uint64_t var) {



	for (std::vector<uint64_t>::iterator it = vec.begin(); it != vec.end(); it++) {

		if (*it == var) return true;

	}

	return false;
}

*/
int strToInt(std::string str) { // inline use in variable.cpp varStr equal.



	try {
		return stoi(str);
	}
	catch (...) {
		return 0;
	}
	return 0;

}
/*
uint64_t strToInt64(std::string str) { // inline use in variable.cpp varStr equal.



	try {
		return std::stoull(str);
	}
	catch (...) {
		return 0;
	}
	return 0;

}
*/
double strToDouble(std::string str) {



	try {
		return std::stod(str);
	}
	catch (...) {
		return 0;
	}
	return 0;

}

bool strToBool(std::string str) {

	if (str == "true") return true;
	else if (str == "True") return true;
	else if (str == "t") return true;
	else if (str == "true") return true;
	else if (str == "TRUE") return true;
	return false;

}

std::string boolToStr(bool var)
{
	if (var) return "true";
	return "false";
}

std::vector<std::string> splitStringByLine(std::string str)
{
	//char* sentence = str.c_str();
	std::stringstream ss(str);
	std::string to;
	std::vector<std::string> result;

	if (str != "")
	{
		while (std::getline(ss, to, '\n')) {
			result.push_back(to);
		}
	}

	return result;
}

bool isNumeric(std::string str)
{
	for (std::string::iterator it = str.begin(); it != str.end(); it++) {
		if (!isdigit(*it)) return false;
	}

	return true;
}
