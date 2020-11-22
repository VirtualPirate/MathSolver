
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>

#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

Operand Operand_null(const Operand& first, const Operand& second){
	return Operand{};}
bool Operand_bool(const Operand& first, const Operand& second){
	return false;}
bool Operand_neq_bool(const Operand& first, const Operand& second){
	return true;
}

// const unsigned O_ARRAY_SIZE = 18;
OperationFunction Operand::add_functions[] = {
	Operand_Operand_add<Constant, Constant>,
	Operand_Operand_add<Constant, Variable>,
	Operand_Operand_add<Constant, Term>,
	Operand_Operand_add<Constant, Expression>,
	Operand_Operand_add<Variable, Constant>,
	Operand_Operand_add<Variable, Variable>,
	Operand_Operand_add<Variable, Term>,
	Operand_Operand_add<Variable, Expression>,
	Operand_Operand_add<Term, Constant>,
	Operand_Operand_add<Term, Variable>,
	Operand_Operand_add<Term, Term>,
	Operand_Operand_add<Term, Expression>,
	Operand_Operand_add<Expression, Constant>,
	Operand_Operand_add<Expression, Variable>,
	Operand_Operand_add<Expression, Term>,
	Operand_Operand_add<Expression, Expression>,
	Operand_null
};
OperationFunction Operand::sub_functions[] = {
	Operand_Operand_sub<Constant, Constant>,
	Operand_Operand_sub<Constant, Variable>,
	Operand_Operand_sub<Constant, Term>,
	Operand_Operand_sub<Constant, Expression>,
	Operand_Operand_sub<Variable, Constant>,
	Operand_Operand_sub<Variable, Variable>,
	Operand_Operand_sub<Variable, Term>,
	Operand_Operand_sub<Variable, Expression>,
	Operand_Operand_sub<Term, Constant>,
	Operand_Operand_sub<Term, Variable>,
	Operand_Operand_sub<Term, Term>,
	Operand_Operand_sub<Term, Expression>,
	Operand_Operand_sub<Expression, Constant>,
	Operand_Operand_sub<Expression, Variable>,
	Operand_Operand_sub<Expression, Term>,
	Operand_Operand_sub<Expression, Expression>,
	Operand_null
};
OperationFunction Operand::mul_functions[] = {
	Operand_Operand_mul<Constant, Constant>,
	Operand_Operand_mul<Constant, Variable>,
	Operand_Operand_mul<Constant, Term>,
	Operand_Operand_mul<Constant, Expression>,
	Operand_Operand_mul<Variable, Constant>,
	Operand_Operand_mul<Variable, Variable>,
	Operand_Operand_mul<Variable, Term>,
	Operand_Operand_mul<Variable, Expression>,
	Operand_Operand_mul<Term, Constant>,
	Operand_Operand_mul<Term, Variable>,
	Operand_Operand_mul<Term, Term>,
	Operand_Operand_mul<Term, Expression>,
	Operand_Operand_mul<Expression, Constant>,
	Operand_Operand_mul<Expression, Variable>,
	Operand_Operand_mul<Expression, Term>,
	Operand_Operand_mul<Expression, Expression>,
	Operand_null
};
OperationFunction Operand::div_functions[] = {
	Operand_Operand_div<Constant, Constant>,
	Operand_Operand_div<Constant, Variable>,
	Operand_Operand_div<Constant, Term>,
	Operand_Operand_div<Constant, Expression>,
	Operand_Operand_div<Variable, Constant>,
	Operand_Operand_div<Variable, Variable>,
	Operand_Operand_div<Variable, Term>,
	Operand_Operand_div<Variable, Expression>,
	Operand_Operand_div<Term, Constant>,
	Operand_Operand_div<Term, Variable>,
	Operand_Operand_div<Term, Term>,
	Operand_Operand_div<Term, Expression>,
	Operand_Operand_div<Expression, Constant>,
	Operand_Operand_div<Expression, Variable>,
	Operand_Operand_div<Expression, Term>,
	Operand_Operand_div<Expression, Expression>,
	Operand_null
};
OperationFunction Operand::pow_functions[] = {
	Operand_Operand_pow<Constant, Constant>,
	Operand_Operand_pow<Constant, Variable>,
	Operand_Operand_pow<Constant, Term>,
	Operand_Operand_pow<Constant, Expression>,
	Operand_Operand_pow<Variable, Constant>,
	Operand_Operand_pow<Variable, Variable>,
	Operand_Operand_pow<Variable, Term>,
	Operand_Operand_pow<Variable, Expression>,
	Operand_Operand_pow<Term, Constant>,
	Operand_Operand_pow<Term, Variable>,
	Operand_Operand_pow<Term, Term>,
	Operand_Operand_pow<Term, Expression>,
	Operand_Operand_pow<Expression, Constant>,
	Operand_Operand_pow<Expression, Variable>,
	Operand_Operand_pow<Expression, Term>,
	Operand_Operand_pow<Expression, Expression>,
	Operand_null
};

