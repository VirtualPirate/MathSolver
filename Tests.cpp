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

namespace test{
	using namespace std;
    void show_sizes(){
        cout << "sizeof Constant is -> " << sizeof(Constant) << endl;
        cout << "sizeof Variable is -> " << sizeof(Variable) << endl;
        cout << "sizeof OperandList is -> " << sizeof(OperandList) << endl;
        cout << "sizeof Term is -> " << sizeof(Term) << endl;
        cout << "sizeof Expression is -> " << sizeof(Expression) << endl;
        cout << "sizeof Operand is -> " << sizeof(Operand) << endl;
    }
	void add_test(const Operand& first, const Operand& second) {
		cout << first << " + " << second << " = " << (first + second) << endl;
	}
	void sub_test(const Operand& first, const Operand& second) {
		cout << first << " - " << second << " = " << (first - second) << endl;
	}
	void mul_test(const Operand& first, const Operand& second) {
		cout << first << " * " << second << " = " << (first * second) << endl;
	}
	void div_test(const Operand& first, const Operand& second) {
		cout << first << " / " << second << " = " << (first / second) << endl;
	}
	void pow_test(const Operand& first, const Operand& second) {
		cout << first << " ^ " << second << " = " << first.raise_pow(second) << endl;
	}

	void add_test_simplify(const Operand& first, const Operand& second) {
		cout << first << " + " << second << " = " << (first + second).simplify() << endl;
	}
	void sub_test_simplify(const Operand& first, const Operand& second) {
		cout << first << " - " << second << " = " << (first - second).simplify() << endl;
	}
	void mul_test_simplify(const Operand& first, const Operand& second) {
		cout << first << " * " << second << " = " << (first * second).simplify() << endl;
	}
	void div_test_simplify(const Operand& first, const Operand& second) {
		cout << first << " / " << second << " = " << (first / second).simplify() << endl;
	}
	void pow_test_simplify(const Operand& first, const Operand& second) {
		cout << first << " ^ " << second << " = " << (first.raise_pow(second)).simplify() << endl;
	}
	void eq_test(const Operand& first, const Operand& second) {
		cout << first << " == " << second << " = " << (first == second) << endl;
	}
	void neq_test(const Operand& first, const Operand& second) {
		cout << first << " != " << second << " = " << (first != second) << endl;
	}

	void integrated_test(const Operand& first, const Operand& second) {
		add_test(first, second);
		sub_test(first, second);
		mul_test(first, second);
		div_test(first, second);
		pow_test(first, second);
		cout << endl;
	}

	void integrated_test_simplify(const Operand& first, const Operand& second) {
		add_test_simplify(first, second);
		sub_test_simplify(first, second);
		mul_test_simplify(first, second);
		div_test_simplify(first, second);
		pow_test_simplify(first, second);
		cout << endl;
	}
}

