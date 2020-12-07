#ifndef Term_H
#define Term_H

#include <vector>
#include "OperandList.hpp"

class Substitutor;
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
	friend bool same_operand_set(const Term&, const Term&);

	friend Operand Operand_to_Term_add(const Operand&, const Term&);
	friend inline Operand Operand_to_Term_sub(const Operand&, const Term&);
	friend Operand Operand_to_Term_mul(const Operand&, const Term&);
	friend inline Operand Operand_to_Term_div(const Operand&, const Term&);

	friend Operand Term_to_Operand_add(const Term&, const Operand&);
	friend inline Operand Term_to_Operand_sub(const Term&, const Operand&);
	friend Operand Term_to_Operand_mul(const Term&, const Operand&);
	friend inline Operand Term_to_Operand_div(const Term&, const Operand&);

	void extend(const Term&);
	std::vector<Operand> internal_simplify() const; 
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

bool same_operand_set(const Term&, const Term&);

#endif