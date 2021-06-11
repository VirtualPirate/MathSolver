#ifndef Operation_Functions_H
#define Operation_Functions_H

#define DEBUG
#ifdef DEBUG
	#define OPERATION_LOG(TYPE_1, TYPE_2, operation) std::cout << TYPE_1 << "-" << TYPE_2 << " arithmetic " << operation << " is invoked" << std::endl;
	#define OPERANDS(FIRST, SECOND) std::cout << "first = " << FIRST << "\t" << "second = " << SECOND << std::endl;
	#define RESULT(result) std::cout << "result = " << result << std::endl;
	#define LOG_CONSTRUCTOR(CONSTRUCTOR_TEXT) std::cout << "[Constructor]:" << CONSTRUCTOR_TEXT << std::endl;
	#define LOG_DESTRUCTOR(DESTRUCTOR_TEXT)	std::cout << "[Destructor]:" << DESTRUCTOR_TEXT << std::endl;

	#define LOG_CONSTRUCT() LOG_CONSTRUCTOR(__FUNCTION__);
	#define LOG_DESTRUCT() LOG_DESTRUCTOR(__FUNCTION__);
#else
	#define OPERATION_LOG(TYPE_1, TYPE_2, operation)
	#define OPERANDS(FIRST, SECOND)
	#define RESULT(result)
	#define LOG_CONSTRUCTOR(CONSTRUCTOR_TEXT)
	#define LOG_DESTRUCTOR(DESTRUCTOR_TEXT)

	#define LOG_CONSTRUCT(CONSTRUCTOR_SIGNATURE)
	#define LOG_DESTRUCT()
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
	extern const Operand ONE;
	extern const Operand ZERO;
	extern const Operand NULL_OPERAND;
};


#endif