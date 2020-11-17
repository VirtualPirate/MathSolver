#include <cmath>
#include <functional>
#include <algorithm>

#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

// Constant to Constant arithmetic operators
Operand Constant::operator+(const Constant& other) const {
	if(this->getPower() == Constant::power_one && other.getPower() == Constant::power_one)
		return Constant{value + other.value};
	else
		return Expression{{*this, other}};
}
Operand Constant::operator-(const Constant& other) const {
	if(this->getPower() == Constant::power_one && other.getPower() == Constant::power_one)
		return Constant{value - other.value};
	else
		return Expression{{*this, other}};
}
Operand Constant::operator*(const Constant& other) const {
	if(*this == other)
		return Constant{this->value, this->getPower() + other.getPower()};
	else if(this->getPower() == other.getPower())
		return Constant{this->value * other.value, this->getPower()};
	else
		return Term{{*this, other}};
}
Operand Constant::operator/(const Constant& other) const {
	Operand second = other.raise_pow(-1);
	return *this * second;
}
Operand Constant::raise_pow(const Constant& other) const {
	Operand final = getPower() * other;
	if(final.getType() == DataType::Constant && final.getPower() == Constant::power_one)
		return Constant{pow(this->value, final.get<Constant>().value)};
	else
		return Constant{value, final};
}


//Constant to Variable arithmetic operations

Operand Constant::operator+(const Variable& other) const {
	return Expression{{*this, other}};
}
Operand Constant::operator-(const Variable& other) const {
	return Expression{{*this, other * (double)-1}};
}
Operand Constant::operator*(const Variable& other) const {
	return Term{{*this, other}};
}
Operand Constant::operator/(const Variable& other) const {
	return Term{{*this, other.raise_pow((double)-1)}};
}
Operand Constant::raise_pow(const Variable& other) const {
	return Constant{this->value, this->getPower() * other};
}


//Constant to Term arithmetic operations

Operand Constant::operator+(const Term& other) const {
	return Expression{{*this, other}};
}
Operand Constant::operator-(const Term& other) const {
	return Expression{{*this, other * (double)-1}};
}
Operand Constant::operator*(const Term& other) const {
	if(other.power == Constant::power_one){
		Term result = other;
		result.insert(*this);
		return result;
	}else
		return Term{{*this, other}};
}
Operand Constant::operator/(const Term& other) const {
	return *this * other.raise_pow(-1);
}
Operand Constant::raise_pow(const Term& other) const {
	return Constant{this->value, this->getPower() * other};
}

//Constant to Expression arithmetic operations
Operand Constant::operator+(const Expression& other) const {
	Expression result = other;
	result.insert_front(*this);
	return result;
	// return Operand{};
}
Operand Constant::operator-(const Expression& other) const {
	Operand result = other * (double)-1;
	result.get_nonconst<Expression>().insert_front(*this);
	return result;
	// return Operand{};
}
Operand Constant::operator*(const Expression& other) const {
	Expression result = other;
	for(auto each=result.fields.begin(); each != result.fields.end(); each++)
		*each = *this * *each;
	return result;
}
Operand Constant::operator/(const Expression& other) const {
	Operand result = other.raise_pow(-1);
	return *this * result;
	// return Operand{};
}
Operand Constant::raise_pow(const Expression& other) const {
	return Constant{this->value, this->getPower() * other};
}

//Variable to Constant artihmetic operations
Operand Variable::operator+(const Constant& other) const {
	return Expression{{*this, other}};;
}
Operand Variable::operator-(const Constant& other) const {
	return Expression{{*this, other * -1}};;
}
Operand Variable::operator*(const Constant& other) const {
	return other * *this;
}
Operand Variable::operator/(const Constant& other) const {
	return Term{{*this, other.raise_pow((double)-1)}};;
}
Operand Variable::raise_pow(const Constant& other) const {
	return Variable{this->name, this->getPower() * other};
}

