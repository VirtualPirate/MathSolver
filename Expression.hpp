#ifndef Expression_H
#define Expression_H

#include "OperandList.hpp"

class Substitutor;
class Substitutor_List;
class Constant;
class Operand;
class Variable;
class Term;
class OperandList;
class Expression: public OperandList{

	bool is_subexpression = false;

	using OperandList::OperandList;

	friend class Constant;
	friend class Operand;
	friend class Variable;
	friend class Term;
	friend std::ostream& operator<<(std::ostream&, const Expression&);

	friend Operand Operand_to_Expression_add(const Operand&, const Expression&);
	friend inline Operand Operand_to_Expression_sub(const Operand&, const Expression&);
	friend Operand Operand_to_Expression_mul(const Operand&, const Expression&);
	friend inline Operand Operand_to_Expression_div(const Operand&, const Expression&);

	friend Operand Expression_to_Operand_add(const Operand&, const Expression&);
	friend inline Operand Expression_to_Operand_sub(const Operand&, const Expression&);
public:
	std::string power_print() const;
	bool is_negative() const;
	bool negative_power() const;

	Expression getBase() const;

	void setSubexpression(bool);
	bool isSubexpression() const;

	void simplify_();
	Operand simplify() const;
	Operand substitute(const Substitutor_List& list) const;

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