#include <vector>
#include <iostream>
#include <sstream>

#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "OperandList.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

std::ostream& operator<<(std::ostream& os, const Expression& ref){
	if(!ref.isNull()){
		bool brace = false;
		if(ref.getPower() != Operand{(double)1})
			brace = true;
		if(brace)
			os << '(';
		const std::vector<Operand>& fields = ref.getFields();
		os << *(fields.begin());
		for(auto each=fields.begin()+1; each!=fields.end(); each++){
			if(!each->is_negative())
				os << " + " << *each;
			else
				os << *each;
		}
		if(brace)
			os << ")^" << ref.getPower().power_print();
	}
	else{
		os << "null_expression{}";
	}
	return os;
}

std::string Expression::power_print() const{
	std::ostringstream stream;
	stream << '(';
	stream << *this;
	stream << ')';
	return stream.str();
}
bool Expression::is_negative() const {
	return false;
}
bool Expression::negative_power() const {
	return power.is_negative();
}

Operand Expression::simplify() const {
	return *this;
}
//Operand to double arithmetic operators
Operand Expression::operator+(const double& other) const {return *this + Operand{other};}
Operand Expression::operator-(const double& other) const {return *this - Operand{other};}
Operand Expression::operator*(const double& other) const {return *this * Operand{other};}
Operand Expression::operator/(const double& other) const {return *this / Operand{other};}
Operand Expression::raise_pow(const double& other) const {return this->raise_pow(Operand{other});}

//Expression to Operand arithmetic operators
Operand Expression::operator+(const Operand& other) const {return Operand{*this} + other;}
Operand Expression::operator-(const Operand& other) const {return Operand{*this} - other;}
Operand Expression::operator*(const Operand& other) const {return Operand{*this} * other;}
Operand Expression::operator/(const Operand& other) const {return Operand{*this} / other;}
Operand Expression::raise_pow(const Operand& other) const {return Operand{*this}.raise_pow(other);}