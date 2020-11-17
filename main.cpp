#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#include "Operand.hpp"
#include "Constant.hpp"
#include "Variable.hpp"
#include "OperandList.hpp"
#include "Term.hpp"
#include "Expression.hpp"
#include "Operation_Functions.hpp"

using namespace std;

void add_test(const Operand& first, const Operand& second){
	cout << first << " + " << second << " = " << (first + second) << endl;
}
void sub_test(const Operand& first, const Operand& second){
	cout << first << " - " << second << " = " << (first - second) << endl;
}
void mul_test(const Operand& first, const Operand& second){
	cout << first << " * " << second << " = " << (first * second) << endl;
}
void div_test(const Operand& first, const Operand& second){
	cout << first << " / " << second << " = " << (first / second) << endl;
}
void pow_test(const Operand& first, const Operand& second){
	cout << first << " ^ " << second << " = " << first.raise_pow(second) << endl;
}

void integrated_test(const Operand& first, const Operand& second){
	add_test(first, second);
	sub_test(first, second);
	mul_test(first, second);
	div_test(first, second);
	pow_test(first, second);
	cout << endl;
}

int main(){
	std::cout << "This is the initial project version" << std::endl;

	//Tests

	Constant num1{10};
	Constant num2{2};
	Constant num3{num1};
	Constant num4{1.5};
	Constant num5{-1};

	Variable var_0{'x'};
	Variable var_1{'y'};
	Variable var_2{'x', -2};
	Variable var_3{'y', 3};

	Term term_0{Variable{'a'}};
	term_0.setNull(false);
	term_0.insert(num1);
	term_0.insert(var_0);
	term_0.insert(var_1);

	term_0.insert(num2);
	term_0.insert(var_2);

	term_0.insert(num3);
	term_0.insert(var_3);

	Term term_1{num1};
	Term term_2{var_1};
	Term term_3{var_2};

	Term term_4{num2};
	term_4.insert(var_0);
	term_4.insert(var_1);

	Term term_5{num1};
	term_5.insert(var_0);
	term_5.insert(var_1);

	Expression exp_0{var_0};
	exp_0.insert(num1);
	exp_0.insert(var_3);

	//Displaying all the operands

		cout << "num1 = " << num1 << endl;
		cout << "num2 = " << num2 << endl;
		cout << "num3 = " << num3 << endl;
		cout << "num4 = " << num4 << endl;
		cout << endl;
		cout << "\n//Constant to Constant operations" << endl;
		// std::cout << boolalpha;
		cout << num1 << " * " << num5 << " = " << (num1 * num5) << endl;
		cout << num1 << " / " << num2 << " = " << (num1 / num2) << endl;
		cout << num1 << " - " << num2 << " = " << (num1 - num2) << endl;
		cout << num1 << " + " << num2 << " = " << (num1 + num2) << endl;
		cout << num1 << " ^ " << num5 << " = " << num1.raise_pow(num5) << endl;
		cout << endl;
		cout << "Constant to Variable arithmetic -" << endl << endl;
		cout << num1 << " + " << var_3 << " = " << (num1 + var_3) << endl;
		cout << num1 << " - " << var_3 << " = " << (num1 - var_3) << endl;
		cout << num1 << " * " << var_3 << " = " << (num1 * var_3) << endl;
		cout << num1 << " / " << var_3 << " = " << (num1 / var_3) << endl;
		cout << num1 << " ^ " << var_3 << " = " << num1.raise_pow(var_3) << endl;
		cout << endl;
		cout << "Constant to Term arithmetic - " << endl << endl;
		cout << num1 << " + " << term_4 << " = " << (num1 + term_4) << endl;
		cout << num1 << " - " << term_4 << " = " << (num1 - term_4) << endl;
		cout << num1 << " * " << term_4 << " = " << (num1 * term_4) << endl;
		cout << num1 << " / " << term_4 << " = " << (num1 / term_4) << endl;
		cout << num1 << " ^ " << term_4 << " = " << (num1.raise_pow(term_4) ) << endl;
 		cout << "Constant to Expression arithmetic - " << endl << endl;
 		cout << num1 << " + " << exp_0 << " = " << (num1 + exp_0) << endl;
 		// cout << num1 << " - " << term_4 << " = " << (num1 - exp_0) << endl;
		cout << num1 << " * " << exp_0 << " = " << (num1 * exp_0) << endl;
		cout << num1 << " / " << exp_0 << " = " << (num1 / exp_0) << endl;
		cout << num1 << " ^ " << exp_0 << " = " << num1.raise_pow(exp_0) << endl;
		cout << endl;
		cout << "Variable to Constant arithemtic - " << endl << endl;
		cout << var_3 << " + " << num2 << " = " << (var_3 + num2) << endl;
		cout << var_3 << " - " << num2 << " = " << (var_3 - num2) << endl;
		cout << var_3 << " * " << num2 << " = " << (var_3 * num2) << endl;
		cout << var_3 << " / " << num2 << " = " << (var_3 / num2) << endl;
		cout << var_3 << " ^ " << num2 << " = " << (var_3.raise_pow(num2)) << endl;
		cout << endl;
		cout << "Variable to Variable arithemtic - " << endl << endl;
		integrated_test(var_0, var_1);
		integrated_test(var_1, var_3);
		cout << "Variable to Term arithmetic - " << endl << endl;
		integrated_test(var_0, term_4);
		integrated_test(var_1, term_0);
		cout << "is_constvar(term_4, term_5)  = " << is_constvar(term_4, term_5) << endl;
		// cout << "Constant to Term arithmetic - " << endl;
		// cout << num1 << " + " << term_1 << " = " << (num1 + term_1) << endl;
		// cout << num1 << " + " << term_0 << " = " << (num1 + term_0) << endl;
		// cout << num1 << " - " << term_1 << " = " << (num1 - term_1) << endl;
		// cout << num1 << " - " << term_0 << " = " << (num1 - term_0) << endl;
		// cout << num1 << " * " << term_0 << " = " << (num1 * term_0) << endl;

		// cout << endl;

		cout << "var_0 = " << var_0 << endl;
		cout << "var_1 = " << var_1 << endl;
		cout << "var_2 = " << var_2 << endl;
		cout << "var_3 = " << var_3 << endl;
		cout << endl;


		cout << "term_0 = " << term_0 << endl;
		cout << "term_1 = " << term_1 << endl;
		cout << "term_2 = " << term_2 << endl;
		cout << "term_3 = " << term_3 << endl;

		cout << "term_0.count(DataType::Variable) = " << term_0.count(DataType::Variable) << endl;

		cout << endl;
		cout << "term_0.is_Constant() = " << term_0.is_Constant() << endl;
		cout << "term_1.is_Constant() = " << term_1.is_Constant() << endl;
		cout << "term_2.is_Constant() = " << term_2.is_Constant() << endl;
		cout << "term_3.is_Constant() = " << term_3.is_Constant() << endl;
		cout << "term_0.is_Variable() = " << term_0.is_Variable() << endl;
		cout << "term_1.is_Variable() = " << term_1.is_Variable() << endl;
		cout << "term_2.is_Variable() = " << term_2.is_Variable() << endl;
		cout << "term_3.is_Variable() = " << term_3.is_Variable() << endl;

		cout << endl;


	/*
	std::cout << "Testing Term::operator<< " << std::endl;
	// std::cout << term_0 << std::endl;
	// std::cout << term_0.getFields().at(2) << std::endl;
	std::cout << term_0 << std::endl;
	term_0.simplify_();
	std::cout << term_0 << std::endl;
	std::cout << std::endl << std::endl;

	Term::iterator iter_begin = term_0.begin(DataType::Variable);
	Term::iterator iter_end = term_0.end(DataType::Variable);

	std::cout << "TEsting TErm::iterator" << std::endl;
	for(auto each=term_0.begin(DataType::Constant); each!=term_0.end(DataType::Constant); each++)
		std::cout << *each << std::endl;


	Expression exp_0{{num1, var_0, var_1, term_0}};
	std::cout << "Testing Expression::operator<<" << std::endl;
	std::cout << exp_0 << std::endl;
	Operand operand_0{10};
	std::cout << "operand_0.is_negative() = " << operand_0.is_negative() << std::endl; 
	Operand operand_1{term_0};
	Constant a = operand_0.get<Constant>();
	std::cout << std::endl << std::endl;
	std::cout << "Testing Operand::operator<<" << std::endl;
	std::cout << operand_0 << "\n\n";
	std::cout << operand_1.power_print() << "\n\n";
	std::cout << "operand_0.get<Constant>() = " << a << std::endl;
`*/

	// std::cout << "\n//Constant to Constant operations" << std::endl;
	// // std::cout << boolalpha;
	// std::cout << num1 << " * " << num2 << " = " << (num1 * num2) << std::endl;
	// std::cout << num1 << " / " << num2 << " = " << (num1 / num2) << std::endl;
	// std::cout << num1 << " - " << num2 << " = " << (num1 - num2) << std::endl;
	// std::cout << num1 << " + " << num2 << " = " << (num1 + num2) << std::endl;
	// std::cout << num1 << " ^ " << num2 << " = " << num1.raise_pow(num2) << std::endl;
	/*
	New new_1{Constant{1}};
	new_1.setNull(false);
	new_1.insert(num1);
	new_1.insert(var_0);
	new_1.insert(var_1);

	new_1.insert(num2);
	new_1.insert(var_2);

	new_1.insert(num3);
	new_1.insert(var_3);

	// New::iterator iter_begin_ = term_0.begin(DataType::Variable);
	// New::iterator iter_end_ = term_0.end(DataType::Variable);

	std::cout << "TEsting New::iterator" << std::endl;
	for(auto each=new_1.begin(DataType::Variable); each!=new_1.end(DataType::Variable); each++)
		std::cout << *each << std::endl;
	std::cout << "new_1 = " << new_1 << std::endl;
	//*/
	return 0;
}