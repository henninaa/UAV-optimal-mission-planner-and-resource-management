#include "LoadData.h"
#include "UAVmodel.h"
#include <vector>
#include "PathModule.h"



int main() {

	PathModule path;

	std::vector<std::vector<double>> wp = std::vector<std::vector<double>>(2, std::vector<double>(3, 100));
	wp[1][1] = 200;

	path.run(wp);

	int n = getNumberOfUAVs();

	std::vector<UAVmodel*> uavs;

	for (int i = 0; i < n; i++) {
		uavs.push_back(new UAVmodel());
	}

	loadUAVModels(uavs);

	return 0;
}