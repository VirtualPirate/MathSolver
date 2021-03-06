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
const Operand CONSTANTS::NULL_OPERAND = Operand{};


// Constant to Constant arithmetic operators
Operand Constant::operator+(const Constant& other) const{return Operand{};}
Operand Constant::operator-(const Constant& other) const{return Operand{};}
Operand Constant::operator*(const Constant& other) const{return Operand{};}
Operand Constant::operator/(const Constant& other) const{return Operand{};}
Operand Constant::raise_pow(const Constant& other) const{return Operand{};}


//Constant to Variable arithmetic operations

Operand Constant::operator+(const Variable& other) const{return Operand{};}
Operand Constant::operator-(const Variable& other) const{return Operand{};}
Operand Constant::operator*(const Variable& other) const{return Operand{};}
Operand Constant::operator/(const Variable& other) const{return Operand{};}
Operand Constant::raise_pow(const Variable& other) const{return Operand{};}


//Constant to Term arithmetic operations

Operand Constant::operator+(const Term& other) const{return Operand{};}
Operand Constant::operator-(const Term& other) const{return Operand{};}
Operand Constant::operator*(const Term& other) const{return Operand{};}
Operand Constant::operator/(const Term& other) const{return Operand{};}
Operand Constant::raise_pow(const Term& other) const{return Operand{};}

//Constant to Expression arithmetic operations
Operand Constant::operator+(const Expression& other) const{return Operand{};}
Operand Constant::operator-(const Expression& other) const{return Operand{};}
Operand Constant::operator*(const Expression& other) const{return Operand{};}
Operand Constant::operator/(const Expression& other) const{return Operand{};}
Operand Constant::raise_pow(const Expression& other) const{return Operand{};}

//Variable to Constant artihmetic operations
Operand Variable::operator+(const Constant& other) const{return Operand{};}
Operand Variable::operator-(const Constant& other) const{return Operand{};}
Operand Variable::operator*(const Constant& other) const{return Operand{};}
Operand Variable::operator/(const Constant& other) const{return Operand{};}
Operand Variable::raise_pow(const Constant& other) const{return Operand{};}

//Variable to Variable arithmetic operations
Operand Variable::operator+(const Variable& other) const{return Operand{};}
Operand Variable::operator-(const Variable& other) const{return Operand{};}
Operand Variable::operator*(const Variable& other) const{return Operand{};}
Operand Variable::operator/(const Variable& other) const{return Operand{};}
Operand Variable::raise_pow(const Variable& other) const{return Operand{};}


//Variable to Term arithmetic operations
Operand Variable::operator+(const Term& other) const{return Operand{};}
Operand Variable::operator-(const Term& other) const{return Operand{};}
Operand Variable::operator*(const Term& other) const{return Operand{};}
Operand Variable::operator/(const Term& other) const{return Operand{};}
Operand Variable::raise_pow(const Term& other) const{return Operand{};}

//Variable to Expression arithmetic operations
Operand Variable::operator+(const Expression& other) const{return Operand{};}
Operand Variable::operator-(const Expression& other) const{return Operand{};}
Operand Variable::operator*(const Expression& other) const{return Operand{};}
Operand Variable::operator/(const Expression& other) const{return Operand{};}
Operand Variable::raise_pow(const Expression& other) const{return Operand{};}


//Term to Constant arithmetic operations
Operand Term::operator+(const Constant& other) const{return Operand{};}
Operand Term::operator-(const Constant& other) const{return Operand{};}
Operand Term::operator*(const Constant& other) const{return Operand{};}
Operand Term::operator/(const Constant& other) const{return Operand{};}
Operand Term::raise_pow(const Constant& other) const{return Operand{};}

//Term to Variable arithmetic operations
Operand Term::operator+(const Variable& other) const{return Operand{};}
Operand Term::operator-(const Variable& other) const{return Operand{};}
Operand Term::operator*(const Variable& other) const{return Operand{};}
Operand Term::operator/(const Variable& other) const{return Operand{};}
Operand Term::raise_pow(const Variable& other) const{return Operand{};}

//Term to Term arithmetic operations
Operand Term::operator+(const Term& other) const{return Operand{};}
Operand Term::operator-(const Term& other) const{return Operand{};}
Operand Term::operator*(const Term& other) const{return Operand{};}
Operand Term::operator/(const Term& other) const{return Operand{};}
Operand Term::raise_pow(const Term& other) const{return Operand{};}

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