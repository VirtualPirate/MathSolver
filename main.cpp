#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#include "Substitutor.hpp"
#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "OperandList.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"
#include "Parser.hpp"

#include "Tests.hpp"

using namespace std;

int main() {
	std::vector<Substitutor> sub;
	sub.push_back(Substitutor{ Variable{'x'}, (double)10 });

	//test::show_sizes();

	Constant num1{ 10 };
	Constant num2{ 2, (double)4 };
	Constant num3{ num1 };
	Constant num4{ 1.5 };
	Constant num5{ -1 };
	Constant num6{ 10, Variable{'x'} };
	Constant num7{ 5 };
	//Constant num8{ num1 + num7 };

	cout << "num8 = " << (num1 + num7) << endl;

	Variable var_0{ 'x' };
	Variable var_1{ 'y' };
	Variable var_2{ 'x', -2 };
	Variable var_3{ 'y', 3 };
	Variable var_4 = 'a';

	
	test::add_test(num1, num4);
	test::sub_test(num1, num2.simplify());
	test::mul_test(num1, num1);
	test::div_test(num1, num7);
	test::pow_test(num1, num2);

	Term term_0{ Variable{'a'} };
	term_0.setNull(false);
	term_0.insert(num1);
	term_0.insert(var_0);
	term_0.insert(var_1);

	term_0.insert(num2);
	term_0.insert(var_2);

	term_0.insert(num3);
	term_0.insert(var_3);

	Term term_1{ num1 };
	Term term_2{ var_1 };
	Term term_3{ var_2 };

	Term term_4{ num2 };
	term_4.insert(var_0);
	term_4.insert(var_1);

	Term term_5{ num1 };
	term_5.insert(var_0);
	term_5.insert(var_1);

	Term term_6{ Constant{1} };
	term_6.insert(var_0);

	Term term_7{ OperandList{Constant{9}} };

	Expression exp_0{ var_0 };
	exp_0.insert(num1);
	exp_0.insert(var_3);

	Operand operand_0{ 'a' };
	Operand operand_1{ 'x' };

	Substitutor_List var_values = { Substitutor{var_0, num1}, Substitutor{var_1, num2}, Substitutor{var_1, num5} };
	cout << "var_values.size() = " << var_values.size() << endl;

	cout << "term_0 = " << term_0 << endl;
	// cout << "term_0 = " << Term{term_0.substitute(sub)} << endl;
	cout << match_number("-200x^2") << endl;

	cout << "num6.getBase() = " << (Operand{ num6 }).getBase() << endl;

	//test::expression_parsing_test();
	//test::parsing_group_test();
	//test::grab_term_test();

	//test::match_power_test();
	test::parse_expression_test();
	test::constant_simplify_tests();
	test::variable_simplify_test();
	//cin.get();
	return 0;
}