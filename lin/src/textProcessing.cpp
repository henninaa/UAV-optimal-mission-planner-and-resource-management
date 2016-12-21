
#include <vector>
#include <string>
#include "textProcessing.h"
#include "Utill.h"

enum spiEnum { init, none, alpha, i, idot, f, space, sign, saveMark, special, specialFirst, func };

std::vector<std::string> splitString(std::string str, bool withSpace) {

	bool markSpace = true;

	std::string tmpStr = "";
	std::string preStr = "";
	std::vector<std::string> result;

	std::string::iterator it = str.begin();

	spiEnum state = init;

	while ( it != str.end()) {

		switch (state) {

		case init:
			state = none;
			break;
		case none:

			if (isdigit(*it)) {

				state = i;
				tmpStr += *it;
				it++;

			}
			else if (isalpha(*it)) {

				state = alpha;
				tmpStr += *it;
				it++;

			}
			else if (*it == SAVEFILEVARIABLEPREFIX) { // Save file variables
				markSpace = false;
				state = saveMark;
				tmpStr = *it;
				it++;
			}
			else if (*it == SPECIALCHARPREFIX) { //Special characters Ex. SPECIALCHARPREFIX SPECIALCHARPREFIX = space

				state = specialFirst;
				tmpStr += *it;
				it++;

			}
			else if (*it == INGAMEVARFUNCCHAR) { // In game variables or function

				state = specialFirst;
				tmpStr += *it;
				it++;

			}
			else if (*it == INTEPRETATIONCHAR) { //Interpretations (Math, int bool) Ex. +int(5) or +float(5+10)

				state = specialFirst;
				tmpStr += *it;
				it++;

			}
			else if (*it == COMMENTCHAR) { //comments

				state = specialFirst;
				tmpStr += *it;
				it++;

			}
			else if(isspace(*it)) {
				if (markSpace)
					state = space;
				else
					it++;
			}
			else if (!isalnum(*it)) {

				state = sign;

			}
			else {
				it++;
			}

			break;
		case alpha:

			if (isalpha(*it)) {

				tmpStr += *it;
				it++;
			}
			else {

				result.push_back(tmpStr);
				tmpStr = "";
				state = none;
			}

			break;
		case i:

			if (*it == ',' || *it == '.') {

				preStr =  *it;
				it++;
				state = idot;
			}
			else if (isdigit(*it)) {

				tmpStr += *it;
				it++;
			}
			else {
				
				result.push_back(tmpStr);
				tmpStr = "";
				state = none;
			}

			break;
		case idot:

			if (isdigit(*it)) {

				tmpStr += preStr;
				preStr = "";
				state = f;
			}
			else {
				result.push_back(tmpStr);
				tmpStr = "";
				result.push_back(preStr);
				preStr = "";
				state = none;
			}

			break;
		case f:

			if (isdigit(*it) || *it == '+' || *it == '-' || *it == 'e') {
				tmpStr += *it;
				it++;
			}
			else {
				result.push_back(tmpStr);
				tmpStr = "";
				state = none;
			}

			break;
		case space:
			tmpStr = SPECIALCHARPREFIX;
			tmpStr += SPACECHAR;
			if (withSpace) result.push_back(tmpStr);
			tmpStr = "";
			it++;
			state = none;

			break;
		case saveMark:
			
			if (*it == SAVEFILEVARIABLEPREFIX) {
				tmpStr += SAVEFILEVARIABLEPREFIX;
				it++;
			}
			else {
				state = none;
				result.push_back(tmpStr);
				tmpStr = "";
			}
			
			break;
		case sign:

			tmpStr += *it;
			result.push_back(tmpStr);
			tmpStr = "";
			it++;
			state = none;

			break;
		case specialFirst:

			if (isspace(*it)) {
				state = none;
			}
			else {
				tmpStr += *it;
				it++;
				state = special;
			}

			break;
		case special:

			if (*it == '(') {
				tmpStr += *it;
				state = func;
				it++;
			}
			else if (!isalnum(*it)) {
				result.push_back(tmpStr);
				tmpStr == "";
			}
			else {
				tmpStr += *it;
				it++;
			}

			break;
		case func:

			if (*it == ')') {
				tmpStr += *it;
				result.push_back(tmpStr);
				tmpStr = "";
				it++;
				state = none;
			}
			else {
			
				tmpStr += *it;
				it++;

			}

		}

	}


	if (tmpStr.size() != 0) {
		result.push_back(tmpStr);
	}

	switch (state) {

	case init:

		break;
	case none:

		break;
	case alpha:

		break;
	case i:

		break;
	case idot:

		result.push_back(preStr);

		break;
	case f:

		break;
	case space:

		break;
	case sign:

		break;
	case special:

		break;
	case func:

		break;
	}

	return result;

}

