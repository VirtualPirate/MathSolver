#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
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


//Getter and setter Methods
const char& Variable::getName() const {
	return name;
}
void Variable::setName(const char& ref){
	name = ref;
}

const Operand& Variable::getPower() const {
	return power;
}
void Variable::setPower(const Operand& ref){
	power = ref;
}

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

std::string Variable::power_print() const{
	std::ostringstream stream;
	stream << *this;
	return stream.str();
}
bool Variable::is_negative() const {
	return false;
}
std::ostream& operator<<(std::ostream& os, const Variable& ref){
	if(ref.power == Operand{Constant{1}})
		os << ref.name;
	else
		os << ref.name << "^" << ref.getPower().power_print();
	return os;
}