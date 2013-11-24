#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <cctype> 
#include <cmath>
#include "libscat.h" //@ Cannot find the header file called "libscat.h"

#include "Find.h"

int main(int argc, char* argv[])
try
{
	//--
	//-- Your code goes here.
	//--
	using namespace std;
	using namespace scat;
	string baseName;
	if (argc == 1) {
		baseName = "Test_ANITA_5000";
	}
	else if (argc == 2) {
		baseName = argv[1];
	}
	else {
		cerr << "Bad command line:";
		for (int i = 0; i<argc; ++i) {
			cerr << " " << argv[i];
		}
		cerr << endl;
		throw exception();
	}

	string ifileName;
	string nfileName;
	string gfileName;
	ifileName = baseName + ".csv";
	nfileName = baseName + ".neutron.txt";
	gfileName = baseName + ".gamma.txt";

	ifstream iFile(ifileName.c_str());
	ofstream nFile(nfileName.c_str());
	ofstream gFile(gfileName.c_str());
	if (!iFile) {
		cerr << "Can't open file:" << ifileName << endl;
		throw exception();
	}
	if (!nFile) {
		cerr << "Can't open file:" << nfileName << endl;
		throw exception();
	}
	if (!gFile) {
		cerr << "Can't open file:" << gfileName << endl;
		throw exception();
	}
	const double PI = 4 * atan(1.0);
	const double min_angle = 0 * PI / 180;
	const double max_angle = 1 * PI / 180;

	FindNum h;

	string line;
	unsigned int lineNo = 0;
	unsigned int lineModulus = 1000;
	double gMin = numeric_limits<double>::max();
	double gMax = 0;
	double nMin = numeric_limits<double>::max();
	double nMax = 0;

	while (getline(iFile, line))
	{
		istringstream iss(line);
		lineNo++;
		iss >> h;
		if (!iss) {
			cerr << "Error in line " << lineNo << ": " << line << endl;
			nFile.close();
			gFile.close();
			throw exception();
		}
		if (min_angle<h.getAngle() && h.getAngle()<max_angle) {
			if (h.getType() == FindNum::Neutron){
				nFile << h.getEnergy() << endl;
				nMax = std::max(nMax, h.getEnergy());
				nMin = std::min(nMin, h.getEnergy());
			}
			else {
				gFile << h.getEnergy() << endl;
				gMax = std::max(gMax, h.getEnergy());
				gMin = std::min(gMin, h.getEnergy());
			}
		}
		if (lineNo%lineModulus == 0) {
			cout << "Line " << lineNo << endl;
		}
	}
	cout << "Processed " << lineNo << (lineNo == 1 ? " line" : " lines") << " from file " << ifileName << endl;

	cout << "Minimum neutron energy: " << nMin << " MeV\n";
	cout << "Maximum neutron energy: " << nMax << " MeV\n";
	cout << "Minimum gamma energy: " << gMin << " MeV\n";
	cout << "Maximum gamma energy: " << gMax << " MeV\n";

	scat::pause("\nPress <ENTER> to end the program.");

	return 0;
}

catch (std::exception& e)
{
	std::cerr << e.what();
	scat::pause("\nPress <ENTER> to end the program.");
	return 1;
}