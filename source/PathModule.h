#pragma once
#include <ampl/ampl.h>
#include <vector>
#include <iostream>

#define MODEL	"amplModel/model.mod"
#define DATA	"amplModel/model.dat"
#define DATACX	"amplModel/chix.dat"
#define DATACY	"amplModel/chiy.dat"
#define DATACZ	"amplModel/chiz.dat"

class PathModule
{
public:
	PathModule();
	~PathModule();

	void run(std::vector<std::vector<double> > waypoints);
	std::vector<std::vector<std::vector<double> > > getPath();
	bool isDone() { return !ampl.isBusy(); }

private:

	class MyInterpretIsOver : public ampl::Runnable {
	public:
		void run() {
			std::cout << "solved";
		}
	} isOverHandler;

	ampl::AMPL ampl;
	std::vector<std::vector<std::vector<double> > > path;

	void modifyWp(std::vector<std::vector<double> > waypoints);

};

