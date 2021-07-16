#ifndef Operation_Functions_H
#define Operation_Functions_H

class Constant;
class Variable;
class Term;
class Operand;
class Expression;
class Substitute;

bool is_addable(const Term&, const Term&);
std::string return_type_string(DataType);

std::string match_number(std::string);

//Operand expression_constant_power(const Expression&, int);
Operand expression_constant_power(const Expression&, int);

namespace CONSTANTS{
	extern const Substitutor null_substitutor;
	extern const Operand ONE;
	extern const Operand ZERO;
	extern const Operand MINUS_ONE;
	extern const Operand NULL_OPERAND;
};


#endif