#include <cmath>
#include <functional>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "SimpleExpression.hpp"
#include "Operation_Functions.hpp"

// Constant to Constant arithmetic operators
Constant Constant_Constant_add(const Constant& first, const Constant& second){
	return Constant{first.value + second.value};
}
Constant Constant_Constant_sub(const Constant& first, const Constant& second){
	return Constant{first.value - second.value};
}
Constant Constant_Constant_mul(const Constant& first, const Constant& second){
	return Constant{first.value * second.value};
}
Constant Constant_Constant_div(const Constant& first, const Constant& second){
	return Constant{first.value / second.value};
}
Constant Constant_Constant_pow(const Constant& first, const Constant& second){
	return Constant{pow(first.value, second.value)};
}