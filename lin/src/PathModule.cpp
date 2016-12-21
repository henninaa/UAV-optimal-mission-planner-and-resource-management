#include "PathModule.h"



PathModule::PathModule()
{

	//path = std::vector<std::vector<double>>(1, std::vector<double>(1, 1));

	ampl.read(MODEL);
	ampl.read(DATA);

}


PathModule::~PathModule()
{
}

void PathModule::run(std::vector<std::vector<double>> waypointsInn)
{
	
	modifyWp(waypointsInn);

	ampl.setOption("solver", "cplex");
	ampl.solve();
	if (!ampl.isRunning())
		ampl.solveAsync(&isOverHandler);

}

std::vector<std::vector<double>> PathModule::getPath()
{

	if (ampl.isRunning())
		return this->path;

	std::vector<std::vector<double>> path;

	ampl::Variable amplVar = ampl.getVariable("pos");
	ampl::DataFrame data = amplVar.getValues();

	for (int i = 0; i < data.getNumRows(); i++) {

		path.push_back(std::vector<double>());
		
		for (auto v : data.getRowByIndex(0))
			path[i].push_back(v.dbl());
	}

	this->path = path;
	return path;
}

void PathModule::modifyWp(std::vector<std::vector<double>> waypointsInn)
{

	int n = waypointsInn.size();

	ampl::Parameter waypoints = ampl.getParameter("waypoints");
	ampl::Parameter W = ampl.getParameter("W");

	double colIndices[] = { 1,2,3 };
	double* rowIndices = new double[n];
	double* waypointData = new double[n];


	for (int i = 0; i < n; i++) {
		rowIndices[i] = i + 1;

		for (int j = 0; j < 3; j++)
			waypointData[j + i * 3] = waypointsInn[i][j];
	}

	waypoints.setValues(n, rowIndices, 3, colIndices, waypointData, false);
	W.setValues(new double(1), double(1));
}
