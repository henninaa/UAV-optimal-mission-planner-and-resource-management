#pragma once
#include <ampl\ampl.h>
#include <vector>
#include <iostream>

#define MODEL	"amplModel\\model.mod"
#define DATA	"amplModel\\model.dat"

class PathModule
{
public:
	PathModule();
	~PathModule();

	void run(std::vector<std::vector<double>> waypoints);
	std::vector<std::vector<double>> getPath();

private:

	class MyInterpretIsOver : public ampl::Runnable {
	public:
		void run() {
			std::cout << "solved";
		}
	} isOverHandler;

	ampl::AMPL ampl;
	std::vector<std::vector<double>> path;

	void modifyWp(std::vector<std::vector<double>> waypoints);

};

