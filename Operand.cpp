
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

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

const unsigned O_ARRAY_SIZE = 18;
Operand (*add_functions[O_ARRAY_SIZE])(const Operand&, const Operand&) = {
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
Operand (*sub_functions[O_ARRAY_SIZE])(const Operand&, const Operand&) = {
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
Operand (*mul_functions[O_ARRAY_SIZE])(const Operand&, const Operand&) = {
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
Operand (*div_functions[O_ARRAY_SIZE])(const Operand&, const Operand&) = {
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
Operand (*pow_functions[O_ARRAY_SIZE])(const Operand&, const Operand&) = {
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

bool (*eq_functions[O_ARRAY_SIZE])(const Operand&, const Operand&) = {
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

bool (*neq_functions[O_ARRAY_SIZE])(const Operand&, const Operand&) = {
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
			// point = (void *)(new Expression{Return_Internal_Ref<Expression>(ref)});
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
	switch(type){
		case DataType::Constant:
			return this->get<Constant>().power_print();
		case DataType::Variable:
			return this->get<Variable>().power_print();
		case DataType::Term:
			return this->get<Term>().power_print();
		default:
			return "stdout: Unknown Type power_print";
		}
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
				os << "stdout: Operand::operator<< for Expression is not defined yet";
				break;
			default:
				os << "stdout: Unknown Type";
		}
	}else os << "stdout: nullptr";
	return os;
}