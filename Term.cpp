#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <initializer_list>

#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "OperandList.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

std::ostream& operator<<(std::ostream& os, const Term& ref){
	if(!ref.isNull()){
		bool brace = false;
		if(ref.getPower() != Operand{1})
			brace = true;
		const std::vector<Operand>& fields = ref.getFields();
		if(brace)
			os << '(';
		os << *(fields.begin());
		for(auto each=fields.begin()+1; each!=fields.end(); each++){
			if(each->getType() == DataType::Constant)
				os << " * " << *each;
			else
				os << *each;
		}
		if(brace)
			os << ")^" << ref.getPower().power_print();
	}

	else{
		os << "null_term{}";
	}
	return os;
}

std::string Term::power_print() const{
	std::ostringstream stream;
	stream << '(';
	stream << *this;
	stream << ')';
	return stream.str();
}

bool Term::is_negative() const {
	return fields.at(0).is_negative();
}
bool Term::negative_power() const {
	return power.is_negative();
}
void Term::simplify_() {
	if(!is_simplified){
		Operand result;
		for(auto i=fields.begin(); i != fields.end(); i++){
			for(auto j=i+1; j != fields.end(); j++){
				result = (*i) * (*j);
				if(result){
					fields.erase(i);
					fields.erase(j-1);
					fields.insert(fields.begin(), result);
					i = fields.begin();
					j = i+1;
				}
			}
		}
		// Moves the Constant(coefficient) to the first index of the fields.
		auto swap_iter = fields.begin() + begin(DataType::Constant).getIndex();
		if(swap_iter != fields.end())
			std::iter_swap(fields.begin(), swap_iter);
		is_simplified = true;
		if(power != Constant::power_one){
			for(auto i=fields.begin(); i != fields.end(); i++)
				*i = i->raise_pow(power);
		}
	}

}

Operand Term::simplify() const {
	Term copy{*this};
	if(!is_simplified)
		copy.simplify_();
	if(copy.fields.size() == 1)
		return copy.fields.at(0);
	return *this;
}

bool Term::is_Constant() const {
	if(fields.size() == 1 && fields.at(0).getType() == DataType::Constant)
		return true;
	return false;
}

bool Term::is_Variable() const {
	if(fields.size() == 1 && fields.at(0).getType() == DataType::Variable)
		return true;
	return false;
}

std::vector<Variable> Term::getVars() const {
	std::vector<Variable> result;
	for(auto each=cbegin(DataType::Variable); each != cend(DataType::Variable); each++)
		result.push_back((*each).get<Variable>());
	return result;
}

//Term to double arithmetic operators
Operand Term::operator+(const double& other) const {return *this + Constant{other};};
Operand Term::operator-(const double& other) const {return *this - Constant{other};};
Operand Term::operator*(const double& other) const {return *this * Constant{other};};
Operand Term::operator/(const double& other) const {return *this / Constant{other};};
Operand Term::raise_pow(const double& other) const {return this->raise_pow(Constant{other});};

//Term to Operand arithmetic operators
Operand Term::operator+(const Operand& other) const {return Operand{*this} + other;}
Operand Term::operator-(const Operand& other) const {return Operand{*this} - other;}
Operand Term::operator*(const Operand& other) const {return Operand{*this} * other;}
Operand Term::operator/(const Operand& other) const {return Operand{*this} / other;}
Operand Term::raise_pow(const Operand& other) const {return Operand{*this}.raise_pow(other);}