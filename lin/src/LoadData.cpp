#include "LoadData.h"

bool loadUAVModels(std::vector<UAVmodel*> uavs)
{



	std::vector<std::string> Acontent;
	std::vector<std::string> Bcontent;



	bool sucess = (getContentFromFile(AFILENAME, Acontent)
		&& getContentFromFile(BFILENAME, Bcontent));

	sucess = sucess &&
		(fillData(uavs, Acontent, Bcontent));

	return sucess;
}

bool getContentFromFile(std::string filename, std::vector<std::string> &holder)
{

	std::ifstream file;

	bool sucess = false;
	int attemptsLeft = ATTEMPTS;

	while (!sucess && attemptsLeft > 0) {

		sucess = true;
		file.clear();
		try
		{
			file.open(filename);

		}
		catch (const std::exception&)
		{
			sucess = false;
			continue;
		}

		if (file.fail())
			sucess = false;
	}

	if (attemptsLeft == 0)
	{
		return false;
	}

	std::string tmpInput = "";

	while (std::getline(file, tmpInput)) {

		holder.push_back(tmpInput);
	}

	return true;
}


std::vector<latLongSet> splitData(std::vector<std::string> data) {

	if (data.size() == 0)
		return std::vector<latLongSet>();

	int n = strToInt(splitStringSimple(data[0])[0]); //n of UAVs

	if (data.size() != n * 10 + 1)
		return std::vector<latLongSet>();

	std::vector<latLongSet> result;
	latLongSet tmpResult;

	for (int i = 0; i < n; i++) {

		for (int j = 0; j < 5; j++) {

			tmpResult.lat.push_back(data[i * 5 + j + 1]);
			tmpResult.longd.push_back(data[i * 5 + j + 6]);

		}

		for (int j = 0; j < 10; j++){

			tmpResult.complete.push_back(data[i * 5 + j + 1]);
		}

		result.push_back(tmpResult);

		tmpResult.lat.clear();
		tmpResult.longd.clear();
		tmpResult.complete.clear();
	}

	return result;

}

bool fillData(std::vector<UAVmodel*> uavs, std::vector<std::string> A, std::vector<std::string> B)
{

	std::vector<latLongSet> Asplit = splitData(A);
	std::vector<latLongSet> Bsplit = splitData(B);

	if (Asplit.size() == 0 || Asplit.size() != Bsplit.size() || Asplit.size() != uavs.size())
		return false;

	std::vector<latLongSet>::iterator Ait = Asplit.begin();
	std::vector<latLongSet>::iterator Bit = Bsplit.begin();

	for (int i = 0; i < Asplit.size(); i++) {

		uavs[i]->fillA(Ait->complete);
		uavs[i]->fillB(Bit->complete);

		Ait++;
		Bit++;
	}

	return true;
}

int getNumberOfUAVs()
{
	std::vector<std::string> tmp;

	if (!getContentFromFile(AFILENAME, tmp))
		return 0;

	if (tmp.size() == 0)
		return 0;

	return strToInt(splitStringSimple(tmp[0])[0]);
}
