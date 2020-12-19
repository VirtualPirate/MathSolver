#ifndef Operation_Functions_H
#define Operation_Functions_H

#define DEBUG
#ifdef DEBUG
	#define OPERATION_LOG(TYPE_1, TYPE_2, operation) std::cout << TYPE_1 << "-" << TYPE_2 << " arithmetic " << operation << " is invoked" << std::endl;
	#define OPERANDS(FIRST, SECOND) std::cout << "first = " << FIRST << "\t" << "second = " << SECOND << std::endl;
	#define RESULT(result) std::cout << "result = " << result << std::endl;
#else
	#define OPERATION_LOG(TYPE_1, TYPE_2, operation)
	#define OPERANDS(FIRST, SECOND)
	#define RESULT(result)
#endif

class Constant;
class Variable;
class Term;
class Operand;
class Expression;
class Substitute;

bool is_addable(const Term&, const Term&);
std::string return_type_string(DataType);

std::string match_number(std::string);

namespace CONSTANTS{
	extern const Substitutor null_substitutor;
};


#endif