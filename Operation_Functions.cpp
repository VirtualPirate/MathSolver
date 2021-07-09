#include <cmath>
#include <functional>
#include <algorithm>

#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Substitutor.hpp"
#include "Operation_Functions.hpp"

#include "Tests.hpp"

const Substitutor CONSTANTS::null_substitutor = Substitutor{};
const Operand CONSTANTS::ONE = Operand{(double)1};
const Operand CONSTANTS::ZERO = Operand{(double)0};
const Operand CONSTANTS::MINUS_ONE = Operand{ (double)-1 };
const Operand CONSTANTS::NULL_OPERAND = Operand{};


// Constant to Constant arithmetic operators
Operand Constant::operator+(const Constant& other) const{
	if (!power && !other.power) // power == other.power == 1
		return Constant{ value + other.value };
	return CONSTANTS::NULL_OPERAND;
}
Operand Constant::operator-(const Constant& other) const{
	if (!power&& !other.power) // power == other.power == 1
		return Constant{ value - other.value };
	return CONSTANTS::NULL_OPERAND;
}
Operand Constant::operator*(const Constant& other) const{
	if (!power && !other.power) // power == other.power == 1
		return Constant{ value * other.value };
	Operand power_add{ getPower() +other.getPower() };
	if (value == other.value && power_add)
		return Constant{ value, power_add };

	return Term{ {*this, other} };
}
Operand Constant::operator/(const Constant& other) const{
	return this->operator*(other.raise_pow((double)-1));
}
Operand Constant::raise_pow(const Constant& other) const{
	return Constant{ value, getPower() * other };
}


//Constant to Variable arithmetic operations

