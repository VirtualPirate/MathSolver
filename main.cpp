#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#include "Constant.hpp"
#include "Operand.hpp"
#include "Variable.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "SimpleExpression.hpp"

int main(){
	std::cout << "This is the initial project version" << std::endl;

	//Tests

	Constant num1{10};
	Constant num2{2};
	Constant num3{num1};
	Constant num4{1.5};

	Operand operand_0{10};
	Constant a = operand_0.get<Constant>();
	std::cout << "operand_0.get<Constant>() = " << a << std::endl;


	std::cout << "\n//Constant to Constant operations" << std::endl;
	// std::cout << boolalpha;
	std::cout << num1 << " * " << num2 << " = " << (num1 * num2) << std::endl;
	std::cout << num1 << " / " << num2 << " = " << (num1 / num2) << std::endl;
	std::cout << num1 << " - " << num2 << " = " << (num1 - num2) << std::endl;
	std::cout << num1 << " + " << num2 << " = " << (num1 + num2) << std::endl;
	std::cout << num1 << " ^ " << num2 << " = " << num1.raise_pow(num2) << std::endl;
	return 0;
}