//Variable to Variable arithmetic operations
Operand Variable::operator+(const Variable& other) const {
	if(*this == other)
		return Term{{(double)2, *this}};
	return Expression{{*this, other}};
}
Operand Variable::operator-(const Variable& other) const {
	if(*this == other)
		return Constant{(double)0};
	return Expression{{*this, other * (double)-1}};
}
Operand Variable::operator*(const Variable& other) const {
	if(this->name == other.name)
		return Variable{this->name, this->power + other.power};
	return Term{{*this, other}};
}
Operand Variable::operator/(const Variable& other) const {
	return *this * other.raise_pow((double)-1);
}
Operand Variable::raise_pow(const Variable& other) const {
	return Variable{this->name, this->getPower() * other};;
}


//Variable to Term arithmetic operations
Operand Variable::operator+(const Term& other) const {
	return Expression{{*this, other}};
}
Operand Variable::operator-(const Term& other) const {
	return Expression{{*this, other * (double)-1}};
}
Operand Variable::operator*(const Term& other) const {
	if(other.power == Constant::power_one){
		Term result = other;
		result.insert(*this);
		return result;
	}else
		return Term{{*this, other}};
}
Operand Variable::operator/(const Term& other) const {
	return *this * other.raise_pow(-1);
}
Operand Variable::raise_pow(const Term& other) const {
	return Variable{this->name, this->getPower() * other};;;
}

//Variable to Expression arithmetic operations
Operand Variable::operator+(const Expression& other) const {
	Expression result = other;
	result.insert_front(*this);
	return result;
}
Operand Variable::operator-(const Expression& other) const {
	Operand result = other * (double)-1;
	result.get_nonconst<Expression>().insert_front(*this);
	return result;
}
Operand Variable::operator*(const Expression& other) const {
	Expression result = other;
	for(auto each=result.fields.begin(); each != result.fields.end(); each++)
		*each = *this * *each;
	return result;
}
Operand Variable::operator/(const Expression& other) const {
	Operand result = other.raise_pow(-1);
	return *this * result;
}
Operand Variable::raise_pow(const Expression& other) const {
	return Variable{this->name, this->getPower() * other};
}


//Term to Constant arithmetic operations
Operand Term::operator+(const Constant& other) const {
	return Expression{{*this, other}};
}
Operand Term::operator-(const Constant& other) const {
	return Expression{{*this, other * (double)-1}};
}
Operand Term::operator*(const Constant& other) const {
	Term result = *this;
	result.insert(other);
	return result;
}
Operand Term::operator/(const Constant& other) const {
	Term result = *this;
	result.insert(other.raise_pow(-1));
	return result;
}
Operand Term::raise_pow(const Constant& other) const {
	Term result = *this;
	result.power = result.power * other;
	return result;
}

//Term to Variable arithmetic operations
Operand Term::operator+(const Variable& other) const {
	return Expression{{*this, other}};
}
Operand Term::operator-(const Variable& other) const {
	return Expression{{*this, other * (double)-1}};
}
Operand Term::operator*(const Variable& other) const {
	Term result = *this;
	result.insert(other);
	return result;
}
Operand Term::operator/(const Variable& other) const {
	Term result = *this;
	result.insert(other.raise_pow(-1));
	return result;
}
Operand Term::raise_pow(const Variable& other) const {
	Term result = *this;
	result.power = result.power * other;
	return result;
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

bool same_varset(Term& first, Term& second) {
	std::vector<Variable> first_vec = first.getVars();
	std::vector<Variable> second_vec = second.getVars();
	if(first_vec.size() == second_vec.size()){
		auto iter = first_vec.begin();
		std::vector<Variable>::iterator element;
		while(iter != first_vec.end()){
			element = std::find(second_vec.begin(), second_vec.end(), *iter);
			if(element != second_vec.end())
				second_vec.erase(element);
			else
				return false;
			iter++;
		}
		return true;
	}
	return false;
}