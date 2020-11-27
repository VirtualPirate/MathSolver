#ifndef Operation_Functions_H
#define Operation_Functions_H

#define DEBUG 1
#if DEBUG==1
	#define OPERATION_LOG(TYPE_1, TYPE_2, operation) std::cout << #TYPE_1 << "-" << #TYPE_2 << " arithmetic " << #operation << " is invoked" << std::endl;
#else
	#define OPERATION_LOG(TYPE_1, TYPE_2, operation)
#endif

class Constant;
class Variable;
class Term;

bool is_addable(const Term&, const Term&);
std::string return_type_string(DataType);

//Expression common arithmetic
Operand Operand_to_Expression_add(const Operand&, const Expression&);
inline Operand Operand_to_Expression_sub(const Operand&, const Expression&);
Operand Operand_to_Expression_mul(const Operand&, const Expression&);
inline Operand Operand_to_Expression_div(const Operand&, const Expression&);

Operand Expression_to_Operand_add(const Operand&, const Expression&);
inline Operand Expression_to_Operand_sub(const Operand&, const Expression&);

//Term common arithmetic
Operand Operand_to_Term_add(const Operand&, const Term&);
inline Operand Operand_to_Term_sub(const Operand&, const Term&);
Operand Operand_to_Term_mul(const Operand&, const Term&);
inline Operand Operand_to_Term_div(const Operand&, const Term&);

Operand Term_to_Operand_add(const Term&, const Operand&);
inline Operand Term_to_Operand_sub(const Term&, const Operand&);
Operand Term_to_Operand_mul(const Term&, const Operand&);
inline Operand Term_to_Operand_div(const Term&, const Operand&);

//Operand wide arithmetic
Operand Operand_to_Operand_pow(const Operand&, const Operand&);


#endif