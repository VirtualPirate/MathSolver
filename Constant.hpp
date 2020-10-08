#ifndef Constant_H
#define Constant_H

#include <iostream>

class Constant{
	double value;

public:
	//Constructors
	Constant(void);
	Constant(double);
	Constant(const Constant&);
	Constant(const Constant*);

	// Assignment operators
	Constant& operator=(double);
	Constant& operator=(const Constant&);

	//Constant to Constant comparison operator
	bool operator==(const Constant&)const;
	bool operator!=(const Constant&)const;

	//Getter Methods
	const double& getValue() const;

	//Setter Methods
	void setValue(const double&);

	std::string power_print() const;
	Constant abs() const;

	//Constant to Constant operations
	Constant operator+(const Constant&) const;
	Constant operator-(const Constant&) const;
	Constant operator*(const Constant&) const;
	Constant operator/(const Constant&) const;
	Constant raise_pow(const Constant&) const;

	//Unary operators 
	Constant operator+() const;
	Constant operator-() const;

	friend std::ostream& operator<<(std::ostream&, const Constant&);

};

#endif