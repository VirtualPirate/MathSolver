#include <vector>
#include <iostream>
#include <sstream>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "OperandList.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

OperandList::OperandList(): fields{}, power{1}, is_simplified{false}, is_null{true}{}

OperandList::OperandList(const OperandList& ref): fields{ref.fields}, power{ref.power}, is_simplified{ref.is_simplified}, is_null{ref.is_null}{}
OperandList& OperandList::operator=(const OperandList& ref){
	fields = ref.fields;
	power = ref.power;
	is_simplified = ref.is_simplified;
	is_null = ref.is_null;
	return *this;
}
OperandList::OperandList(OperandList&& ref): fields{std::move(ref.fields)}, power{std::move(ref.power)}, is_simplified{ref.is_simplified}, is_null{ref.is_null}{
	ref.is_null = true;
}
OperandList& OperandList::operator=(OperandList&& ref){
	fields = std::move(ref.fields);
	power = std::move(ref.power);
	is_simplified = ref.is_simplified;
	is_null = ref.is_null;

	ref.is_null = true;
	return *this;
}



OperandList::OperandList(const Constant& ref): fields{{Operand{ref}}}, power{1}, is_simplified{true}, is_null{false}{}
OperandList& OperandList::operator=(const Constant& ref){
	fields.clear();
	fields.push_back(Operand{ref});
	power = 1;
	is_simplified = true;
	is_null = false;
	return *this;
}
OperandList::OperandList(const Variable& ref): fields{{Operand{ref}}}, power{1}, is_simplified{true}, is_null{false}{}
OperandList& OperandList::operator=(const Variable& ref){
	fields.clear();
	fields.push_back(Operand{ref});
	power = 1;
	is_simplified = true;
	is_null = false;
	return *this;
}
OperandList::OperandList(const Operand& ref): fields{{ref}}, power{1}, is_simplified{true}, is_null{false}{}
OperandList& OperandList::operator=(const Operand& ref){
	fields.clear();
	fields.push_back(ref);
	power = 1;
	is_simplified = true;
	is_null = false;
	return *this;
}

OperandList::OperandList(const std::vector<Operand>& ref): fields{ref}, power{1}, is_simplified{false}, is_null{false}{}

// Getter methods
const std::vector<Operand>& OperandList::getFields() const {
	return fields;
}
const Operand& OperandList::getPower() const {
	return power;
}
const bool& OperandList::isSimplified() const {
	return is_simplified;
}
const bool& OperandList::isNull() const {
	return is_null;
}

//Setter Methods
void OperandList::setNull(const bool& ref){
	is_null = ref;
}
void OperandList::setPower(const Operand& ref){
	power = ref;
}

//field modifiers
void OperandList::insert(const Constant& ref){
	fields.push_back(Operand{ref});
}
void OperandList::insert(const Variable& ref){
	fields.push_back(Operand{ref});
}
void OperandList::insert(const Operand& ref){
	fields.push_back(ref);
}

//Iterator functions
OperandList::iterator OperandList::begin(DataType type){
	if(fields.at(0).getType() == type)
		return OperandList::iterator{this, 0, type};
	return OperandList::iterator{this, 0, type} + 1;
}
OperandList::iterator OperandList::end(DataType type) {
	return OperandList::iterator{this, (int)this->fields.size(), type};
}

OperandList::operator bool() const {return is_null;}
// std::ostream& operator<<(std::ostream& os, const OperandList& ref){
// 	if(!ref.is_null){
// 	os << *(ref.fields.begin());
// 	for(auto each=ref.fields.begin()+1; each!=ref.fields.end(); each++)
// 		if(each->getType() == DataType::Constant)
// 			os << " * " << *each;
// 		else
// 			os << *each;
// 	}
// 	else{
// 		os << "null_term{}";
// 	}
// 	return os;
// }

// OperandList::iterator definition
OperandList::iterator::iterator(): index{0}{}
OperandList::iterator::iterator(const OperandList::iterator& ref): ref{ref.ref}, index{ref.index}, iterative{ref.iterative}{}
OperandList::iterator::iterator(OperandList* point, int index_, DataType type): ref{point}, index{index_}, iterative{type}{}

OperandList::iterator& OperandList::iterator::operator=(const OperandList::iterator& ref){
	this->ref = ref.ref;
	index = ref.index;
	return *this;
}

void OperandList::iterator::set_iterative(const DataType& type){
	iterative = type;
	index = 0;
}

int OperandList::iterator::getIndex() const {
	return index;
}

//OperandList::iterator operations
int OperandList::iterator::operate_add(int other){
	int abs_index = this->index + 1;
	int rel_index = 0;
	while(abs_index < ref->fields.size() && rel_index < other){
		if(this->ref->fields.at(abs_index).getType() == iterative){
			rel_index++;
			if(rel_index == other)
				break;
		}
		abs_index++;
	}
	return abs_index;
}
int OperandList::iterator::operate_sub(int other){
	int abs_index = this->index - 1;
	int rel_index = 0;
	while(abs_index > 0 && rel_index < other){
		if(this->ref->fields.at(abs_index).getType() == iterative){
			rel_index++;
			if(rel_index == other)
				break;
		}
		abs_index--;
	}
	return abs_index;
}
OperandList::iterator OperandList::iterator::operator+(int other){
	return OperandList::iterator{this->ref, operate_add(other), this->iterative};
}

OperandList::iterator OperandList::iterator::operator-(int other){
	return OperandList::iterator{this->ref, operate_sub(other), this->iterative};
}

OperandList::iterator& OperandList::iterator::operator+=(int other){
	this->index = operate_add(other);
	return *this;
}

OperandList::iterator& OperandList::iterator::operator-=(int other){
	this->index = operate_sub(other);
	return *this;
}

//Pre-Increment methods
OperandList::iterator& OperandList::iterator::operator++(){
	this->index = operate_add(1);
	return *this;
}
OperandList::iterator& OperandList::iterator::operator--(){
	this->index = operate_sub(1);
	return *this;
}

//Post-Increment methods
OperandList::iterator OperandList::iterator::operator++(int other){
	++(*this);
	return (*this) - 1;
}
OperandList::iterator OperandList::iterator::operator--(int other){
	++(*this);
	return (*this) + 1;
}

Operand& OperandList::iterator::operator*(){
	return ref->fields.at(index);
}

//Iterator comparison operators
bool OperandList::iterator::operator==(const OperandList::iterator& ref) const {
	return this->index == ref.index;
}

bool OperandList::iterator::operator!=(const OperandList::iterator& ref) const {
	return this->index != ref.index;
}
