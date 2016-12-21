#include "UAVmodel.h"


UAVmodel::UAVmodel()
{

	A_lateral = std::vector<std::vector<double> >(5, std::vector<double>(5));
	A_longditudinal = std::vector<std::vector<double> >(5, std::vector<double>(5));
	B_lateral = std::vector<std::vector<double> >(5, std::vector<double>(2));
	B_longditudinal = std::vector<std::vector<double> >(5, std::vector<double>(2));
}

UAVmodel::UAVmodel(std::vector<std::string> A, std::vector<std::string> B) : UAVmodel()
{

	fillA(A);
	fillB(B);
}

UAVmodel::~UAVmodel()
{



}

void UAVmodel::fillA(std::vector<std::string> data)
{


	int i = 0;
	int j = 0;
	double tmpD;
	std::vector<std::string> tmpVec;

	for (std::vector<std::string>::iterator it = data.begin(); it != data.end(); it++) {

		j = 0;
		tmpVec = splitString(*it);

		for (std::vector<std::string>::iterator itInner = tmpVec.begin(); itInner != tmpVec.end(); itInner++) {

			tmpD = strToDouble(*itInner);

			if (i < 5)
				A_lateral[i][j] = tmpD;
			else
				A_longditudinal[i-5][j] = tmpD;

			j++;
		}

		i++;
	}

}

void UAVmodel::fillB(std::vector<std::string> data)
{

	int i = 0;
	int j = 0;
	double tmpD;
	std::vector<std::string> tmpVec;

	for (std::vector<std::string>::iterator it = data.begin(); it != data.end(); it++) {

		j = 0;
		tmpVec = splitString(*it);

		for (std::vector<std::string>::iterator itInner = tmpVec.begin(); itInner != tmpVec.end(); itInner++) {

			tmpD = strToDouble(*it);

			if (i < 5)
				B_lateral[i][j] = tmpD;
			else
				B_longditudinal[i-5][j] = tmpD;

			j++;
		}

		i++;
	}

}
