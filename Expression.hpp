#ifndef Expression_H
#define Expression_H

#include "OperandList.hpp"

class Constant;
class Operand;
class Variable;
class OperandList;
class Expression: public OperandList{
	friend std::ostream& operator<<(std::ostream&, const Expression&);
public:
	bool is_negative() const;
	bool negative_power() const;

};

#endif