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

void add_test_simplify(const Operand& first, const Operand& second){
	cout << first << " + " << second << " = " << (first + second).simplify() << endl;
}
void sub_test_simplify(const Operand& first, const Operand& second){
	cout << first << " - " << second << " = " << (first - second).simplify() << endl;
}
void mul_test_simplify(const Operand& first, const Operand& second){
	cout << first << " * " << second << " = " << (first * second).simplify() << endl;
}
void div_test_simplify(const Operand& first, const Operand& second){
	cout << first << " / " << second << " = " << (first / second).simplify() << endl;
}
void pow_test_simplify(const Operand& first, const Operand& second){
	cout << first << " ^ " << second << " = " << (first.raise_pow(second)).simplify() << endl;
}
void eq_test(const Operand& first, const Operand& second){
	cout << first << " == " << second << " = " << (first == second) << endl;
}
void neq_test(const Operand& first, const Operand& second){
	cout << first << " != " << second << " = " << (first != second) << endl;
}

void integrated_test(const Operand& first, const Operand& second){
	add_test(first, second);
	sub_test(first, second);
	mul_test(first, second);
	div_test(first, second);
	pow_test(first, second);
	cout << endl;
}

void integrated_test_simplify(const Operand& first, const Operand& second){
	add_test_simplify(first, second);
	sub_test_simplify(first, second);
	mul_test_simplify(first, second);
	div_test_simplify(first, second);
	pow_test_simplify(first, second);
	cout << endl;
}

int main(){

	Constant num1{10};
	Constant num2{2};
	Constant num3{num1};
	Constant num4{1.5};
	Constant num5{-1};
	Constant num6{10, Variable{'x'}};

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

	Term term_6{Constant{1}};
	term_6.insert(var_0);

	Term term_7{OperandList{Constant{9}}};

	Expression exp_0{var_0};
	exp_0.insert(num1);
	exp_0.insert(var_3);
	return 0;
}