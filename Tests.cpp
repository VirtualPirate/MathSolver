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

	void expression_parsing_test() {
		const char* exp_0 = " -200 +-x^ 2 ( 2.5x + 3y^z)";
		const char* exp_1 = "-+--++-200 *+ x--";
		const char* exp_2 = "(a + b - c) ^ 3";
		const char* exp_3 = "a^2 + b^2 - 2ab";
		const char* exp_4 = "(a/b)^2 + 3/4";

		Parser parser_0{ exp_0 };
		Parser parser_1{ exp_1 };
		Parser parser_2{ exp_2 };
		Parser parser_3{ exp_3 };
		Parser parser_4{ exp_4 };

		parser_0.debug_info();
		parser_0.test_grab_group();
		parser_1.debug_info();
		parser_2.debug_info();
		parser_3.debug_info();
		parser_4.debug_info();
	}
	
	void parsing_group_test() {
		const char* exp_0 = " -200 +-x^ 2 ( 2.5x + 3y^z)";
		const char* exp_1 = "(a + b - c) ^ 3";
		const char* exp_2 = "(a/b)^2 + 3/4";
		const char* exp_3 = "((a+b)c + (c + a)) + h";

		Parser parser_0{ exp_0 };
		Parser parser_1{ exp_1 };
		Parser parser_2{ exp_2 };
		Parser parser_3{ exp_3 };

		auto tokens_0 = parser_0.getTokens();
		auto tokens_1 = parser_1.getTokens();
		auto tokens_2 = parser_2.getTokens();
		auto tokens_3 = parser_3.getTokens();

		auto iter_pair_0 = Parser::grab_group(tokens_0.cbegin(), tokens_0.cend());
		print_constiteratorpair(iter_pair_0);

		auto iter_pair_1 = Parser::grab_group(tokens_1.cbegin(), tokens_1.cend());
		print_constiteratorpair(iter_pair_1);

		auto iter_pair_2 = Parser::grab_group(tokens_2.cbegin(), tokens_2.cend());
		print_constiteratorpair(iter_pair_2);

		auto iter_pair_3 = Parser::grab_group(tokens_3.cbegin(), tokens_3.cend());	
		print_constiteratorpair(iter_pair_3);


	}

	void grab_term_test()
	{

		std::cout << "\n\n[test] grab_term_test started \n\n";
		const char* exp_0 = " -200 +-x^ 2 ( 2.5x + 3y^z)";
		const char* exp_1 = "(a + b - c) ^ 3";
		const char* exp_2 = "(a/b)^2 + 3/4";
		const char* exp_3 = "((a+b)c + (c + a)) + h";

		Parser parser_0{ exp_0 };
		Parser parser_1{ exp_1 };
		Parser parser_2{ exp_2 };
		Parser parser_3{ exp_3 };

		auto tokens_0 = parser_0.getTokens();
		auto tokens_1 = parser_1.getTokens();
		auto tokens_2 = parser_2.getTokens();
		auto tokens_3 = parser_3.getTokens();

		auto iter_pair_0 = Parser::grab_term(tokens_0.cbegin(), tokens_0.cend());
		print_constiteratorpair(iter_pair_0);

		auto iter_pair_1 = Parser::grab_term(tokens_1.cbegin(), tokens_1.cend());
		print_constiteratorpair(iter_pair_1);

		auto iter_pair_2 = Parser::grab_term(tokens_2.cbegin(), tokens_2.cend());
		print_constiteratorpair(iter_pair_2);

		auto iter_pair_3 = Parser::grab_term(tokens_3.cbegin(), tokens_3.cend());
		print_constiteratorpair(iter_pair_3);
	}

	void print_constiteratorpair(TokensConstIteratorPair ref) {
		std::cout << "{ ";
		for (; ref.first < ref.second; ref.first++)
			std::cout << *(ref.first);
		std::cout << "}\n";
	}

	void match_power_test() {
		const char* exp_0 = "2^2^x^2.3";
		Parser parser_0{ exp_0 };
		auto tokens_0 = parser_0.getTokens();
		auto Operand_pair = Parser::match_power(tokens_0.cbegin() + 1, tokens_0.cend());
		Operand operand_0 = Operand_pair.first;
		std::cout << "operand_0 = " << operand_0 << std::endl;

		const char* exp_1 = "x^(2x)^(3x + 1)";
		Parser parser_1{ exp_1 };
		auto tokens_1 = parser_1.getTokens();
		auto Operand_pair_1 = Parser::match_power(tokens_1.cbegin() + 1, tokens_1.cend());
		Operand operand_1 = Operand_pair_1.first;
		std::cout << "operand_1 = " << operand_1 << std::endl;

	}

	void parse_expression_test() {
		const char* exp_0 = "3x + 1";

		Parser parser_0{ exp_0 };
		auto tokens_0 = parser_0.getTokens();
		Operand operand_0 = Parser::Parse_Expression(tokens_0.cbegin(), tokens_0.cend());

		std::cout << "parse_expression_test() started" << std::endl;
		std::cout << "operand_0 = " << operand_0 << std::endl;
	}
}

