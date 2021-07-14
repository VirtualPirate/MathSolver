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

Timer::Timer() {
	start = std::chrono::high_resolution_clock::now();
}

Timer::~Timer() {
	end = std::chrono::high_resolution_clock::now();
	duration = end - start;
	std::cout << "Timer took " << duration.count() << " s" << std::endl;
}


namespace test{
	using namespace std;

	Constant num1{ 10 };
	Constant num2{ 2, (double)4 };
	Constant num3{ num1 };
	Constant num4{ 1.5 };
	Constant num5{ -1 };
	Constant num6{ 10, Variable{'x'} };
	Constant num7{ 5 };
	Constant num8{ (double)10, (double)5 };

	Variable var_0{ 'x' };
	Variable var_1{ 'y' };
	Variable var_2{ 'x', -2 };
	Variable var_3{ 'y', 3 };
	Variable var_4 = 'a';

	Term term0{ {num1, var_0} }; // 10x
	Term term1{ {num2, var_3} };  // 2^4y^3
	Term term2{ {num7, var_0}, (double)2 }; // (5x)^2
	Term term3{ {num7, var_0} }; // 5x
	Term term4{ {num1, var_0, var_1, var_3, var_2} }; // 10xyy^3x^-2
	Term term5{ {num7, var_1, var_0, var_2, var_3} }; // 5xyy^3x^-2
	Term term6{ {var_0, var_1} }; // xy
	Term term7{ {num1, var_0, num2, var_1} }; // 10x * 2^4x
	Term term8{ {num1, num6, num7, var_2, var_3} }; // 10 * 10^x * 5x^-2y^3
	Term term9{ {num1, var_0, var_0, var_2} }; // 10xxx^-2
	Term term10{ {num1, var_0, var_0, var_2}, num7 }; // (10xxx^-2)^5
	Term term11{ {num1, term2} };

	Expression exp0(Parser::Parse_Expression("1 + 2x -y"));
	Expression exp1(Parser::Parse_Expression("x + 2xy + x^2"));
	Expression exp2(Parser::Parse_Expression("a + b"));
	Expression exp3(Parser::Parse_Expression("2 + 3^4"));
	Expression exp4(Parser::Parse_Expression("x + x + y + y + a + b + a"));
	Expression exp5(Parser::Parse_Expression("2x + y + x"));
	Expression exp6(Parser::Parse_Expression("2x + (5y + 6y + (2 + 1) + 3) + 98"));

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
		/*
		const char* exp_0 = "3x + 1";

		Parser parser_0{ exp_0 };
		auto tokens_0 = parser_0.getTokens();
		Operand operand_0 = Parser::Parse_Expression(tokens_0.cbegin(), tokens_0.cend());

		std::cout << "parse_expression_test() started" << std::endl;
		std::cout << "operand_0 = " << operand_0 << std::endl;
		*/

		std::cout << "\n\n";
		Parser parser_1{ "-200 +-x^ 2 ( 2.5x + 3y^z) ^ (2xy) ^ (xyz)" };
		parser_1.debug_info();
		auto tokens_1 = parser_1.getTokens();
		Operand operand_1 = Parser::Parse_Expression(tokens_1.cbegin(), tokens_1.cend());
		std::cout << "operand_1 = " << operand_1 << std::endl;

		Operand operand_2 = Parser::Parse_Expression("((a+b)c + (c + a)) + h");
		std::cout << "operand_2 = " << operand_2 << std::endl;

		Operand operand_3 = Parser::Parse_Expression("(a/b)^2 + 3/4");
		std::cout << "operand_3 = " << operand_3 << std::endl;

		Operand operand_4 = Parser::Parse_Expression("(a + b - c) ^ 3");
		std::cout << "operand_4 = " << operand_4 << std::endl;

		Operand operand_5 = Parser::Parse_Expression("1 / (2 + 1)");
		std::cout << "oeprand_5 = " << operand_5 << std::endl;

