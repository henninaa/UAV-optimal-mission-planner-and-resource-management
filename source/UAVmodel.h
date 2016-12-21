#pragma once
#include <vector>
#include <string>
#include "textProcessing.h"
#include "Utill.h"

class UAVmodel
{
public:
	UAVmodel();
	UAVmodel(std::vector<std::string> A, std::vector<std::string> B);
	~UAVmodel();

	void fillA(std::vector<std::string> data);
	void fillB(std::vector<std::string> data);

private:

	std::vector<std::vector<double> > A_lateral;
	std::vector<std::vector<double> > A_longditudinal;
	std::vector<std::vector<double> > B_lateral;
	std::vector<std::vector<double> > B_longditudinal;

};

