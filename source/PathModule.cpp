#include "PathModule.h"



PathModule::PathModule()
{

	//path = std::vector<std::vector<double>>(1, std::vector<double>(1, 1));

	ampl.read(MODEL);
	ampl.readData(DATA);
	ampl.readData(DATACX);
	ampl.readData(DATACY);
	ampl.readData(DATACZ);

}


PathModule::~PathModule()
{
}

void PathModule::run(std::vector<std::vector<double> > waypointsInn)
{
	
	modifyWp(waypointsInn);
	
	ampl.setOption("solver", "cplex");
	//ampl.solve();
	
	if (!ampl.isBusy())
		ampl.solveAsync(&isOverHandler);

}

std::vector<std::vector<std::vector<double> > > PathModule::getPath() // result gives [vehicle] [time] [axis]
{

	if (ampl.isBusy())
		return this->path;

	std::vector<std::vector<std::vector<double> > > path;

	ampl::Variable amplVarx = ampl.getVariable("x");
	ampl::Variable amplVary = ampl.getVariable("y");
	ampl::Variable amplVarz = ampl.getVariable("z");
	ampl::DataFrame datax = amplVarx.getValues();
	ampl::DataFrame datay = amplVary.getValues();
	ampl::DataFrame dataz = amplVarz.getValues();

	int n = datax.getRowByIndex(datax.getNumRows()-1)[1].dbl();
	int p = datax.getRowByIndex(datax.getNumRows()-1)[0].dbl();

	path = std::vector<std::vector<std::vector<double> > > (p, std::vector<std::vector<double> >(n, std::vector<double>(3, 0)));
	std::cout << n << " " << p;

	int a = datax.getNumRows()/p -1;
	for (int i = 0; i < a; i++) {	
		
		for(int k = 0; k < p; k++){

			path[k][i][0] = datax.getRowByIndex(i + n*k)[2].dbl();
			path[k][i][1] = datay.getRowByIndex(i + n*k)[2].dbl();
			path[k][i][2] = dataz.getRowByIndex(i + n*k)[2].dbl();
		}
		
	}

	
	this->path = path;
	return path;
}

void PathModule::modifyWp(std::vector<std::vector<double> > waypointsInn)
{

	int n = waypointsInn.size();
	int nc = waypointsInn[0].size();

	if (n==0 || nc != 3) return;

	ampl::Parameter waypoints = ampl.getParameter("waypoints");
	ampl::Parameter W = ampl.getParameter("W");

	double colIndices[] = { 1,2,3 };
	double* rowIndices = new double[n];
	double* waypointData = new double[n*nc];


	for (int i = 0; i < n; i++) {
		rowIndices[i] = i + 1;

		for (int j = 0; j < nc; j++)
			waypointData[j + i * nc] = waypointsInn[i][j];
	}

	ampl::Variant wn(n);

	waypoints.setValues(n, rowIndices, 3, colIndices, waypointData, false);
	W.set(wn);
}
