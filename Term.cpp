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
#include "Substitutor.hpp"

#include "Tests.hpp"


void Term::extend(const Term& ref){
	is_simplified = false;
	fields.insert(fields.end(), ref.fields.begin(), ref.fields.end());
}
std::ostream& operator<<(std::ostream& os, const Term& ref){
	if(!ref.isNull()){
		bool brace = false;
		if(ref.getPower() != Operand{(double)1})
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
std::vector<Operand> Term::internal_simplify() const {
	std::vector<Operand> result;
	Operand operand;
	for(const auto& each: fields){
		operand = each.simplify();
		if(operand.getType() == DataType::Term && operand.getPower() == Constant::power_one){
			const Term& term =  operand.get<Term>();
			result.insert(result.end(), term.fields.begin(), term.fields.end());
		}
		else
			result.push_back(operand);
	}
	return result;
} 
// void Term::simplify_() {return *this;
	// if(!is_simplified){
	// 	//This for loop eliminates all the ones inside the Term
	// 	for(auto i=fields.begin(); i != fields.end(); i++){
	// 		if(*i == Constant::power_one)
	// 			fields.erase(i);
	// 	}

	// 	if(power != Constant::power_one){
	// 		for(auto i=fields.begin(); i != fields.end();i++)
	// 			*i = i->raise_pow(power.simplify());
	// 	}
	// 	this->fields = this->internal_simplify();
	// 	Operand result;
	// 	for(auto i=fields.begin(); i != fields.end(); i++){
	// 		for(auto j=i+1; j != fields.end(); j++){
	// 			result = (*i) * (*j);
	// 			if(result && result.type != DataType::Term){
	// 				std::cout << "*i = " << *i << "  " << "*j = " << *j << std::endl; 
	// 				fields.erase(i);
	// 				fields.erase(j-1);
	// 				fields.insert(fields.begin(), result);
	// 				i = fields.begin();
	// 				j = i+1;
	// 			}
	// 		}
	// 	}
	// 	// Moves the Constant(coefficient) to the first index of the fields.
	// 	auto swap_iter = fields.begin() + begin(DataType::Constant).getIndex();
	// 	if(swap_iter != fields.end())
	// 		std::iter_swap(fields.begin(), swap_iter);
	// 	is_simplified = true;
	// }

// }

Operand Term::simplify() const {
	return *this;
	// Term copy{*this};
	// if(!is_simplified)
	// 	copy.simplify_();
	// if(copy.fields.size() == 1)
	// 	return copy.fields.at(0);
	// else if(this->power == Constant::power_zero)
	// 	return 1;
	// return copy;
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

Term Term::getBase() const {
	return Term{fields};
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

bool Term::operator==(const Term& ref) const {
	if(same_operand_set(*this, ref) && power == ref.power)
		return true;
	return false;
}

bool Term::operator!=(const Term& ref) const {
	return !(*this == ref);
}

bool same_operand_set(const Term& first, const Term& second){
	if(first.fields.size() == second.fields.size()){
		for(auto each=first.fields.cbegin(); each!=first.fields.cend(); each++){
			if(std::find(second.fields.cbegin(), second.fields.cend(), *each) == second.fields.cend())
				return false;
		}
		return true;
	}
	return false;
}