Operand Constant::operator+(const Variable& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Constant::operator-(const Variable& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Constant::operator*(const Variable& other) const{
	return Term{ {*this, other} };
}
Operand Constant::operator/(const Variable& other) const{
	return this->operator*(other.raise_pow((double)-1));
}
Operand Constant::raise_pow(const Variable& other) const{
	return Constant{ value, getPower() * other };
}


//Constant to Term arithmetic operations

Operand Constant::operator+(const Term& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Constant::operator-(const Term& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Constant::operator*(const Term& other) const{
	if (other.power == CONSTANTS::ONE) {
		Term result{ other };
		result.insert_front(*this);
		return result;
	}
	else
		return Term{ {*this, other} };
}
Operand Constant::operator/(const Term& other) const{
	return *this * other.raise_pow((double)-1);
}
Operand Constant::raise_pow(const Term& other) const{
	return Constant{ value, getPower() * other };
}

//Constant to Expression arithmetic operations
Operand Constant::operator+(const Expression& other) const{return Operand{};}
Operand Constant::operator-(const Expression& other) const{return Operand{};}
Operand Constant::operator*(const Expression& other) const{return Operand{};}
Operand Constant::operator/(const Expression& other) const{return Operand{};}
Operand Constant::raise_pow(const Expression& other) const{return Operand{};}

//Variable to Constant artihmetic operations
Operand Variable::operator+(const Constant& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Variable::operator-(const Constant& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Variable::operator*(const Constant& other) const{
	return other.operator*(*this);
}
Operand Variable::operator/(const Constant& other) const{
	return this->operator*(other.raise_pow((double)-1));
}
Operand Variable::raise_pow(const Constant& other) const{
	return Variable{ name, power * other };
}

//Variable to Variable arithmetic operations
Operand Variable::operator+(const Variable& other) const{
	if (*this == other)
		return Term{ {(double)2, *this} };
	return CONSTANTS::NULL_OPERAND;
}
Operand Variable::operator-(const Variable& other) const{
	if (*this == other)
		return CONSTANTS::ZERO;
	return CONSTANTS::NULL_OPERAND;
}
Operand Variable::operator*(const Variable& other) const{
	if (name == other.name) {
		Operand power_sum{ power + other.power };
		if (power_sum)
			return Variable{ name, power_sum };
	}
	return Term{ {*this, other} };
}
Operand Variable::operator/(const Variable& other) const{
	return this->operator*(other.raise_pow((double)-1));
}
Operand Variable::raise_pow(const Variable& other) const{
	return Variable{ name, power * other };
}


//Variable to Term arithmetic operations
Operand Variable::operator+(const Term& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Variable::operator-(const Term& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Variable::operator*(const Term& other) const{
	if (other.power == CONSTANTS::ONE) {
		Term result{ other };
		result.insert_front(*this);
		return result;
	}
	else
		return Term{ {*this, other} };
}
Operand Variable::operator/(const Term& other) const{
	return *this * other.raise_pow((double)-1);
}
Operand Variable::raise_pow(const Term& other) const{
	return Variable{ name, power * other };
}

//Variable to Expression arithmetic operations
Operand Variable::operator+(const Expression& other) const{return Operand{};}
Operand Variable::operator-(const Expression& other) const{return Operand{};}
Operand Variable::operator*(const Expression& other) const{return Operand{};}
Operand Variable::operator/(const Expression& other) const{return Operand{};}
Operand Variable::raise_pow(const Expression& other) const{return Operand{};}


//Term to Constant arithmetic operations
Operand Term::operator+(const Constant& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Term::operator-(const Constant& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Term::operator*(const Constant& other) const{
	return other.operator*(*this);
}
Operand Term::operator/(const Constant& other) const{
	return *this * other.raise_pow((double)-1);
}
Operand Term::raise_pow(const Constant& other) const {
	return Term{ fields, power * other };
}

//Term to Variable arithmetic operations
Operand Term::operator+(const Variable& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Term::operator-(const Variable& other) const{
	return CONSTANTS::NULL_OPERAND;
}
Operand Term::operator*(const Variable& other) const{
	return other.operator*(*this);
}
Operand Term::operator/(const Variable& other) const{
	return other.operator*((double)-1).operator*(*this);
}
Operand Term::raise_pow(const Variable& other) const {
	return Term{ fields, power.operator*(other) };
}

//Term to Term arithmetic operations
Operand Term::operator+(const Term& other) const{
	if (is_addable(*this, other)) { // if the terms *this and other contain same variable sets
		Term result{ *this };
		if (this->count(DataType::Constant) == 0) // if the terms does not contain any constants
			result.insert_front((double)2);
		else
			*(result.begin(DataType::Constant)) = *(this->cbegin(DataType::Constant)) + *(other.cbegin(DataType::Constant));
		return result;
	}
	return CONSTANTS::NULL_OPERAND;
}
Operand Term::operator-(const Term& other) const{
	if (is_addable(*this, other)) { // if the terms *this and other contain same variable sets
		Term result{ *this };
		if (this->count(DataType::Constant) == 0) // if the terms does not contain any constants
			return CONSTANTS::ZERO;
		else
			*(result.begin(DataType::Constant)) = *(this->cbegin(DataType::Constant)) - *(other.cbegin(DataType::Constant));
		return result;
	}
	return CONSTANTS::NULL_OPERAND;
}
Operand Term::operator*(const Term& other) const{
	if (this->power == CONSTANTS::ONE && other.power == CONSTANTS::ONE) {
		std::vector<Operand> result;
		result.reserve(this->fields.size() + other.fields.size());

		for (const auto& each : this->fields)
			result.push_back(each);
		for (const auto& each : other.fields)
			result.push_back(each);

		return Term{ result };
	}
	else
	{
		return Term{ *this, other };
	}
}
Operand Term::operator/(const Term& other) const{return Operand{};}
Operand Term::raise_pow(const Term& other) const{
	return Term{ fields, power.operator*(other) };
}

//Term to Expression arithmetic operations
Operand Term::operator+(const Expression& other) const{return Operand{};}
Operand Term::operator-(const Expression& other) const{return Operand{};}
Operand Term::operator*(const Expression& other) const{return Operand{};}
Operand Term::operator/(const Expression& other) const{return Operand{};}
Operand Term::raise_pow(const Expression& other) const{return Operand{};}

//Expression to Constant arithmetic operations
Operand Expression::operator+(const Constant& other) const{return Operand{};}
Operand Expression::operator-(const Constant& other) const{return Operand{};}
Operand Expression::operator*(const Constant& other) const{return Operand{};}
Operand Expression::operator/(const Constant& other) const{return Operand{};}
Operand Expression::raise_pow(const Constant& other) const{return Operand{};}

//Expression to Variable arithmetic operations
Operand Expression::operator+(const Variable& other) const{return Operand{};}
Operand Expression::operator-(const Variable& other) const{return Operand{};}
Operand Expression::operator*(const Variable& other) const{return Operand{};}
Operand Expression::operator/(const Variable& other) const{return Operand{};}
Operand Expression::raise_pow(const Variable& other) const{return Operand{};}

//Expression to Term arithmetic operations
Operand Expression::operator+(const Term& other) const{return Operand{};}
Operand Expression::operator-(const Term& other) const{return Operand{};}
Operand Expression::operator*(const Term& other) const{return Operand{};}
Operand Expression::operator/(const Term& other) const{return Operand{};}
Operand Expression::raise_pow(const Term& other) const{return Operand{};}

//Expression to Expression arithmetic operations
Operand Expression::operator+(const Expression& other) const {return Operand{};}
Operand Expression::operator-(const Expression& other) const {return Operand{};}
Operand Expression::operator*(const Expression& other) const {return Operand{};}
Operand Expression::operator/(const Expression& other) const {return Operand{};}
Operand Expression::raise_pow(const Expression& other) const {return Operand{};}

bool is_addable(const Term& first,  const Term& second) {
	bool criteria = first.cbegin(DataType::Term) == first.cend(DataType::Term)
	&& first.cbegin(DataType::Expression) == first.cend(DataType::Expression)
	&& (first.count(DataType::Constant) == 1 || first.count(DataType::Constant) == 0) && first.getPower() == CONSTANTS::ONE
	&& second.getPower() == CONSTANTS::ONE;

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

std::string match_number(std::string query){
	std::string result;
	bool period = false;
	bool has_digit = false;
	if(!query.empty() && query.at(0) == '-'){
		result.push_back('-');
		query.erase(query.begin());
	}
	for(auto each_char: query){
		if(isdigit(each_char)){
			result.push_back(each_char);
			has_digit = true;
		}
		else if(each_char == '.' && !period){
			period = true;
			result.push_back(each_char);
			has_digit = false;
		}else break;
	}
	if(has_digit)
	return result;
	return "";
}