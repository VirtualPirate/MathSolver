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
Parser::Parser(std::string val): context{val}, current_index{0}, tokens{}{
	for(char each: " \f\n\r\t\v")
		context.erase(std::remove(context.begin(), context.end(), each), context.end());
	create_tokens();
}
std::string Parser::getUnParsed() const {
	return context.substr(current_index);
}
std::optional<double> Parser::match_number(){
	size_t match_length = 0;
	bool period = false;
	bool has_digit = false;
	auto iter = context.cbegin() + current_index;
	if(*iter == '-'){
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

void Parser::remove_redundant_operators() {
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
					*lower = key_->second;
					tokens.erase(upper);
					continue;
				}
			}
			else
				throw std::runtime_error{ "Error parsing - Invoked from Parser::remove_redundant_operators()" };
		}
		lower++;
		upper++;
	}
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
			std::runtime_error{"Parser::create_tokens(): Invalid token. Can't be parsed"};
	}
}

void Parser::debug_info(){
	for(std::variant<double, char>& each: tokens){
		if(std::holds_alternative<double>(each))
			std::cout << '[' << std::get<double>(each) << "] ";
		else
			std::cout << '[' << std::get<char>(each) << "] ";
	}
}

//Checks if a chararter is an operator
bool Parser::is_operator(const char& ref) {
	for (char each : "*+-/^")
		if (ref == each)
			return true;

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