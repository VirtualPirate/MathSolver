#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <stack>


#include "Operand.hpp"
#include "Parser.hpp"

std::ostream& operator<<(std::ostream& os, Token const& v) {
	std::visit([&os](auto const& e) {os << e; }, v);
	return os;
}

bool operator==(const Token& first, const char& second) {
	if (std::holds_alternative<char>(first) && std::get<char>(first) == second)
		return true;
	return false;
}

bool operator!=(const Token& first, const char& second) {
	return !(first == second);
}

std::unordered_map<std::pair<char, char>, char, pair_hash> const Parser::lookup_table_a = {
	{{'+', '+'}, '+'},
	{{'+', '-'}, '-'},
	{{'-', '+'}, '-'},
	{{'-', '-'}, '+'},
	{{'*', '+'}, '*'},
	{{'*', '-'}, '\0'},
	{{'/', '+'}, '/'},
	{{'/', '-'}, '\0'},
	{{'^', '+'}, '^'},
	{{'^', '-'}, '\0'}
};


//Parser Implementation
Parser::Parser(const char* val) : context{ val }, current_index{ 0 }, tokens{}{
	remove_whitespaces();
	remove_redundant_operators();
	create_tokens();
	generalize_operators();
	strip_operators();
}
Parser::Parser(const std::string& val): context{val}, current_index{0}, tokens{}{
	remove_whitespaces();
	remove_redundant_operators();
	create_tokens();
	generalize_operators();
	strip_operators();
}
std::string Parser::getUnParsed() const {
	return context.substr(current_index);
}

const std::vector<Token>& Parser::getTokens() const {
	return tokens;
}
std::optional<double> Parser::match_number(){
	size_t match_length = 0;
	bool period = false;
	bool has_digit = false;
	bool matched_operator = false;
	auto iter = context.cbegin() + current_index;
	if(*iter == '-' || *iter == '+') {
		match_length++;
		iter++;
		matched_operator = true;
	}
	for(;iter!=context.cend(); iter++){
		if(isdigit(*iter)){
			match_length++;
			has_digit = true;
		}
		else if(*iter == '.' && !period){
			period = true;
			match_length++;
			has_digit = false;
		}else break;
	}
	if(has_digit){
		double value = std::stod(context.substr(current_index, match_length));
		current_index += match_length;
		if (matched_operator)
			tokens.emplace_back('+');
		return value;
	}
	return {};
}
std::optional<char> Parser::match_char(){
	auto iter = context.cbegin() + current_index;
	for(char each: "*+-/^()")
		if(*iter == each || isalpha(*iter)){
			current_index++;
			return *iter;
		}
		return {};
}

void Parser::remove_whitespaces() {
	for (char each : " \f\n\r\t\v")
		context.erase(std::remove(context.begin(), context.end(), each), context.end());
}

std::string Parser::remove_redundant_operators_2(std::string expression) {

	size_t expression_length = expression.size();

	std::string str;
	str.reserve(expression_length);

	size_t lower_index = 0;
	size_t upper_index = 1;

	char lower_char = '\0';
	char upper_char = '\0';
	std::unordered_map<std::pair<char, char>, char, pair_hash>::const_iterator key_;
	std::pair<char, char> op_pair;

	while (upper_index < expression_length) {

		lower_char = expression[lower_index];
		upper_char = expression[upper_index];

		if (Parser::is_operator(lower_char) && Parser::is_operator(upper_char)) {
			op_pair.first = lower_char;
			op_pair.second = upper_char;
			key_ = Parser::lookup_table_a.find(op_pair);
			if (key_ != Parser::lookup_table_a.cend() && key_->second != '\0') {
				expression[upper_index] = key_->second;
				expression[lower_index] = '\0';
			}
			else
				throw std::runtime_error{ "Error parsing - Invoked from Parser::remove_redunadant_operators_2()" };

		}

		upper_index++;
		lower_index++;
	}

	char each_char = '\0';
	for (size_t index = 0; index < expression_length; index++) {
		each_char = expression[index];
		if (each_char != '\0')
			str.push_back(each_char);
	}

	return str;

}

void Parser::remove_redundant_operators() {
	size_t expression_length = context.size();

	std::string str;
	str.reserve(expression_length);

	size_t lower_index = 0;
	size_t upper_index = 1;

	char lower_char = '\0';
	char upper_char = '\0';
	std::unordered_map<std::pair<char, char>, char, pair_hash>::const_iterator key_;
	std::pair<char, char> op_pair;

	while (upper_index < expression_length) {

		lower_char = context[lower_index];
		upper_char = context[upper_index];

		if (Parser::is_operator(lower_char) && Parser::is_operator(upper_char)) {
			op_pair.first = lower_char;
			op_pair.second = upper_char;
			key_ = Parser::lookup_table_a.find(op_pair);
			if (key_ != Parser::lookup_table_a.cend() && key_->second != '\0') {
				context[upper_index] = key_->second;
				context[lower_index] = '\0';
			}
			else
				throw std::runtime_error{ "Error parsing - Invoked from Parser::remove_redunadant_operators()" };

		}

		upper_index++;
		lower_index++;
	}

	char each_char = '\0';
	for (size_t index = 0; index < expression_length; index++) {
		each_char = context[index];
		if (each_char != '\0')
			str.push_back(each_char);
	}

	context = std::move(str);

}

