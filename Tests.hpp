#ifndef Tests_H
#define Tests_H

class Operand;
class Constant;
class Variable;
class Term;
class Expression;

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

#define CONSTANT_LOGS 0
#if CONSTANT_LOGS == 1
    #define CONSTANT_LOG_CONSTRUCT() LOG_CONSTRUCT()
    #define CONSTANT_LOG_DESTRUCT() LOG_DESTRUCT()
#else
    #define CONSTANT_LOG_CONSTRUCT()
    #define CONSTANT_LOG_DESTRUCT()
#endif

#define VARIABLE_LOGS 0
#if VARIABLE_LOGS == 1
    #define VARIABLE_LOG_CONSTRUCT() LOG_CONSTRUCT()
    #define VARIABLE_LOG_DESTRUCT() LOG_DESTRUCT()
#else
#define VARIABLE_LOG_CONSTRUCT()
#define VARIABLE_LOG_DESTRUCT()
#endif

#define TERM_LOGS 0
#if TERM_LOGS == 1
    #define TERM_LOG_CONSTRUCT() LOG_CONSTRUCT()
    #define TERM_LOG_DESTRUCT() LOG_DESTRUCT()
#else
    #define TERM_LOG_CONSTRUCT()
    #define TERM_LOG_DESTRUCT()
#endif

#define EXPRESSION_LOGS 0
#if EXPRESSION_LOGS == 1
    #define EXPRESSION_LOG_CONSTRUCT() LOG_CONSTRUCT()
    #define EXPRESSION_LOG_DESTRUCT() LOG_DESTRUCT()
#else
    #define EXPRESSION_LOG_CONSTRUCT()
    #define EXPRESSION_LOG_DESTRUCT()
#endif

#define OPERAND_LOGS 0
#if OPERAND_LOGS == 1
    #define OPERAND_LOG_CONSTRUCT() LOG_CONSTRUCT()
    #define OPERAND_LOG_DESTRUCT() LOG_DESTRUCT()
#else
    #define OPERAND_LOG_CONSTRUCT()
    #define OPERAND_LOG_DESTRUCT()
#endif


namespace test{
    void show_sizes();
}

#endif