		Operand oeprand_6 = Parser::Parse_Expression("1 / (x  +y) / (200 + 2xy)");
		std::cout << "operand_6 = " << oeprand_6 << std::endl;
	}

	void constant_simplify_tests() {
		Constant con_0{ (double)2, Constant{(double)2, (double)2} };
		Constant con_1{ 2, con_0 };
		Operand operand{ con_1.simplify() };
		if (operand.is_constant())
			std::cout << "The operand is constant" << std::endl;
		std::cout << "operand = " << operand << std::endl;
	}

	void variable_simplify_test() {
		Constant constant{ (double)2, Constant{(double)2, Variable{'x', Constant{(double)2, Constant{(double)3, (double)2}}}} };
		std::cout << "constant before simplification = " << constant << std::endl;
		std::cout << "constant after simplification = " << constant.simplify() << std::endl;
	}

	void term_simplify_test() {
		std::cout << "[Term simplification tests]\n\n";
		std::cout << "term before simplification (term2) = " << term2 << std::endl;
		std::cout << "term after simplification (term2) = " << term2.simplify() << std::endl;
		std::cout << "term before simplification (term7) = " << term7 << std::endl;
		std::cout << "term after simplification (term7) = " << term7.simplify() << std::endl;
		std::cout << "term before simplification (term8) = " << term8 << std::endl;
		std::cout << "term after simplification (term8) = " << term8.simplify() << std::endl;
		std::cout << "term before simplification (term9) = " << term9 << std::endl;
		std::cout << "term after simplification (term9) = " << term9.simplify() << std::endl;
		std::cout << "term before simplification (term10) = " << term10 << std::endl;
		std::cout << "term after simplification (term10) = " << term10.simplify() << std::endl;
		std::cout << "term before simplification (term11) = " << term11 << std::endl;
		std::cout << "term after simplification (term11) = " << term11.simplify() << std::endl;
		std::cout << "\n\n";

	}

	void expression_simplify_test() {
		std::cout << "[Expression simplification tests]\n\n";
		std::cout << "expression before simplification (exp3)= " << exp3 << std::endl;
		std::cout << "expression after simplification (exp3) = " << exp3.simplify() << std::endl;
		std::cout << "expression before simplification (exp4)= " << exp4 << std::endl;
		std::cout << "expression after simplification (exp4) = " << exp4.simplify() << std::endl;
		std::cout << "expression before simplification (exp5)= " << exp5 << std::endl;
		std::cout << "expression after simplification (exp5) = " << exp5.simplify() << std::endl;
		std::cout << "expression before simplification (exp6)= " << exp6 << std::endl;
		std::cout << "expression after simplification (exp6) = " << exp6.simplify() << std::endl;

		std::cout << "\n\n";

	}

	void constant_constant_test() {
		std::cout << "[Constant to Constant] arithmetic tests\n\n";
		test::add_test(num1, num4);
		test::sub_test(num1, num2.simplify());
		test::mul_test(num1, num1);
		test::mul_test(num1, num8);
		test::div_test(num1, num7);
		test::pow_test(num1, num2);
		std::cout << "\n\n";
	}

	void constant_variable_test() {
		std::cout << "[Constant to Variable] arithmetic tests\n\n";
		test::mul_test(num2, var_3);
		test::div_test(num2, var_3);
		test::pow_test(num2, var_0);
		std::cout << "\n\n";
	}
	void variable_constant_test() {
		std::cout << "[Variable to Constant] arithmetic tests\n\n";
		test::mul_test(var_2, num2);
		test::div_test(var_3, num6);
		test::pow_test(var_2, num5);
		std::cout << "\n\n";

	}

	void variable_variable_test() {
		std::cout << "[Variable to Variable] arithmetic testsn\n\n";
		test::add_test(var_2, var_2);
		test::add_test(var_3, var_3);
		test::add_test(var_4, var_4);

		test::sub_test(var_3, var_3);
		test::sub_test(var_4, var_4);

		test::mul_test(var_0, var_2);
		test::mul_test(var_1, var_3);
		test::mul_test(var_2, var_3);

		test::div_test(var_0, var_1);
		test::div_test(var_0, var_2);
		std::cout << "\n\n";
	}

	void constant_term_test() {
		std::cout << "[Constant to Term] arithmetic tests\n\n";
		test::mul_test(num1, term0);
		test::mul_test(num2, term2);
		test::div_test(num7, term2);
		test::pow_test(num1, term0);
		std::cout << "\n\n";
	}

	void variable_term_test() {
		std::cout << "[Variable to Term] arithmetic tests\n\n";
		test::mul_test(var_0, term0);
		test::mul_test(var_3, term2);
		test::div_test(var_0, term0);
		test::pow_test(var_1, term0);
		std::cout << "\n\n";

	}

	void term_constant_test() {
		std::cout << "[Term to Constant] arithmetic tests\n\n";

		std::cout << "\n\n";
	}

	void term_variable_test() {
		std::cout << "[Term to Variable] arithmetic tests\n\n";

		std::cout << "\n\n";
	}
	
	void term_term_test() {
		std::cout << "[Term to Term] arithmetic tests\n\n";

		test::add_test(term0, term3);
		test::add_test(term4, term5);
		test::add_test(term6, term6);
		test::sub_test(term4, term5);

		test::mul_test(term0, term3);
		test::mul_test(term0, term6);

		std::cout << "\n\n";

	}

	void constant_expression_test() {
		std::cout << "[Constant to Expression] arithmetic tests\n\n";
		exp0.setSubexpression(true);
		exp1.setSubexpression(true);

		test::mul_test(num1, exp0);
		test::mul_test(num2, exp0);
		test::mul_test(num3, exp0);
		test::mul_test(num4, exp0);
		test::mul_test(num5, exp0);

		test::mul_test(num1, exp1);
		test::mul_test(num2, exp1);
		test::mul_test(num3, exp1);
		test::mul_test(num4, exp1);
		test::mul_test(num5, exp1);

		std::cout << "\n\n";
	}
	void variable_expression_test() {
		std::cout << "[Variable to Expression] arithemtic tests\n\n";

		test::mul_test(var_0, exp0);
		test::mul_test(var_1, exp0);
		test::mul_test(var_2, exp0);
		test::mul_test(var_3, exp0);
		test::mul_test(var_4, exp0);

		test::mul_test(var_0, exp1);
		test::mul_test(var_1, exp1);
		test::mul_test(var_2, exp1);
		test::mul_test(var_3, exp1);
		test::mul_test(var_4, exp1);

		std::cout << "\n\n";
	}
	void term_expression_test() {
		std::cout << "[Term to Expression] arithmetic tests\n\n";

		std::cout << "\n\n";
	}

	void expression_constant_test() {
		std::cout << "[Expression to Constant] arithmetic tests\n\n";

		std::cout << "\n\n";
	}
	void expression_variable_test() {
		std::cout << "[Expression to Variable] arithmetic tests\n\n";

		std::cout << "\n\n";
	}
	void expression_term_test() {
		std::cout << "[Expression to Term] arithemtic tests\n\n";

		std::cout << "\n\n";
	}

	void expression_expression_test() {
		std::cout << "[Expression to Expression] arithemtic tests\n\n";

		test::mul_test(exp2, exp2);

		std::cout << "\n\n";
	}
	void operand_expression_test() {
		Expression expression = Parser::Parse_Expression("1 + 2x + 2").get<Expression>();
		std::cout << "operand_expression_test = " << Expression::Operand_Expression_mul(Operand{ (double)2 }, expression) << std::endl;
	}

	void variable_isaddable_test() {
		std::cout << "variable_isaddable_test()" << std::endl << std::endl;

		cout << "var_0 = " << var_0 << endl;
		cout << "term0 = " << term0 << endl;

		cout << boolalpha << var_0.is_addable(term0) << endl;
		cout << (var_0 + term0 )<< endl;

	}
}

