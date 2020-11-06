#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

//Constructors
Constant::Constant(void):value{0}{}
Constant::Constant(double val): value{val}{}
Constant::Constant(const Constant& ref): value{ref.value}{}
Constant::Constant(const Constant* point): value{point->value}{}

// Constant to Constant assignment operators
Constant& Constant::operator=(double val){value = val;return *this;}
Constant& Constant::operator=(const Constant& ref){value = ref.value;return *this;}

//Constant to Constant comparison operators
bool Constant::operator==(const Constant& other) const {return value == other.value;}
bool Constant::operator!=(const Constant& other) const {return value != other.value;}

//Constant to double arithmetic operators
Operand Constant::operator+(const double& other) const {return *this + Constant{other};}
Operand Constant::operator-(const double& other) const {return *this + Constant{other};}
Operand Constant::operator*(const double& other) const {return *this + Constant{other};}
Operand Constant::operator/(const double& other) const {return *this + Constant{other};}
Operand Constant::raise_pow(const double& other) const {return *this + Constant{other};}


//Constant to Operand arithmetic operators
Operand Constant::operator+(const Operand& other) const {return Operand{*this} + other;}
Operand Constant::operator-(const Operand& other) const {return Operand{*this} - other;}
Operand Constant::operator*(const Operand& other) const {return Operand{*this} * other;}
Operand Constant::operator/(const Operand& other) const {return Operand{*this} / other;}
Operand Constant::raise_pow(const Operand& other) const {return Operand{*this}.raise_pow(other);}


// Some other functions
Operand Constant::simplify() const {return *this;}
std::string Constant::power_print() const{
	std::ostringstream stream;
	stream << *this;
	return stream.str();
}
bool Constant::is_negative() const {return value < 0;}
bool Constant::negative_power() const {return false;}
Constant Constant::abs() const {return Constant{fabs(value)};}


//Getter methods
const double& Constant::getValue() const {
	return value;
}

void Constant::setValue(const double& ref){
	value = ref;
}


Constant Constant::operator+() const {return +value;}
Constant Constant::operator-() const {return -value;}


std::ostream& operator<<(std::ostream& os, const Constant& ref){
	os << ref.value;
	return os;
}