void Parser::generalize_operators() {
	
	Token token_minus{ '-' };
	Token token_divide{ '/' };

	bool has_operand = false;
	std::vector<Token> new_tokens;
	size_t minus_count = std::count(tokens.begin(), tokens.end(), token_minus);
	size_t div_count = std::count(tokens.begin(), tokens.end(), token_divide);
	new_tokens.reserve(tokens.size() + (minus_count + div_count) * 2);
	for (const Token& each : tokens) {
		if (each == token_minus) {
			if (has_operand) {
				new_tokens.push_back('+');
				new_tokens.push_back((double)-1);
			}
			else
				new_tokens.push_back((double)-1);
			continue;
		}
		else if (Parser::is_operand(each)) {
			has_operand = true;
		}
		else {
			has_operand = false;
		}
		new_tokens.push_back(each);
	}

	size_t index = 0;
	while (index < new_tokens.size()) {
		if (new_tokens[index] == token_divide) {
			if (index+1 >= new_tokens.size())
				break;
			new_tokens[index] = new_tokens[index + 1];
			new_tokens[index + 1] = Token{ '^' };
			new_tokens.insert(new_tokens.begin() + index + 2, (double)-1);
			index++;
		}
		index++;
	}

	tokens = std::move(new_tokens);

}

void Parser::create_tokens(){
	std::optional<double> number_match;
	std::optional<char> char_match;
	while(current_index < context.size()){
		if(number_match = match_number())
			tokens.push_back(number_match.value());
		else if(char_match = match_char())
			tokens.push_back(char_match.value());
		else
			throw std::runtime_error{"Parser::create_tokens(): Invalid token. Can't be parsed"};
	}
}

void Parser::debug_info(){
	for(std::variant<double, char>& each: tokens){
		if(std::holds_alternative<double>(each))
			std::cout << '[' << std::get<double>(each) << "] ";
		else
			std::cout << '[' << std::get<char>(each) << "] ";
	}
	std::cout << std::endl;
}

void Parser::test_grab_group() {
	auto iter = Parser::grab_group(tokens.cbegin(), tokens.cend());
	std::cout << "{ ";
	for (; iter.first < iter.second; (iter.first)++)
		std::cout << *(iter.first);
	std::cout << "}\n";
}

//Checks if a chararter is an operator
bool Parser::is_operator(const char& ref) {
	for (char each : "*+-/^") {
		if (ref == each)
			return true;
	}

	return false;
}

// Checks if a Token is an operator.
// Calls Parser::is_operator(const char& ref) internally
bool Parser::is_operator(const Token& ref) {
	if (std::holds_alternative<char>(ref))
		return Parser::is_operator(std::get<char>(ref));
	return false;
}

// Checks if a Token is double type
bool Parser::is_operand(const Token& ref) {
	if (std::holds_alternative<double>(ref))
		return true;
	else
		return isalpha(std::get<char>(ref));
}

inline bool Parser::is_brace(const Token& ref, const char& brace) {
	if (std::holds_alternative<char>(ref) && std::get<char>(ref) == brace)
		return true;
	return false;
}

// checks if a Token is '('
bool Parser::is_leftbrace(const Token& ref) {
	return Parser::is_brace(ref, '(');
}

// checks if a Token is ')'
bool Parser::is_rightbrace(const Token& ref) {
	return Parser::is_brace(ref, ')');
}


TokensConstIteratorPair Parser::grab_group(TokensConstIterator begin, TokensConstIterator end) {
	bool group_continuing = false;
	bool group_started = false;
	unsigned brace_count = 0;
	TokensConstIteratorPair group;

	for ( ;begin < end; begin++) {
		if (Parser::is_leftbrace(*begin)) {
			if (!group_started) {
				group.first = begin+1;
				group_started = true;
			}

			if (brace_count != 0)
				group.second = begin+1;
			brace_count++;
			continue;
		}
		else if (Parser::is_rightbrace(*begin))
			brace_count--;
		if (brace_count > 0) {
			group.second = begin+1;
			group_continuing = true;
		}
		else if (group_continuing)
			break;
			
	}

	return group;
}

TokensConstIteratorPair Parser::grab_term(TokensConstIterator begin, TokensConstIterator end) {
	bool term_started = false;
	TokensConstIteratorPair group;

	for (; begin < end; begin++) {
		if (*begin != '+') {
			if (!term_started) {
				term_started = false;
				group.first = begin;
			}
			if (Parser::is_leftbrace(*begin))
				begin = Parser::grab_group(begin, end).second;
			group.second = begin + 1;
		}
		else
			return group;
	}

	return group;
}


inline void Parser::lstrip_operators() {
	while (Parser::is_operator(*(tokens.begin())))
		tokens.erase(tokens.begin());
}

inline void Parser::rstrip_operators() {
	while (Parser::is_operator(*(tokens.rbegin())))
		tokens.erase((tokens.rbegin()+1).base());
}

void Parser::strip_operators() {
	lstrip_operators();
	rstrip_operators();
}