ComparisonFunction Operand::eq_functions[] = {
	Operand_Operand_eq<Constant, Constant>,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_Operand_eq<Variable, Variable>,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_Operand_eq<Term, Term>,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool
};

ComparisonFunction Operand::neq_functions[] = {
	Operand_Operand_neq<Constant, Constant>,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_Operand_neq<Variable, Variable>,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_Operand_neq<Term, Term>,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool
};

GetPowerFunction Operand::get_power_functions[] = {
	getPower<Constant>,
	getPower<Variable>,
	getPower<Term>,
	getPower<Expression>
};

SetPowerFunction Operand::set_power_functions[] = {
	setPower<Constant>,
	setPower<Variable>,
	setPower<Term>,
	setPower<Expression>
};

CheckFunction Operand::is_negative_functions[] = {
	is_negative<Constant>,
	is_negative<Variable>,
	is_negative<Term>,
	is_negative<Expression>
};

CheckFunction Operand::negative_power_functions[] = {
	negative_power<Constant>,
	negative_power<Variable>,
	negative_power<Term>,
	negative_power<Expression>
};

PowerPrintFunc Operand::power_print_functions[] = {
	power_print<Constant>,
	power_print<Variable>,
	power_print<Term>,
	power_print<Expression>
};

AllocateFunction Operand::allocate_functions[] = {
	allocate<Constant>,
	allocate<Variable>,
	allocate<Term>,
	allocate<Expression>
};

CoutFunction Operand::operator_cout_functions[] = {
	cout_<Constant>,
	cout_<Variable>,
	cout_<Term>,
	cout_<Expression>
};

SimplifyFunction Operand::simplify_functions[] = {
	simplify<Constant>,
	simplify<Variable>,
	simplify<Term>,
	simplify<Expression>
};

unsigned func_hash(DataType first_type, DataType second_type){
	int first_num = (int)first_type;
	int second_num = (int)second_type;
	if(first_num >= 0 && second_num >= 0)
		return (unsigned)(first_num * 4 + second_num);
	else
		return O_ARRAY_SIZE - 2;
}

Operand::Operand(): value{nullptr}, type{DataType::None}, is_null{true}{}

Operand::Operand(double value): value{(void*)(new Constant{value})}, type{DataType::Constant}, is_null{false}{}
Operand& Operand::operator=(double val){
	if(value) free(value);
	value = (void*)(new Constant{val});
	type = DataType::Constant;
	is_null = false;
	return *this;
}
Operand::Operand(const Constant& val): value{(void*)(new Constant{val})}, type{DataType::Constant}, is_null{false}{}
Operand& Operand::operator=(const Constant& ref){
	if(value) free(value);
	value = (void*)(new Constant{ref});
	type = DataType::Constant;
	is_null = false;
	return *this;
}

Operand::Operand(const Variable& ref): value{(void*)(new Variable{ref})}, type{DataType::Variable}, is_null{false}{}
Operand& Operand::operator=(const Variable& ref){
	if(value) free(value);
	value = (void*)(new Variable{ref});
	type = DataType::Variable;
	is_null = false;
	return *this;
}
Operand::Operand(const Term& ref): value{(void*)(new Term{ref})}, type{DataType::Term}, is_null{ref.isNull()}{}
Operand& Operand::operator=(const Term& ref){
	if(value) free(value);
	value = (void*)(new Term{ref});
	type = DataType::Term;
	is_null = ref.isNull();
	return *this;
}
Operand::Operand(const Expression& ref): value{(void*)(new Expression{ref})}, type{DataType::Expression}, is_null{ref.isNull()}{}
Operand& Operand::operator=(const Expression& ref){
	if(value) free(value);
	value = (void*)(new Expression{ref});
	type = DataType::Expression;
	is_null = ref.isNull();
	return *this;
}

