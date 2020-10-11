#ifndef Term_H
#define Term_H

#include <vector>
#include "OperandList.hpp"

class Constant;
class Variable;
class Operand;
class OperandList;

class Term: public OperandList{

	friend std::ostream& operator<<(std::ostream&, const Term&);
};

#endif