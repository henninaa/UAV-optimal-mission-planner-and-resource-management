#pragma once

#include <vector>
#include <string>

class stringData;

//--------------Defines---------------

#define SAVEFILEVARIABLEPREFIX '#'


#define SPECIALCHARPREFIX '\\'
#define SPACECHAR 's'

#define INGAMEVARFUNCCHAR '$'
#define INTEPRETATIONCHAR '+'
#define COMMENTCHAR '%'

#define VARIABLEMARKER "#"
#define SUBSECTIONMARKER "##"
#define SECTIONMARKER "###"

//--------------Stuff-----------------

typedef std::vector < std::vector<std::string>> vvecStr;

struct textPack {

	std::vector<std::string> txt;
	std::vector<int> is;
	std::vector<double> fs;
	std::vector<bool> bs;
};

//--------------Functions--------------

std::vector<std::string> splitString(std::string str, bool withSpace = false);
std::vector<std::string> splitStringSimple(std::string str, bool withSpace = false);

std::string mergeString(std::vector<std::string> vec);
std::string mergeString(textPack txt);

double calculateDouble(std::vector<std::string> input);
int calculateInt(std::vector<std::string> input);
bool calculateBool(std::vector<std::string> input);

std::string mergeWithSpace(std::string first, std::string second);


//--------------Classes----------------

class stringData {



public:

	stringData() { };

};