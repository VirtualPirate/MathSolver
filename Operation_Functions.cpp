#include <cmath>
#include <functional>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

// Constant to Constant arithmetic operators
Operand Constant::operator+(const Constant& other) const {
	return Constant{value + other.value};
}
Operand Constant::operator-(const Constant& other) const {
	return Constant{value - other.value};
}
Operand Constant::operator*(const Constant& other) const {
	return Constant{value * other.value};
}
Operand Constant::operator/(const Constant& other) const {
	return Constant{value / other.value};
}
Operand Constant::raise_pow(const Constant& other) const {
	return Constant{pow(value, other.value)};
}


//Constant to Variable arithmetic operations

Operand Constant::operator+(const Variable& other) const {
	return Term{};
}
Operand Constant::operator-(const Variable& other) const {
	return Term{};
}
Operand Constant::operator*(const Variable& other) const {
	return Term{{*this, other.simplify()}};
}
Operand Constant::operator/(const Variable& other) const {
	return Term{{*this, Variable{other.getName(), -1}.simplify()}};
}
Operand Constant::raise_pow(const Variable& other) const {
	Term term{*this};
	term.setPower(other.simplify());
	return term;
}


//Constant to Term arithmetic operations

Operand Constant::operator+(const Term& other) const {
	Term second{other.simplify()};
	if(second.is_Constant() || second.is_Variable())
		return *this + second;
	return Term{};
}

Operand Constant::operator-(const Term& other) const {
	Term second{other.simplify()};
	if(second.is_Constant() || second.is_Variable())
		return *this - second;
	return Term{};
}

Operand Constant::operator*(const Term& other) const {
	Term second{other};
	second.insert(*this);
	second.simplify_();
	return second;
}