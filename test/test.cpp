
#include <ampl/ampl.h>
#include <vector>
#include <iostream>

#define MODEL	"model.mod"
#define DATA	"model.dat"
#define DATACX	"chix.dat"
#define DATACY	"chiy.dat"
#define DATACZ	"chiz.dat"


#define DATATM	"diet.mod"
#define DATATD	"diet.dat"

int main(){


	ampl::AMPL ampl;

	ampl.read(MODEL);
	ampl.readData(DATA);
	ampl.readData(DATACX);
	ampl.readData(DATACY);
	ampl.readData(DATACZ);


/*	ampl.readData("diet.mod");
	ampl.readData("DATATD");
*/
	ampl.setOption("solver", "cplex");
	ampl.solve();

	return 0;

}