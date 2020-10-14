#include <vector>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "OperandList.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

bool Expression::is_negative() const {
	return false;
}
bool Expression::negative_power() const {
	return power.is_negative();
}