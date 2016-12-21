#include "LoadData.h"
#include "UAVmodel.h"
#include <vector>
#include "PathModule.h"
#include <iostream>


void printUAVpath(std::vector<std::vector<std::vector<double> > > path, int n){

std::cout << path[n].size() << "\n";
std::cout << path[0][0].size() << "\n";

for (std::vector<std::vector<double> >::iterator it = path[n].begin(); it != path[n].end(); it++){

	for(std::vector<double>::iterator itI = it->begin(); itI != it->end(); itI++){
		std::cout << *itI << " ";
	}
	std::cout << "\n";

}

}

int main() {

	PathModule path;

	std::vector<std::vector<double> > wp = std::vector<std::vector<double> >(3, std::vector<double>(2, 100));
	wp[1][1] = 200;
	//wp[2][2] = 200;

	path.run(wp);

	bool fin = false;
	std::vector<std::vector<std::vector<double> > >pathWp;

	std::cout << "t";
	while (!fin){
		if (path.isDone()){
			std::cout << "t";
			pathWp = path.getPath();
			fin = true;
			std::cout << "DONE";
		}

	}

	printUAVpath(pathWp, 1);

	/*
	int n = getNumberOfUAVs();

	std::vector<UAVmodel*> uavs;
	
	for (int i = 0; i < n; i++) {
		uavs.push_back(new UAVmodel());
	}

	loadUAVModels(uavs);
	*/
	return 0;
}