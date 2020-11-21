#ifndef Operation_Functions_H
#define Operation_Functions_H

class Constant;
class Variable;
class Term;

bool is_addable(const Term&, const Term&);
std::string return_type_string(DataType);

#endif