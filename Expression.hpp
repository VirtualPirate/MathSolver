#ifndef Expression_H
#define Expression_H

#include "OperandList.hpp"

class Constant;
class Operand;
class Variable;
class Term;
class OperandList;
class Expression: public OperandList{
	friend class Constant;
	friend class Operand;
	friend class Variable;
	friend class Term;
	friend std::ostream& operator<<(std::ostream&, const Expression&);
public:
	std::string power_print() const;
	bool is_negative() const;
	bool negative_power() const;

	void simplify_();
	Operand simplify() const;

	Operand operator+(const Constant&) const;
	Operand operator-(const Constant&) const;
	Operand operator*(const Constant&) const;
	Operand operator/(const Constant&) const;
	Operand raise_pow(const Constant&) const;

	Operand operator+(const Variable&) const;
	Operand operator-(const Variable&) const;
	Operand operator*(const Variable&) const;
	Operand operator/(const Variable&) const;
	Operand raise_pow(const Variable&) const;

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

};

#endif