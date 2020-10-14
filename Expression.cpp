#include <vector>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "OperandList.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

std::ostream& operator<<(std::ostream& os, const Expression& ref){
	if(!ref.isNull()){
	const std::vector<Operand>& fields = ref.getFields();
	os << *(fields.begin());
	for(auto each=fields.begin()+1; each!=fields.end(); each++)
		if(!each->is_negative())
			os << " + " << *each;
		else
			os << *each;
	}
	else{
		os << "null_expression{}";
	}
	return os;
}

bool Expression::is_negative() const {
	return false;
}
bool Expression::negative_power() const {
	return power.is_negative();
}