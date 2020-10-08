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

	Variable var_0{'x'};
	Variable var_1{'y'};
	Variable var_2{'x', 2};
	Variable var_3{'y', 3};

	Term term_0{};
	term_0.setNull(false);
	term_0.insert(num1);
	term_0.insert(var_0);
	term_0.insert(var_1);

	term_0.insert(num2);
	term_0.insert(var_2);

	term_0.insert(num3);
	term_0.insert(var_3);

	std::cout << "Testing Term::operator<< " << std::endl;
	// std::cout << term_0 << std::endl;
	// std::cout << term_0.getFields().at(2) << std::endl;
	std::cout << term_0 << std::endl;

	Term::iterator iter_begin = term_0.begin(DataType::Variable);
	Term::iterator iter_end = term_0.end(DataType::Variable);

	std::cout << "TEsting TErm::iterator" << std::endl;
	for(auto each=term_0.begin(DataType::Variable); each!=term_0.end(DataType::Variable); each++)
		std::cout << *each << std::endl;


	Operand operand_0{10};
	Constant a = operand_0.get<Constant>();
	std::cout << std::endl << std::endl;
	std::cout << "Testing Operand::operator<<" << std::endl;
	std::cout << operand_0 << "\n\n";
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