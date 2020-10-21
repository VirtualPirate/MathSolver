#ifndef Term_H
#define Term_H

#include <vector>
#include "OperandList.hpp"

class Constant;
class Variable;
class Operand;
class OperandList;

class Term: public OperandList{
	friend std::ostream& operator<<(std::ostream&, const Term&);
public:
	bool is_negative() const;
	bool negative_power() const;
	std::string power_print() const;
	void simplify_();
	Operand simplify() const;

	bool is_Constant() const;
	bool is_Variable() const;

	Operand operator+(const Operand&) const;
	Operand operator-(const Operand&) const;
	Operand operator*(const Operand&) const;
	Operand operator/(const Operand&) const;
	Operand raise_pow(const Operand&) const;
};

#endif