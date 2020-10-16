#ifndef Constant_H
#define Constant_H

#include <iostream>

class Operand;
class Variable;
class Term;
class Expression;
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

	//Getter Methods
	const double& getValue() const;

	//Setter Methods
	void setValue(const double&);

	std::string power_print() const;
	bool is_negative() const;
	bool negative_power() const;
	Constant abs() const;

	//Constant to double arithmetic operations
	Constant operator+(const double&) const;
	Constant operator-(const double&) const;
	Constant operator*(const double&) const;
	Constant operator/(const double&) const;
	Constant raise_pow(const double&) const;

	//Constant to Constant operations
	Constant operator+(const Constant&) const;
	Constant operator-(const Constant&) const;
	Constant operator*(const Constant&) const;
	Constant operator/(const Constant&) const;
	Constant raise_pow(const Constant&) const;

	//Constant to Variable arithmetic operations
	Term operator+(const Variable&) const;
	Term operator-(const Variable&) const;
	Term operator*(const Variable&) const;
	Term operator/(const Variable&) const;
	Term raise_pow(const Variable&) const;

	//Constant to Term arithmetic operations
	Term operator+(const Term&) const;
	Term operator-(const Term&) const;
	Term operator*(const Term&) const;
	Term operator/(const Term&) const;
	Term raise_pow(const Term&) const;

	//Constant to Expression arithmetic operations
	Expression operator+(const Expression&) const;
	Expression operator-(const Expression&) const;
	Expression operator*(const Expression&) const;
	Expression operator/(const Expression&) const;
	Term raise_pow(const Expression&) const;


	bool operator==(const double&) const;
	bool operator!=(const double&) const;

	bool operator==(const Constant&)const;
	bool operator!=(const Constant&)const;

	bool operator==(const Variable&) const;
	bool operator!=(const Variable&) const;

	bool operator==(const Term&) const;
	bool operator!=(const Term&) const;

	bool operator==(const Expression&) const;
	bool operator!=(const Expression&) const;

	bool operator==(const Operand&) const;
	bool operator!=(const Operand&) const;


	//Unary operators 
	Constant operator+() const;
	Constant operator-() const;

	friend std::ostream& operator<<(std::ostream&, const Constant&);

};

#endif