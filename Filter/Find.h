#ifndef FindNum_H_
#define FindNum_H_

#include <iostream>

class FindNum{

public:

	// Create an enum type object which is inside a class
	enum Type{ Neutron, Gamma, Unknown };

	FindNum() :t(Unknown){}
	FindNum(Type tt, double xx, double yy, double zz,
		double uu, double vv, double ww)
		:t(tt), x(xx), y(yy), z(zz), u(uu), v(vv), w(ww){}

	double getAngle()  const { return std::acos(z / std::sqrt(x*x + y*y + z*z)); }
	//    double getEnergy() const {return std::sqrt(u*u+v*v+w*w);}
	double getEnergy() const;
	double getType()   const { return t; }

private:
	Type t;
	double x, y, z;
	double u, v, w;
};

std::istream& operator>>(std::istream& is, FindNum& item);

#endif