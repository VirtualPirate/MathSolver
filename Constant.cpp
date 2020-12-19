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
#include "Substitutor.hpp"

Operand const Constant::power_one{(double)1};
Operand const Constant::power_zero{(double)0};
Operand const Constant::power_null{};
//Constructors
Constant::Constant(void):value{0}{}
Constant::Constant(double val): value{val}, power{}{}
Constant::Constant(const Constant& ref): value{ref.value}, power{ref.power}{}
Constant::Constant(const Constant* point): value{point->value}, power{point->power}{}

Constant::Constant(double val, const Operand& pow): value{val}{
	setPower(pow);
}

// Constant to Constant assignment operators
Constant& Constant::operator=(double val){value = val;return *this;}
Constant& Constant::operator=(const Constant& ref){value = ref.value;power=ref.power;return *this;}

//Constant to Constant comparison operators
bool Constant::operator==(const Constant& other) const {return value == other.value && (power == other.power || (!power && !other.power));}
bool Constant::operator!=(const Constant& other) const {return !(*this == other);}

//Constant to double arithmetic operators
Operand Constant::operator+(const double& other) const {return *this + Constant{other};}
Operand Constant::operator-(const double& other) const {return *this - Constant{other};}
Operand Constant::operator*(const double& other) const {return *this * Constant{other};}
Operand Constant::operator/(const double& other) const {return *this / Constant{other};}
Operand Constant::raise_pow(const double& other) const {return this->raise_pow(Constant{other});}


//Constant to Operand arithmetic operators
Operand Constant::operator+(const Operand& other) const {return Operand{*this} + other;}
Operand Constant::operator-(const Operand& other) const {return Operand{*this} - other;}
Operand Constant::operator*(const Operand& other) const {return Operand{*this} * other;}
Operand Constant::operator/(const Operand& other) const {return Operand{*this} / other;}
Operand Constant::raise_pow(const Operand& other) const {return Operand{*this}.raise_pow(other);}


// Some other functions
Operand Constant::simplify() const {
	return *this;
}
std::string Constant::power_print() const{
	std::ostringstream stream;
	stream << *this;
	return stream.str();
}
bool Constant::is_negative() const {return value < 0;}
bool Constant::negative_power() const {return false;}
bool Constant::is_pure() const {return getPower() == Constant::power_one;}
Constant Constant::abs() const {return Constant{fabs(value)};}


//Getter methods
const double& Constant::getValue() const {
	return value;
}
const double& Constant::getBase() const {
	return value;
}
const Operand& Constant::getPower() const {
	if(power)
		return power;
	return power_one;
}

void Constant::setValue(const double& ref){
	value = ref;
}
void Constant::setPower(const Operand& ref){
	if(ref == power_one)
		power = Operand{};
	else
		power = ref;
}


Constant Constant::operator+() const {return +value;}
Constant Constant::operator-() const {return -value;}


std::ostream& operator<<(std::ostream& os, const Constant& ref){
	if(ref.power && ref.power!=(double)1)
		os << ref.value << '^' << ref.getPower().power_print();
	else
		os << ref.value;
	return os;
}