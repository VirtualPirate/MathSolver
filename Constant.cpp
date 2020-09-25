#include <iostream>
#include <string>
#include <sstream>
#include <cmath>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "SimpleExpression.hpp"
#include "Operation_Functions.hpp"

//Constructors
Constant::Constant(void):value{0}{}
Constant::Constant(double val): value{val}{}
Constant::Constant(const Constant& ref): value{ref.value}{}
Constant::Constant(const Constant&& ref): value{ref.value}{}
Constant::Constant(const Constant* point): value{point->value}{}

// Constant to Constant assignment operators
Constant& Constant::operator=(double val){value = val;return *this;}
Constant& Constant::operator=(const Constant& ref){value = ref.value;return *this;}
Constant& Constant::operator=(const Constant&& ref){value = ref.value;return *this;}

//Constant to Constant comparison operators
bool Constant::operator==(const Constant& other) const {return value == other.value;}
bool Constant::operator!=(const Constant& other) const {return value != other.value;}

// Some other functions
std::string Constant::power_print() const{
	ostringstream stream;
	stream << *this;
	return stream.str();
}

Constant Constant::abs() const {return Constant{fabs(value)};}


// Constant to Constant arithmetic operators
Constant Constant::operator+(const Constant& other) const
{return Constant_Constant_add(*this, other);}
Constant Constant::operator-(const Constant& other) const
{return Constant_Constant_sub(*this, other);}
Constant Constant::operator*(const Constant& other) const
{return Constant_Constant_mul(*this, other);}
Constant Constant::operator/(const Constant& other) const
{return Constant_Constant_div(*this, other);}
Constant Constant::raise_pow(const Constant& other) const
{return Constant_Constant_pow(*this, other);}


Constant Constant::operator+() const {return +value;}
Constant Constant::operator-() const {return -value;}


ostream& operator<<(ostream& os, const Constant& ref){
	os << ref.value;
	return os;
}