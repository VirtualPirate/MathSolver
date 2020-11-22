#include <cmath>
#include <functional>
#include <algorithm>

#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

Operand Operand_to_Expression_add(const Operand& first, const Expression& second){
	if(second.getPower() == Constant::power_one){
		Expression result = second;
		result.insert_front(first);
		return result;
	}
	return Expression{{first, second}};
}
inline Operand Operand_to_Expression_sub(const Operand& first, const Expression& second){
	return first + (second * (double)-1);
}
Operand Operand_to_Expression_mul(const Operand& first, const Expression& second){
	if(second.getPower() == Constant::power_one){
		Expression result = second;
		for(auto each=result.fields.begin(); each != result.fields.end(); each++)
			*each = first * *each;
		return result;
	}
	return Term{{first, second}};
}
inline Operand Operand_to_Expression_div(const Operand& first, const Expression& second){
	return first * second.raise_pow(-1);
}

Operand Expression_to_Operand_add(const Expression& first, const Operand& second){
	if(second.getPower() == Constant::power_one){
		Expression result = first;
		result.insert(first);
		return result;
	}
	return Expression{{first, second}};
}

inline Operand Expression_to_Operand_sub(const Expression& first, const Operand& second){
	return first + (second * (double)-1);
}

Operand Operand_to_Term_mul(const Operand& first, const Term& second){
	if(second.power == Constant::power_one){
		Term result = second;
		result.insert(first);
		return result;
	}else
		return Term{{first, second}};
}

inline Operand Operand_to_Term_div(const Operand& first, const Term& second){
	return first * second.raise_pow(-1);
}



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
	if(this->value == other.value)
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
	return Operand_to_Term_mul(*this, other);
}
Operand Constant::operator/(const Term& other) const {
	return Operand_to_Term_div(*this, other);
}
Operand Constant::raise_pow(const Term& other) const {
	return Constant{this->value, this->getPower() * other};
}

//Constant to Expression arithmetic operations
Operand Constant::operator+(const Expression& other) const {
	return Operand_to_Expression_add(*this, other);
}
Operand Constant::operator-(const Expression& other) const {
	return Operand_to_Expression_sub(*this, other);
}
Operand Constant::operator*(const Expression& other) const {
	return Operand_to_Expression_mul(*this, other);
}
Operand Constant::operator/(const Expression& other) const {
	return Operand_to_Expression_div(*this, other);
}
Operand Constant::raise_pow(const Expression& other) const {
	return Constant{this->value, this->getPower() * other};
}

//Variable to Constant artihmetic operations
Operand Variable::operator+(const Constant& other) const {
	return Expression{{*this, other}};
}
Operand Variable::operator-(const Constant& other) const {
	return Expression{{*this, other * -1}};
}
Operand Variable::operator*(const Constant& other) const {
	return other * *this;
}
Operand Variable::operator/(const Constant& other) const {
	return Term{{*this, other.raise_pow((double)-1)}};
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
	return Operand_to_Term_mul(*this, other);
}
Operand Variable::operator/(const Term& other) const {
	return Operand_to_Term_div(*this, other);
}
Operand Variable::raise_pow(const Term& other) const {
	return Variable{this->name, this->getPower() * other};;;
}

//Variable to Expression arithmetic operations
Operand Variable::operator+(const Expression& other) const {
	return Operand_to_Expression_add(*this, other);
}
Operand Variable::operator-(const Expression& other) const {
	return Operand_to_Expression_sub(*this, other);
	
}
Operand Variable::operator*(const Expression& other) const {
	return Operand_to_Expression_mul(*this, other);
	
}
Operand Variable::operator/(const Expression& other) const {
	return Operand_to_Expression_div(*this, other);
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
	if(is_addable(*this, other)){
		Term result{*this};
		*result.begin(DataType::Constant) += *other.cbegin(DataType::Constant);
		return result;
	}
	return Expression{{*this, other}};
}
Operand Term::operator-(const Term& other) const {
	if(is_addable(*this, other)){
		Term result{*this};
		*result.begin(DataType::Constant) -= *other.cbegin(DataType::Constant);
		return result;
	}
	return Expression{{*this, other * (double)-1}};
}
Operand Term::operator*(const Term& other) const {
	Term result{*this};
	if(same_operand_set(*this, other))
		result.setPower(this->power + other.power);
	else if(this->power == other.power)
		result.extend(other);
	else
		result.insert(other);
	return result;
}
Operand Term::operator/(const Term& other) const {
	return *this * other.raise_pow(-1);
}
Operand Term::raise_pow(const Term& other) const {
	Term result = *this;
	result.power = result.power * other;
	return result;
}

//Term to Expression arithmetic operations
Operand Term::operator+(const Expression& other) const {
	return Operand_to_Expression_add(*this, other);
}
Operand Term::operator-(const Expression& other) const {
	return Operand_to_Expression_sub(*this, other);
}
Operand Term::operator*(const Expression& other) const {
	return Operand_to_Expression_mul(*this, other);
}
Operand Term::operator/(const Expression& other) const {
	return Operand_to_Expression_div(*this, other);
}
Operand Term::raise_pow(const Expression& other) const {
	Term result = *this;
	result.power = result.power * other;
	return result;
}

//Expression to Constant arithmetic operations
Operand Expression::operator+(const Constant& other) const {
	return Expression_to_Operand_add(*this, other);
}
Operand Expression::operator-(const Constant& other) const {
	return Expression_to_Operand_sub(*this, other);
}
Operand Expression::operator*(const Constant& other) const {
	return Operand_to_Expression_mul(other, *this);
}
Operand Expression::operator/(const Constant& other) const {
	return Operand_to_Expression_div(other, *this);
}
Operand Expression::raise_pow(const Constant& other) const {
	return Operand{};
}

//Expression to Variable arithmetic operations
Operand Expression::operator+(const Variable& other) const {
	return Expression_to_Operand_add(*this, other);
}
Operand Expression::operator-(const Variable& other) const {
	return Expression_to_Operand_sub(*this, other);
}
Operand Expression::operator*(const Variable& other) const {
	return Operand_to_Expression_mul(other, *this);
}
Operand Expression::operator/(const Variable& other) const {
	return Operand_to_Expression_div(other, *this);
}
Operand Expression::raise_pow(const Variable& other) const {
	return Operand{};
}

//Expression to Term arithmetic operations
Operand Expression::operator+(const Term& other) const {
	return Expression_to_Operand_add(*this, other);
}
Operand Expression::operator-(const Term& other) const {
	return Expression_to_Operand_sub(*this, other);
}
Operand Expression::operator*(const Term& other) const {
	return Operand_to_Expression_mul(other, *this);
}
Operand Expression::operator/(const Term& other) const {
	return Operand_to_Expression_div(other, *this);
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

bool is_addable(const Term& first,  const Term& second) {
	bool criteria = first.cbegin(DataType::Term) == first.cend(DataType::Term)
	&& first.cbegin(DataType::Expression) == first.cend(DataType::Expression)
	&& first.count(DataType::Constant) == 1;

	std::vector<Variable> first_vec = first.getVars();
	std::vector<Variable> second_vec = second.getVars();
	if(first_vec.size() == second_vec.size() && criteria){
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

std::string return_type_string(DataType type){
	switch(type){
		case DataType::Constant:
			return "Constant";
		case DataType::Variable:
			return "Variable";
		case DataType::Term:
			return "Term";
		case DataType::Expression:
			return "Expression";
		default:
			return "None";
	}
}