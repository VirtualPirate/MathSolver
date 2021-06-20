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
	//std::cout << "debug info -> "; this->debug_info();
	generalize_operators();
}
Parser::Parser(const std::string& val): context{val}, current_index{0}, tokens{}{
	remove_whitespaces();
	remove_redundant_operators();
	create_tokens();
	//std::cout << "debug info -> "; this->debug_info();
	generalize_operators();
}
std::string Parser::getUnParsed() const {
	return context.substr(current_index);
}
std::optional<double> Parser::match_number(){
	size_t match_length = 0;
	bool period = false;
	bool has_digit = false;
	auto iter = context.cbegin() + current_index;
	if(*iter == '-' || *iter == '+') {
		match_length++;
		iter++;
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
	/*
	std::pair<char, char> op_pair;
	auto lower = tokens.begin();
	auto upper = tokens.begin() + 1;
	std::unordered_map<std::pair<char, char>, char, pair_hash>::const_iterator key_;
	while (upper != tokens.end()) {
		if (Parser::is_operator(*lower) && Parser::is_operator(*upper)) {
			op_pair.first = std::get<char>(*lower);
			op_pair.second = std::get<char>(*upper);
			key_ = Parser::lookup_table_a.find(op_pair);
			if (key_ != Parser::lookup_table_a.cend()) { // If the key is present
				if (key_->second != '\0') { // if key_->second is a valid operator
					*upper = key_->second;
					*lower = '\0';
				}
			}
			else
				throw std::runtime_error{ "Error parsing - Invoked from Parser::remap_tokens()" };
		}
		lower++;
		upper++;
	}

	std::vector<Token> new_tokens;
	new_tokens.reserve(tokens.size());
	for (auto each = tokens.begin(); each != tokens.end(); each++) {
		if (std::holds_alternative<char>(*each) && std::get<char>(*each) == '\0')
			continue;
		new_tokens.push_back(*each);
	}
	tokens = std::move(new_tokens);
	*/
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
		if (new_tokens[index] == token_minus) {
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