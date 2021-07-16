#include <vector>
#include <iostream>
#include <sstream>

#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "OperandList.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"
#include "Substitutor.hpp"

#include "Tests.hpp"


Expression::Expression(const Expression& lvalue) : OperandList(lvalue), is_subexpression{ lvalue.is_subexpression }{}
Expression& Expression::operator=(const Expression& lvalue) {
	OperandList::operator=(lvalue);
	is_subexpression = lvalue.is_subexpression;
	return *this;
}
Expression::Expression(Expression&& rvalue) : OperandList(std::move(rvalue)), is_subexpression{ rvalue.is_subexpression }{}
Expression& Expression::operator=(Expression&& rvalue) {
	OperandList::operator=(std::move(rvalue));
	is_subexpression = rvalue.is_subexpression;
	return *this;
}

Expression::Expression(const Operand& ref) {
	if(ref.is_expression())
		*this = ref.get<Expression>();
	else
		OperandList(ref);
}

Expression& Expression::operator=(const Operand& ref) {
	if (ref.is_expression())
		*this = ref.get<Expression>();
	else
		OperandList::operator=(ref);

	return *this;
}

std::ostream& operator<<(std::ostream& os, const Expression& ref){
	if(!ref.isNull()){
		bool brace = ref.isSubexpression();
		if(ref.getPower() != Operand{(double)1})
			brace = true;
		if(brace)
			os << '(';
		const std::vector<Operand>& fields = ref.getFields();
		os << *(fields.begin());
		for(auto each=fields.begin()+1; each!=fields.end(); each++){
			if(!each->is_negative())
				os << " + " << *each;
			else
				os << ' ' << *each;
		}
		if (brace && ref.getPower() != CONSTANTS::ONE)
			os << ")^" << ref.getPower().power_print();
		else if (brace)
			os << ')';
	}
	else{
		os << "null_expression{}";
	}
	return os;
}

std::string Expression::power_print() const{
	std::ostringstream stream;
	stream << *this;
	return stream.str();
}
bool Expression::is_negative() const {
	return false;
}
bool Expression::negative_power() const {
	return power.is_negative();
}

void Expression::simplify_each() {
	for (Operand& each : fields)
		each = std::move(each.simplify());
}

void Expression::simplify_internal_expressions() {
	Expression simplified_expression;
	for (size_t each = 0; each < fields.size();) {
		if (fields.at(each).is_expression() && fields.at(each).getPower() == CONSTANTS::ONE) {
			simplified_expression = std::move(fields.at(each).simplify());
			fields.erase(fields.begin() + each);;
			fields.insert(fields.begin() + each, simplified_expression.fields.begin(), simplified_expression.fields.end());
			each += simplified_expression.fields.size();
		}
		else
			each++;
	}
}

void Expression::remove_zeroes() {
	for (auto each = fields.begin(); each != fields.end(); ) {
		if (each->is_constant() && *each == CONSTANTS::ZERO)
			fields.erase(each);
		else
			each++;
	}
}

Operand Expression::simplify() const {
	//return *this;

	Expression result{ *this };
	result.simplify_each();
	result.simplify_internal_expressions();

	//std::cout << "*this expression = " << *this << std::endl;
	auto upper_iter = result.fields.begin();
	auto lower_iter = result.fields.begin() + 1;

	Operand each_operand;
	while (upper_iter != result.fields.end()-1) {
		each_operand = *upper_iter + *lower_iter;
		//std::cout << "upper_iter = " << *upper_iter << std::endl;
		//std::cout << "lower_iter = " << *lower_iter << std::endl;
		//std::cout << "result = " << result << std::endl;
		if (each_operand)
		{
			*lower_iter = std::move(each_operand.simplify());
			result.fields.erase(upper_iter);
			upper_iter = result.fields.begin();
			lower_iter = result.fields.begin() + 1;
			continue;
		}
		else if (++lower_iter == result.fields.end()) {
			upper_iter++;
			lower_iter = upper_iter + 1;
		}
	}

	result.remove_zeroes();

	if (result.power.is_constant()) {
		double power_value = result.power.get<Constant>().value;
		if (power_value == (int)power_value) {// if power_value does not have a decimal part
			result.power = CONSTANTS::ONE;
			result = expression_constant_power(result, (int)power_value);
		}
	}

	return result;

}

Expression Expression::getBase() const{
	return Expression{fields};
}
void Expression::setSubexpression(bool is_sub) { is_subexpression = is_sub; }
bool Expression::isSubexpression() const { return is_subexpression; }
//Operand to double arithmetic operators
Operand Expression::operator+(const double& other) const {return *this + Operand{other};}
Operand Expression::operator-(const double& other) const {return *this - Operand{other};}
Operand Expression::operator*(const double& other) const {return *this * Operand{other};}
Operand Expression::operator/(const double& other) const {return *this / Operand{other};}
Operand Expression::raise_pow(const double& other) const {return this->raise_pow(Operand{other});}

//Expression to Operand arithmetic operators
Operand Expression::operator+(const Operand& other) const {return Operand{*this} + other;}
Operand Expression::operator-(const Operand& other) const {return Operand{*this} - other;}
Operand Expression::operator*(const Operand& other) const {return Operand{*this} * other;}
Operand Expression::operator/(const Operand& other) const {return Operand{*this} / other;}
Operand Expression::raise_pow(const Operand& other) const {return Operand{*this}.raise_pow(other);}

Operand Expression::Operand_Expression_mul(const Operand& first, const Expression& second) {
	if (second.power == CONSTANTS::ONE) {
		std::vector<Operand> result_fields;
		result_fields.reserve(second.fields.size());
		for (const Operand& each_operand : second.fields)
			result_fields.push_back(first * each_operand);
		return Expression{ result_fields };
	}
	else
		return Term{ first, second };
}