#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "OperandList.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

std::ostream& operator<<(std::ostream& os, const Term& ref){
	if(!ref.isNull()){
	const std::vector<Operand>& fields = ref.getFields();
	os << *(fields.begin());
	for(auto each=fields.begin()+1; each!=fields.end(); each++)
		if(each->getType() == DataType::Constant)
			os << " * " << *each;
		else
			os << *each;
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
	return false;
}
void Term::simplify() {
	Operand result;
	for(auto i=fields.begin(); i != fields.end(); i++){
		for(auto j=i+1; j != fields.end(); j++){
			result = (*i) * (*j);
			if(result){
				fields.erase(i);
				fields.erase(j-1);
				std::cout << *this << std::endl;
				fields.insert(fields.begin(), result);
				i = fields.begin();
				j = i+1;
			}
		}
	}

}