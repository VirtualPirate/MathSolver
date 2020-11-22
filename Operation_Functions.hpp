#ifndef Operation_Functions_H
#define Operation_Functions_H

class Constant;
class Variable;
class Term;

bool is_addable(const Term&, const Term&);
std::string return_type_string(DataType);

//Common arithmetic operaions
Operand Operand_to_Expression_add(const Operand&, const Expression&);
Operand Operand_to_Expression_sub(const Operand&, const Expression&);
Operand Operand_to_Expression_mul(const Operand&, const Expression&);
Operand Operand_to_Expression_div(const Operand&, const Expression&);

Operand Expression_to_Operand_add(const Operand&, const Expression&);
Operand Expression_to_Operand_sub(const Operand&, const Expression&);

#endif