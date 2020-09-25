
#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "SimpleExpression.hpp"
#include "Operation_Functions.hpp"

Operand Operand_null(const Operand& first, const Operand& second){
	return Operand{};}
bool Operand_bool(const Operand& first, const Operand& second){
	return false;}
bool Operand_neq_bool(const Operand& first, const Operand& second){
	return true;
}

const unsigned O_ARRAY_SIZE = 18;

void* allocate_n_return(const Operand& ref){
	void* point = nullptr;
	if(!ref.is_null){
	switch(ref.type){
		case DataType::Constant:
			point = (void *)(new Constant{Return_Internal_Ref<Constant>(ref)});
			break;
		case DataType::Variable:
			// point = (void *)(new Variable{Return_Internal_Ref<Variable>(ref)});
			break;
		case DataType::ConstVar:
			// point = (void *)(new ConstVar{Return_Internal_Ref<ConstVar>(ref)});
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
Operand::Operand(const Constant& val): value{(void*)(new Constant{val})}, type{DataType::Constant}, is_null{false}{}
Operand& Operand::operator=(const Constant& ref){
	if(value) free(value);
	value = (void*)(new Constant{ref});
	type = DataType::Constant;
	is_null = false;
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

Operand::operator bool() const{
	if((!is_null) && value)
		return true;
	return false;
}


