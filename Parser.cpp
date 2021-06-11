#include <iostream>
#include <cstdlib>
#include <algorithm>

#include "Operand.hpp"
#include "Parser.hpp"

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