// Copy and move semantics
Operand::Operand(const Operand& ref): value{ref.allocate()}, type{ref.type}, is_null{ref.is_null}{}
Operand::Operand(Operand&& ref): value{ref.value}, type{ref.type}, is_null{ref.is_null}{
	ref.value = nullptr;
	ref.is_null = true;
}
Operand& Operand::operator=(const Operand& ref){
	if(value) free(value);
	value = ref.allocate();
	type = ref.type;
	is_null = ref.is_null;
	return *this;

}
Operand& Operand::operator=(Operand&& ref){
	if(value) free(value);
	value = ref.value;
	ref.value = nullptr;
	type = ref.type;
	is_null = ref.is_null;
	ref.is_null = true;
	return *this;
}
//Destructor
Operand::~Operand(){free(value);}

//Getters setters

const DataType& Operand::getType() const{
	return type;
}
bool Operand::isNull() const{
	return is_null;
}

//Operand to Operand comparison operators
bool Operand::operator==(const Operand& other) const {	
	return eq_functions[func_hash(this->type, other.type)](*this, other);}

bool Operand::operator!=(const Operand& other) const {
	return neq_functions[func_hash(this->type, other.type)](*this, other);}

//Operand to double comparison operators
bool Operand::operator==(const double& other) const {return *this == Operand{other};}
bool Operand::operator!=(const double& other) const {return *this != Operand{other};}

//Operand to Constant comparison operators
bool Operand::operator==(const Constant& other) const {return *this == Operand{other};}
bool Operand::operator!=(const Constant& other) const {return *this != Operand{other};}

//Operand to Variable comparison operators
bool Operand::operator==(const Variable& other) const {return *this == Operand{other};}
bool Operand::operator!=(const Variable& other) const {return *this != Operand{other};}

//Operand to Term comparison operators
bool Operand::operator==(const Term& other) const {return *this == Operand{other};}
bool Operand::operator!=(const Term& other) const {return *this != Operand{other};}

//Operand to Expression comparison operators
bool Operand::operator==(const Expression& other) const {return *this == Operand{other};}
bool Operand::operator!=(const Expression& other) const {return *this != Operand{other};}

Operand::operator bool() const{
	if((!is_null) && value && type != DataType::None)
		return true;
	return false;
}

bool Operand::same_type(const Operand& other) const {
	return type == other.type;
}
bool Operand::same_type(const DataType& other) const {
	return type == other;
}
//Operand to Operand arithmetic operators
Operand Operand::operator+(const Operand& other) const {
	return add_functions[func_hash(this->type, other.type)](*this, other);}

Operand Operand::operator-(const Operand& other) const {
	return sub_functions[func_hash(this->type, other.type)](*this, other);}

Operand Operand::operator*(const Operand& other) const {
	// cout << "invoked Operand_Operand_mul func" << endl;
	return mul_functions[func_hash(this->type, other.type)](*this, other);}

Operand Operand::operator/(const Operand& other) const {
	return div_functions[func_hash(this->type, other.type)](*this, other);}

Operand Operand::raise_pow(const Operand& other) const {
	return pow_functions[func_hash(this->type, other.type)](*this, other);}

Operand& Operand::operator+=(const Operand& other){
	*this = *this + other;
	return *this;
}
Operand& Operand::operator-=(const Operand& other){
	*this = *this - other;
	return *this;
}
Operand& Operand::operator*=(const Operand& other){
	*this = *this * other;
	return *this;
}
Operand& Operand::operator/=(const Operand& other){
	*this = *this / other;
	return *this;
}

//Operand to double arithmetic operators
Operand Operand::operator+(const double& other) const {return *this + Operand{other};}
Operand Operand::operator-(const double& other) const {return *this - Operand{other};}
Operand Operand::operator*(const double& other) const {return *this * Operand{other};}
Operand Operand::operator/(const double& other) const {return *this / Operand{other};}
Operand Operand::raise_pow(const double& other) const {return this->raise_pow(Operand{other});}

//Operand to Constant arithmetic operators
Operand Operand::operator+(const Constant& other) const {return *this + Operand{other};}
Operand Operand::operator-(const Constant& other) const {return *this - Operand{other};}
Operand Operand::operator*(const Constant& other) const {return *this * Operand{other};}
Operand Operand::operator/(const Constant& other) const {return *this / Operand{other};}
Operand Operand::raise_pow(const Constant& other) const {return this->raise_pow(Operand{other});}

