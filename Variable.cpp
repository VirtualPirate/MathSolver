#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "SimpleExpression.hpp"
#include "Operation_Functions.hpp"

std::unordered_map<char, Constant> var_values;

//Copy Assignment operator
Variable& Variable::operator=(const Variable& ref){
	name = ref.name;
	power = ref.power;
	return *this;
}
//Move assignment operator
Variable& Variable::operator=(Variable&& ref){
	name = std::move(ref.name);
	power = std::move(ref.power);
	return *this;
}

//Constructors
Variable::Variable(): name{}, power{}{}
Variable::Variable(char var_name): name{var_name}, power{Constant{1}}{}
Variable::Variable(char var_name, double pow): name{var_name}, power{Constant{pow}}{}
Variable::Variable(char var_name, const Operand& pow): name{var_name}, power{pow}{}

//Variable to Variable comparison operators
bool Variable::operator==(const Variable& ref) const {
	if(this->name == ref.name && this->power == ref.power)
		return true;
	return false;
}

bool Variable::operator!=(const Variable& ref) const {
	if(this->name != ref.name && this->power == ref.power)
		return true;
	return false;
}