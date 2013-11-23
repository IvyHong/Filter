#include "Find.h"

#include <limits>

using namespace std;


double FindNum::getEnergy()const {
	double energy;
	if (t == Gamma){
		energy = sqrt(u*u + v*v + w*w);
	}
	else if (t == Neutron){
		double momentum = sqrt(u*u + v*v + w*w);
		static const double restmass = 939.565330; //MeV
		double Lorenz = sqrt(1 + momentum / restmass*momentum / restmass);
		energy = restmass*(Lorenz - 1);
	}
	return energy;
}

bool getFromCsv(istream& is, double& a, double& b, double& c, double& d, double& e, double& f, int attempt = 1)
{
	if (attempt>1) {
		is.ignore(numeric_limits<streamsize>::max(), ',');
	}
	is >> a;
	is.ignore(numeric_limits<streamsize>::max(), ',');
	is >> b;
	is.ignore(numeric_limits<streamsize>::max(), ',');
	is >> c;
	is.ignore(numeric_limits<streamsize>::max(), ',');
	is >> d;
	is.ignore(numeric_limits<streamsize>::max(), ',');
	is >> e;
	is.ignore(numeric_limits<streamsize>::max(), ',');
	is >> f;
	return is.good() || (attempt>1 && is.eof());
}

istream& operator>>(istream& is, FindNum& item)
{
	double x, y, z, u, v, w;

	is >> x;
	is.ignore(numeric_limits<streamsize>::max(), ',');
	is >> y;
	is.ignore(numeric_limits<streamsize>::max(), ',');
	is >> z;
	is.ignore(numeric_limits<streamsize>::max(), ',');
	is >> u;
	is.ignore(numeric_limits<streamsize>::max(), ',');
	is >> v;
	is.ignore(numeric_limits<streamsize>::max(), ',');
	is >> w;

	if (is.good() && (x != 0. || y != 0. || z != 0. || u != 0. || v != 0. || w != 0.)) {
		item = FindNum(FindNum::Gamma, x, y, z, u, v, w);
	}
	else {
		is.ignore(numeric_limits<streamsize>::max(), ',');
		is >> x;
		is.ignore(numeric_limits<streamsize>::max(), ',');
		is >> y;
		is.ignore(numeric_limits<streamsize>::max(), ',');
		is >> z;
		is.ignore(numeric_limits<streamsize>::max(), ',');
		is >> u;
		is.ignore(numeric_limits<streamsize>::max(), ',');
		is >> v;
		is.ignore(numeric_limits<streamsize>::max(), ',');
		is >> w;
		if (is.eof()) {
			item = FindNum(FindNum::Neutron, x, y, z, u, v, w);
		}
	}
	return is;
}