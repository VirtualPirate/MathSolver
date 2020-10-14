#ifndef Expression_H
#define Expression_H

#include "OperandList.hpp"

class Constant;
class Operand;
class Variable;
class OperandList;
class Expression: public OperandList{
	bool is_negative() const;
};

#endif