//Operand to Variable arithmetic operators
Operand Operand::operator+(const Variable& other) const {return *this + Operand{other};}
Operand Operand::operator-(const Variable& other) const {return *this - Operand{other};}
Operand Operand::operator*(const Variable& other) const {return *this * Operand{other};}
Operand Operand::operator/(const Variable& other) const {return *this / Operand{other};}
Operand Operand::raise_pow(const Variable& other) const {return this->raise_pow(Operand{other});}

//Operand to Term arithmetic operators
Operand Operand::operator+(const Term& other) const {return *this + Operand{other};}
Operand Operand::operator-(const Term& other) const {return *this - Operand{other};}
Operand Operand::operator*(const Term& other) const {return *this * Operand{other};}
Operand Operand::operator/(const Term& other) const {return *this / Operand{other};}
Operand Operand::raise_pow(const Term& other) const {return this->raise_pow(Operand{other});}

//Operand to Expression arithmetic operators
Operand Operand::operator+(const Expression& other) const {return *this + Operand{other};}
Operand Operand::operator-(const Expression& other) const {return *this - Operand{other};}
Operand Operand::operator*(const Expression& other) const {return *this * Operand{other};}
Operand Operand::operator/(const Expression& other) const {return *this / Operand{other};}
Operand Operand::raise_pow(const Expression& other) const {return this->raise_pow(Operand{other});}

//Operand to Constant +=
Operand& Operand::operator+=(const Constant& other){*this += Operand{other};return *this;}
Operand& Operand::operator-=(const Constant& other){*this -= Operand{other};return *this;}
Operand& Operand::operator*=(const Constant& other){*this *= Operand{other};return *this;}
Operand& Operand::operator/=(const Constant& other){*this /= Operand{other};return *this;}

//Operand to Variable +=
Operand& Operand::operator+=(const Variable& other){*this += Operand{other};return *this;}
Operand& Operand::operator-=(const Variable& other){*this -= Operand{other};return *this;}
Operand& Operand::operator*=(const Variable& other){*this *= Operand{other};return *this;}
Operand& Operand::operator/=(const Variable& other){*this /= Operand{other};return *this;}

//Operand to Term +=
Operand& Operand::operator+=(const Term& other){*this += Operand{other};return *this;}
Operand& Operand::operator-=(const Term& other){*this -= Operand{other};return *this;}
Operand& Operand::operator*=(const Term& other){*this *= Operand{other};return *this;}
Operand& Operand::operator/=(const Term& other){*this /= Operand{other};return *this;}

//Operand to Expression +=
Operand& Operand::operator+=(const Expression& other){*this += Operand{other};return *this;}
Operand& Operand::operator-=(const Expression& other){*this -= Operand{other};return *this;}
Operand& Operand::operator*=(const Expression& other){*this *= Operand{other};return *this;}
Operand& Operand::operator/=(const Expression& other){*this /= Operand{other};return *this;}

const Operand& Operand::getPower() const {
	int index = (int)type;
	if (index > -1)
		return get_power_functions[index](this);
	std::cout << "stdout: Operand::getPower() on nulltype" << std::endl;
	return Constant::power_null;

}
void Operand::setPower(const Operand& pow){
	int index = (int)type;
	if(index > -1)
		set_power_functions[index](this, pow);
	else
		std::cout << "stdout: Operand::setPower() on nulltype" << std::endl;

}
std::string Operand::power_print() const {
	int index = (int)type;
	if (index > -1)
		return power_print_functions[index](this);
	return "stdout: Unknown type power_print";

	}

void* Operand::allocate() const {
	int index = (int)type;
	if (index > -1)
		return allocate_functions[index](this);
	std::cout << "stdout: Unknown type allocate()";
	return nullptr;
}

bool Operand::is_negative() const {
	int index = (int)type;
	if (index > -1)
		return is_negative_functions[index](this);
	std::cout << "stdout: Unknown type is_negative";
	return false;

}
bool Operand::negative_power() const {
	int index = (int)type;
	if (index > -1)
		return is_negative_functions[index](this);
	std::cout << "stdout: Unknown type negative_power";
	return false;
}
Operand Operand::simplify() const {
	int index = (int)type;
	if (index > -1)
		return simplify_functions[index](this);
	std::cout << "stdout: Unknown type simplify";
	return *this;
}
std::ostream& operator<<(std::ostream& os, const Operand& ref){
	if(!ref.is_null){
		int index = (int)ref.type;
		if (index > -1)
			return Operand::operator_cout_functions[index](os, ref);
		os << "stdout: Unknown type operator<<";
	}else
		os << "stdout: nullptr in operator<<";
	return os;
}