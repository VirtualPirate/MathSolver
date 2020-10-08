#include <vector>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "SimpleExpression.hpp"
#include "Operation_Functions.hpp"

Term::Term(): fields{}, power{1}, is_simplified{false}, is_null{true}{}

Term::Term(const Term& ref): fields{ref.fields}, power{ref.power}, is_simplified{ref.is_simplified}, is_null{ref.is_null}{}
Term& Term::operator=(const Term& ref){
	fields = ref.fields;
	power = ref.power;
	is_simplified = ref.is_simplified;
	is_null = ref.is_null;
	return *this;
}
Term::Term(Term&& ref): fields{std::move(ref.fields)}, power{std::move(ref.power)}, is_simplified{ref.is_simplified}, is_null{ref.is_null}{
	ref.is_null = true;
}
Term& Term::operator=(Term&& ref){
	fields = std::move(ref.fields);
	power = std::move(ref.power);
	is_simplified = ref.is_simplified;
	is_null = ref.is_null;

	ref.is_null = true;
	return *this;
}

// Getter methods
const std::vector<Operand>& Term::getFields(){
	return fields;
}
const Operand& Term::getPower(){
	return power;
}
const bool& Term::isSimplified(){
	return is_simplified;
}
const bool& Term::isNull(){
	return is_null;
}

//field modifiers
void Term::insert(const Constant& ref){
	fields.push_back(Operand{ref});
}
void Term::insert(const Variable& ref){
	fields.push_back(Operand{ref});
}
void Term::insert(const Operand& ref){
	fields.push_back(ref);
}

std::ostream& operator<<(std::ostream& os, const Term& ref){
	os << *(ref.fields.begin());
	for(auto each=ref.fields.begin()+1; each!=ref.fields.end(); each++)
		if(each->getType() == DataType::Constant)
			os << " * " << *each;
		else
			os << *each;
	return os;
}

// Term::iterator definition
Term::iterator::iterator(): index{0}{}
Term::iterator::iterator(const Term::iterator& ref): ref{ref.ref}, index{ref.index}, iterative{ref.iterative}{}
Term::iterator::iterator(Term* point, int index_, DataType type): ref{point}, index{index_}, iterative{type}{}

Term::iterator& Term::iterator::operator=(const Term::iterator& ref){
	this->ref = ref.ref;
	index = ref.index;
	return *this;
}

void Term::iterator::set_iterative(const DataType& type){
	iterative = type;
	index = 0;
}

//Term::iterator operations
int Term::iterator::operate_add(int other){
	int abs_index = this->index;
	int rel_index = 0;
	while(abs_index < ref->fields.size() && rel_index < other){
		if(this->ref->fields.at(index).getType() == iterative)
			rel_index++;
		abs_index++;
	}
	return abs_index;
}
int Term::iterator::operate_sub(int other){
	int abs_index = this->index;
	int rel_index = 0;
	while(abs_index > 0 && rel_index < other){
		if(this->ref->fields.at(index).getType() == iterative)
			rel_index++;
		abs_index--;
	}
	return abs_index;
}
Term::iterator Term::iterator::operator+(int other){
	return Term::iterator{this->ref, operate_add(other), this->iterative};
}

Term::iterator Term::iterator::operator-(int other){
	return Term::iterator{this->ref, operate_sub(other), this->iterative};
}

Term::iterator& Term::iterator::operator+=(int other){
	this->index = operate_add(other);
	return *this;
}

Term::iterator& Term::iterator::operator-=(int other){
	this->index = operate_sub(other);
	return *this;
}

Term::iterator& Term::iterator::operator++(){
	this->index = operate_add(1);
	return *this;
}
Term::iterator& Term::iterator::operator--(){
	this->index = operate_sub(1);
	return *this;
}

Operand& Term::iterator::operator*(){
	return ref->fields.at(index);
}

// Term::iterator& Term::iterator::operator+=(const )