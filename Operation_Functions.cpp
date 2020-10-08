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
	return Constant{first.getValue() + second.getValue()};
}
Constant Constant_Constant_sub(const Constant& first, const Constant& second){
	return Constant{first.getValue() - second.getValue()};
}
Constant Constant_Constant_mul(const Constant& first, const Constant& second){
	return Constant{first.getValue() * second.getValue()};
}
Constant Constant_Constant_div(const Constant& first, const Constant& second){
	return Constant{first.getValue() / second.getValue()};
}
Constant Constant_Constant_pow(const Constant& first, const Constant& second){
	return Constant{pow(first.getValue(), second.getValue())};
}


//Constant to Variable arithmetic operations

Term Constant_Variable_add(const Constant& first, const Variable& second){
	return Term{};
}
Term Constant_Variable_sub(const Constant& first, const Variable& second){
	return Term{};
}
Term Constant_Variable_mul(const Constant& first, const Variable& second){
	return Term{std::vector<Operand>{Operand{first}, Operand{second}}};
}
Term Constant_Variable_div(const Constant& first, const Variable& second){
	return Term{};
}
Term Constant_Variable_pow(const Constant& first, const Variable& second){
	return Term{};
}
