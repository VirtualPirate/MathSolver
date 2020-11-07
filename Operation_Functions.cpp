#include <cmath>
#include <functional>

#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

// Constant to Constant arithmetic operators
Operand Constant::operator+(const Constant& other) const {
	Operand first = this->simplify();
	Operand second = other.simplify();
	double first_ = first.get<Constant>().value;
	double second_ = second.get<Constant>().value;
	if(first.getPower() == Constant::power_one && second.getPower() == Constant::power_one)
		return Constant{first_ + second_};
	return Operand{};
}
Operand Constant::operator-(const Constant& other) const {
	Operand second = other * (double)-1;
	return *this + second;
}
Operand Constant::operator*(const Constant& other) const {
	Operand first = this->simplify();
	Operand second = other.simplify();
	double first_ = first.get<Constant>().value;
	double second_ = second.get<Constant>().value;
	if(first_ == second_)
		return Constant{first_, first.getPower() + second.getPower()};
	else if(first.getPower() == second.getPower())
		return Constant{first_ * second_, first.getPower()};
	else
		return Term{{first, second}};
}
Operand Constant::operator/(const Constant& other) const {
	Operand second = other.raise_pow(-1);
	return *this * second;
}
Operand Constant::raise_pow(const Constant& other) const {
	Operand first = this->simplify();
	Operand second = other.simplify();
	if(second.getPower() == Constant::power_one){
		Operand final = (getPower() * second).simplify();
		if(final.getType() == DataType::Constant && final.getPower() == Constant::power_one)
			return Constant{pow(value, final.get<Constant>().value)};
	}
	first.setPower((getPower() * second).simplify());
	return first;
}


//Constant to Variable arithmetic operations

Operand Constant::operator+(const Variable& other) const {
	return Operand{};
}
Operand Constant::operator-(const Variable& other) const {
	return Operand{};
}
Operand Constant::operator*(const Variable& other) const {
	return Operand{};
}
Operand Constant::operator/(const Variable& other) const {
	return Operand{};
}
Operand Constant::raise_pow(const Variable& other) const {
	Operand first = this->simplify();
	Operand second = other.simplify();
	first.setPower((first.getPower() * second).simplify());
	return Operand{};
}


//Constant to Term arithmetic operations

Operand Constant::operator+(const Term& other) const {
	return Operand{};
}
Operand Constant::operator-(const Term& other) const {
	return Operand{};
}
Operand Constant::operator*(const Term& other) const {
	return Operand{};
}
Operand Constant::operator/(const Term& other) const {
	return Operand{};
}
Operand Constant::raise_pow(const Term& other) const {
	return Operand{};
}

//Constant to Expression arithmetic operations
Operand Constant::operator+(const Expression& other) const {
	return Operand{};
}
Operand Constant::operator-(const Expression& other) const {
	return Operand{};
}
Operand Constant::operator*(const Expression& other) const {
	return Operand{};
}
Operand Constant::operator/(const Expression& other) const {
	return Operand{};
}

//Variable to Constant artihmetic operations
Operand Variable::operator+(const Constant& other) const {
	return Operand{};
}
Operand Variable::operator-(const Constant& other) const {
	return Operand{};
}
Operand Variable::operator*(const Constant& other) const {
	return Operand{};
}
Operand Variable::operator/(const Constant& other) const {
	return Operand{};
}
Operand Variable::raise_pow(const Constant& other) const {
	return Operand{};
}

//Variable to Variable arithmetic operations
Operand Variable::operator+(const Variable& other) const {
	return Operand{};
}
Operand Variable::operator-(const Variable& other) const {
	return Operand{};
}
Operand Variable::operator*(const Variable& other) const {
	return Operand{};
}
Operand Variable::operator/(const Variable& other) const {
	return Operand{};
}
Operand Variable::raise_pow(const Variable& other) const {
	return Operand{};
}


