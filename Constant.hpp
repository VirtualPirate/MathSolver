#ifndef Constant_H
#define Constant_H

#include <iostream>

struct Constant{
	double value;

	//Constructors
	Constant(void);
	Constant(double);
	Constant(const Constant&);
	Constant(const Constant&&);
	Constant(const Constant*);

	// Assignment operators
	Constant& operator=(double);
	Constant& operator=(const Constant&);
	Constant& operator=(const Constant&&);

	//Constant to Constant comparison operator
	bool operator==(const Constant&)const;
	bool operator!=(const Constant&)const;

	std::string power_print() const;
	Constant abs() const;

	//Constant to Constant operations
	Constant operator+(const Constant&) const;
	Constant operator-(const Constant&) const;
	Constant operator*(const Constant&) const;
	Constant operator/(const Constant&) const;
	Constant raise_pow(const Constant&) const;

	//Unary operators 
	Number operator+() const;
	Number operator-() const;
	friend ostream& operator<<(ostream&, const Number&);

}

#endif