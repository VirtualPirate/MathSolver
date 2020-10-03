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