//Variable to Term arithmetic operations
Operand Variable::operator+(const Term& other) const {
	return Operand{};
}
Operand Variable::operator-(const Term& other) const {
	return Operand{};
}
Operand Variable::operator*(const Term& other) const {
	return Operand{};
}
Operand Variable::operator/(const Term& other) const {
	return Operand{};
}
Operand Variable::raise_pow(const Term& other) const {
	return Operand{};
}

//Variable to Expression arithmetic operations
Operand Variable::operator+(const Expression& other) const {
	return Operand{};
}
Operand Variable::operator-(const Expression& other) const {
	return Operand{};
}
Operand Variable::operator*(const Expression& other) const {
	return Operand{};
}
Operand Variable::operator/(const Expression& other) const {
	return Operand{};
}
Operand Variable::raise_pow(const Expression& other) const {
	return Operand{};
}


//Term to Constant arithmetic operations
Operand Term::operator+(const Constant& other) const {
	return Operand{};
}
Operand Term::operator-(const Constant& other) const {
	return Operand{};
}
Operand Term::operator*(const Constant& other) const {
	return Operand{};
}
Operand Term::operator/(const Constant& other) const {
	return Operand{};
}
Operand Term::raise_pow(const Constant& other) const {
	return Operand{};
}

//Term to Variable arithmetic operations
Operand Term::operator+(const Variable& other) const {
	return Operand{};
}
Operand Term::operator-(const Variable& other) const {
	return Operand{};
}
Operand Term::operator*(const Variable& other) const {
	return Operand{};
}
Operand Term::operator/(const Variable& other) const {
	return Operand{};
}
Operand Term::raise_pow(const Variable& other) const {
	return Operand{};
}

//Term to Term arithmetic operations
Operand Term::operator+(const Term& other) const {
	return Operand{};
}
Operand Term::operator-(const Term& other) const {
	return Operand{};
}
Operand Term::operator*(const Term& other) const {
	return Operand{};
}
Operand Term::operator/(const Term& other) const {
	return Operand{};
}
Operand Term::raise_pow(const Term& other) const {
	return Operand{};
}

//Term to Expression arithmetic operations
Operand Term::operator+(const Expression& other) const {
	return Operand{};
}
Operand Term::operator-(const Expression& other) const {
	return Operand{};
}
Operand Term::operator*(const Expression& other) const {
	return Operand{};
}
Operand Term::operator/(const Expression& other) const {
	return Operand{};
}
Operand Term::raise_pow(const Expression& other) const {
	return Operand{};
}

//Expression to Constant arithmetic operations
Operand Expression::operator+(const Constant& other) const {
	return Operand{};
}
Operand Expression::operator-(const Constant& other) const {
	return Operand{};
}
Operand Expression::operator*(const Constant& other) const {
	return Operand{};
}
Operand Expression::operator/(const Constant& other) const {
	return Operand{};
}
Operand Expression::raise_pow(const Constant& other) const {
	return Operand{};
}

//Expression to Variable arithmetic operations
Operand Expression::operator+(const Variable& other) const {
	return Operand{};
}
Operand Expression::operator-(const Variable& other) const {
	return Operand{};
}
Operand Expression::operator*(const Variable& other) const {
	return Operand{};
}
Operand Expression::operator/(const Variable& other) const {
	return Operand{};
}
Operand Expression::raise_pow(const Variable& other) const {
	return Operand{};
}

//Expression to Term arithmetic operations
Operand Expression::operator+(const Term& other) const {
	return Operand{};
}
Operand Expression::operator-(const Term& other) const {
	return Operand{};
}
Operand Expression::operator*(const Term& other) const {
	return Operand{};
}
Operand Expression::operator/(const Term& other) const {
	return Operand{};
}
Operand Expression::raise_pow(const Term& other) const {
	return Operand{};
}

//Expression to Expression arithmetic operations
Operand Expression::operator+(const Expression& other) const {
	return Operand{};
}
Operand Expression::operator-(const Expression& other) const {
	return Operand{};
}
Operand Expression::operator*(const Expression& other) const {
	return Operand{};
}
Operand Expression::operator/(const Expression& other) const {
	return Operand{};
}
Operand Expression::raise_pow(const Expression& other) const {
	return Operand{};
}