std::vector<std::string> splitStringSimple(std::string str, bool withSpace) {

	std::string tmpStr = "";
	std::string preStr = "";
	std::vector<std::string> result;

	std::string::iterator it = str.begin();

	spiEnum state = init;

	while (it != str.end()) {

		switch (state) {

		case init:
			state = none;
			break;
		case none:

			if (isdigit(*it)) {

				state = i;
				tmpStr += *it;
				it++;

			}
			else if (isalpha(*it)) {

				state = alpha;
				tmpStr += *it;
				it++;

			}

			else if (isspace(*it)) {

				state = space;
			}
			else if (!isalnum(*it)) {

				state = sign;

			}
			else {
				it++;
			}

			break;
		case alpha:

			if (isalpha(*it)) {

				tmpStr += *it;
				it++;
			}
			else {

				result.push_back(tmpStr);
				tmpStr = "";
				state = none;
			}

			break;
		case i:

			if (*it == ',' || *it == '.') {

				preStr = *it;
				it++;
				state = idot;
			}
			else if (isdigit(*it)) {

				tmpStr += *it;
				it++;
			}
			else {

				result.push_back(tmpStr);
				tmpStr = "";
				state = none;
			}

			break;
		case idot:

			if (isdigit(*it)) {

				tmpStr += preStr;
				preStr = "";
				state = f;
			}
			else {
				result.push_back(tmpStr);
				tmpStr = "";
				result.push_back(preStr);
				preStr = "";
				state = none;
			}

			break;
		case f:

			if (isdigit(*it)) {
				tmpStr += *it;
				it++;
			}
			else {
				result.push_back(tmpStr);
				tmpStr = "";
				state = none;
			}

			break;
		case space:

			if (withSpace) result.push_back("\\s");
			tmpStr = "";
			it++;
			state = none;

			break;
		case sign:

			tmpStr += *it;
			result.push_back(tmpStr);
			tmpStr = "";
			it++;
			state = none;

			break;


		}
	}


	if (tmpStr.size() != 0) {
		result.push_back(tmpStr);
	}

	switch (state) {

	case init:

		break;
	case none:

		break;
	case alpha:

		break;
	case i:

		break;
	case idot:

		result.push_back(preStr);

		break;
	case f:

		break;
	case space:

		break;
	case sign:

		break;
	case special:

		break;
	case func:

		break;
	}

	return result;

}

std::string mergeString(std::vector<std::string> vec) {

	textPack txt;
	txt.txt = vec;
	return mergeString(txt);

}

std::string mergeString(textPack txt) {

	std::vector<std::string> vec = txt.txt;

	std::string tmpStr = "";
	std::string result = "";

	std::string specialCharTmp;

	std::vector<std::string>::iterator it = vec.begin();

	spiEnum state = init;

	while (it != vec.end()) {

		if (it->size() == 0) {
			it++;
			continue;
		}

		switch (state) {

		case init:
			state = none;
			break;
		case none:

			if ((*it)[0] == SPECIALCHARPREFIX) {
				state = special;
			}
			else if ((*it)[0] == INTEPRETATIONCHAR) {
				state = special;
			}
			else if ((*it)[0] == INGAMEVARFUNCCHAR) {
				state = special;
			}
			else if ((*it)[0] == SAVEFILEVARIABLEPREFIX) {
				state = special;
			}
			else if ((*it)[0] == COMMENTCHAR) {
				state = special;
			}
			else {
				state = alpha;
			}

			break;
		case alpha:

			result += *it;
			state = none;
			it++;

			break;
		case i:

			break;
		case idot:

			break;
		case f:

			break;
		case space:

			break;
		case sign:

			break;
		case special:
			specialCharTmp = SPECIALCHARPREFIX;
			specialCharTmp += SPACECHAR;
			if (*it == "\\s") {
				result += " ";
				it++;
				state = none;
			}
			else {
				it++;
				state = none;
			}

			break;
		case func:

			break;
		}

	}

	return result;

}

double calculateDouble(std::vector<std::string> input){

	double result;
	std::vector<std::string>::iterator it;
	std::string tmp = "";

	for (it = input.begin(); it != input.end(); it++) {

		tmp += *it;

	}

	result = strToDouble(tmp);

	return result;
}

int calculateInt(std::vector<std::string> input) {

	int result;
	std::vector<std::string>::iterator it;
	std::string tmp = "";

	for (it = input.begin(); it != input.end(); it++) {

		tmp += *it;

	}

	result = strToInt(tmp);

	return result;
}

bool calculateBool(std::vector<std::string> input) {

	bool result;
	std::vector<std::string>::iterator it;
	std::string tmp = "";

	for (it = input.begin(); it != input.end(); it++) {

		tmp += *it;

	}

	return tmp == "true";
}

std::string mergeWithSpace(std::string first, std::string second)
{

	return first + SPECIALCHARPREFIX + SPACECHAR + second;
}
