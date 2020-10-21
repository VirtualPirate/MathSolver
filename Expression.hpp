#ifndef Expression_H
#define Expression_H

#include "OperandList.hpp"

class Constant;
class Operand;
class Variable;
class OperandList;
class Expression: public OperandList{
	friend std::ostream& operator<<(std::ostream&, const Expression&);
public:
	std::string power_print() const;
	bool is_negative() const;
	bool negative_power() const;

	void simplify_();
	Operand simplify() const;

	Operand operator+(const Operand&) const;
	Operand operator-(const Operand&) const;
	Operand operator*(const Operand&) const;
	Operand operator/(const Operand&) const;
	Operand raise_pow(const Operand&) const;

};

#endif