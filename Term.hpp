#ifndef Term_H
#define Term_H

#include <vector>
#include "OperandList.hpp"

class Constant;
class Variable;
class Expression;
class Operand;
class OperandList;

class Term: public OperandList{
	friend class Constant;
	friend class Variable;
	friend class Operand;
	friend class Expression;
	friend std::ostream& operator<<(std::ostream&, const Term&);

	void extend(const Term&);
public:
	bool is_negative() const;
	bool negative_power() const;
	std::string power_print() const;
	void simplify_();
	Operand simplify() const;

	bool is_Constant() const;
	bool is_Variable() const;

	std::vector<Variable> getVars() const;

	Operand operator+(const double&) const;
	Operand operator-(const double&) const;
	Operand operator*(const double&) const;
	Operand operator/(const double&) const;
	Operand raise_pow(const double&) const;

	Operand operator+(const Constant&) const;
	Operand operator-(const Constant&) const;
	Operand operator*(const Constant&) const;
	Operand operator/(const Constant&) const;
	Operand raise_pow(const Constant&) const;

	//Term to Variable arithmetic operators
	Operand operator+(const Variable&) const;
	Operand operator-(const Variable&) const;
	Operand operator*(const Variable&) const;
	Operand operator/(const Variable&) const;
	Operand raise_pow(const Variable&) const;

	//Variable to Term operations
	Operand operator+(const Term&) const;
	Operand operator-(const Term&) const;
	Operand operator*(const Term&) const;
	Operand operator/(const Term&) const;
	Operand raise_pow(const Term&) const;

	Operand operator+(const Expression&) const;
	Operand operator-(const Expression&) const;
	Operand operator*(const Expression&) const;
	Operand operator/(const Expression&) const;
	Operand raise_pow(const Expression&) const;

	Operand operator+(const Operand&) const;
	Operand operator-(const Operand&) const;
	Operand operator*(const Operand&) const;
	Operand operator/(const Operand&) const;
	Operand raise_pow(const Operand&) const;

	bool operator==(const Term&) const;
	bool operator!=(const Term&) const;
};

#endif