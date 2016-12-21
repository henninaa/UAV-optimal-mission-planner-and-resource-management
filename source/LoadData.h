#pragma once
#include <vector>
#include <string>
#include <fstream>
#include "UAVmodel.h"

#define AFILENAME "matlab\\transfer\\A.txt"
#define BFILENAME "matlab\\transfer\\B.txt"
#define ATTEMPTS 10

struct latLongSet
{
	std::vector<std::string> lat;
	std::vector<std::string> longd;
	std::vector<std::string> complete;
};

bool loadUAVModels(std::vector<UAVmodel*> uavs);
bool getContentFromFile(std::string filename, std::vector<std::string> &holder);

std::vector<latLongSet> splitData(std::vector<std::string>);

bool fillData(std::vector<UAVmodel*> uavs, std::vector<std::string> A, std::vector<std::string> B);

int getNumberOfUAVs();