#include <cmath>
#include <functional>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

// Constant to Constant arithmetic operators
Constant Constant::operator+(const Constant& other) const {
	return Constant{value + other.value};
}
Constant Constant::operator-(const Constant& other) const {
	return Constant{value - other.value};
}
Constant Constant::operator*(const Constant& other) const {
	return Constant{value * other.value};
}
Constant Constant::operator/(const Constant& other) const {
	return Constant{value / other.value};
}
Constant Constant::raise_pow(const Constant& other) const {
	return Constant{pow(value, other.value)};
}


//Constant to Variable arithmetic operations

Term Constant::operator+(const Variable& other) const {
	return Term{};
}
Term Constant::operator-(const Variable& other) const {
	return Term{};
}
Term Constant::operator*(const Variable& other) const {
	return Term{{*this, other}};
}
Term Constant::operator/(const Variable& other) const {
	return Term{{*this, Variable{other.getName(), -1}}};
}
Term Constant::raise_pow(const Variable& other) const {
	Term term{*this};
	term.setPower(other);
	return term;
}
