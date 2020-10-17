
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <functional>

#include "Constant.hpp"
#include "Operand.hpp"
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
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
};
OperationFunction Operand::sub_functions[] = {
	Operand_Operand_sub<Constant, Constant>,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
};
OperationFunction Operand::mul_functions[] = {
	Operand_Operand_mul<Constant, Constant>,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
};
OperationFunction Operand::div_functions[] = {
	Operand_Operand_div<Constant, Constant>,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
};
OperationFunction Operand::pow_functions[] = {
	Operand_Operand_pow<Constant, Constant>,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
	Operand_null,
};

ComparisonFunction Operand::eq_functions[] = {
	Operand_Operand_eq<Constant, Constant>,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
	Operand_bool,
};

ComparisonFunction Operand::neq_functions[] = {
	Operand_Operand_neq<Constant, Constant>,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
	Operand_neq_bool,
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

void* allocate_n_return(const Operand& ref){
	void* point = nullptr;
	if(!ref.isNull()){
	switch(ref.getType()){
		case DataType::Constant:
			point = (void *)(new Constant{ref.get<Constant>()});
			break;
		case DataType::Variable:
			point = (void *)(new Variable{ref.get<Variable>()});
			break;
		case DataType::Term:
			point = (void *)(new Term{ref.get<Term>()});
			break;
		case DataType::Expression:
			point = (void *)(new Expression{ref.get<Expression>()});
			break;
		default:
			std::cout << "allocate_n_return() : Unknown Type";
		}
	}
	return point;
}

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
	// Invokes Operand::operator(double)
	*this = ref.getValue();
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
Operand::Operand(const Operand& ref): value{allocate_n_return(ref)}, type{ref.type}, is_null{ref.is_null}{}
Operand::Operand(Operand&& ref): value{ref.value}, type{ref.type}, is_null{ref.is_null}{
	ref.value = nullptr;
	ref.is_null = true;
}
Operand& Operand::operator=(const Operand& ref){
	if(value) free(value);
	value = allocate_n_return(ref);
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

Operand::operator bool() const{
	if((!is_null) && value)
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

std::string Operand::power_print() const {
	/*switch(type){
		case DataType::Constant:
			return this->get<Constant>().power_print();
		case DataType::Variable:
			return this->get<Variable>().power_print();
		case DataType::Term:
			return this->get<Term>().power_print();
		case DataType::Expression:
			return this->get<Expression>().power_print();
		default:
			return "stdout: Unknown Type power_print";
		}
*/	
	int index = (int)type;
	if (index > -1)
		return power_print_functions[index](this);
	return "stdout: Unknown type power_print";

	}

bool Operand::is_negative() const {
	/*
	switch(type){
		case DataType::Constant:
			return this->get<Constant>().is_negative();
		case DataType::Variable:
			return this->get<Variable>().is_negative();
		case DataType::Term:
			return this->get<Term>().is_negative();
		case DataType::Expression:
			return this->get<Expression>().is_negative();
		default:
			std::cout << "stdout: Unknown type is_negative";
	}
	return false;
	*/
	int index = (int)type;
	if (index > -1)
		return is_negative_functions[index](this);
	else
		std::cout << "stdout: Unknown type is_negative";
	return false;

}
bool Operand::negative_power() const {
/*	switch(type){
		case DataType::Constant:
			return this->get<Constant>().negative_power();
		case DataType::Variable:
			return this->get<Variable>().negative_power();
		case DataType::Term:
			return this->get<Term>().negative_power();
		case DataType::Expression:
			return this->get<Expression>().negative_power();
		default:
			std::cout << "stdout: Unknown type negative_power";
	}
	return false;*/
	int index = (int)type;
	if (index > -1)
		return is_negative_functions[index](this);
	else
		std::cout << "stdout: Unknown type negative_power";
	return false;
}

std::ostream& operator<<(std::ostream& os, const Operand& ref){
	if(!ref.is_null){
		switch(ref.type){
			case DataType::Constant:
				os << ref.get<Constant>();
				break;
			case DataType::Variable:
				os << ref.get<Variable>();
				break;
			case DataType::Term:
				os << ref.get<Term>();
				break;
			case DataType::Expression:
				os << ref.get<Expression>();
				break;
			default:
				os << "stdout: Unknown Type";
		}
	}else os << "stdout: nullptr";
	return os;
}