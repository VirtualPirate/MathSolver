#include <iostream>

#include "Operand.hpp"
#include "Parser.hpp"


//MatchToken implementation
MatchToken::MatchToken(const std::string* ref): context{ref}, indexes{std::pair{0, 0}}, token_type{DataType::None}, token_found{false}{}

void MatchToken::setContext(const std::string* ref){context = ref;}
void MatchToken::setIndexes(size_t first, size_t second){indexes= std::pair{first, second};}
void MatchToken::setTokenType(DataType type){token_type = type;}
void MatchToken::setTokenFound(bool bool_){token_found = bool_;}

const std::string* MatchToken::getContext() const {return context;}
const std::pair<size_t, size_t>& MatchToken::getIndexes() const {return indexes;}
DataType MatchToken::getTokenType() const {return token_type;}
MatchToken::operator bool() const{
	return token_type != DataType::None && token_found;
}

std::string MatchToken::getMatchedString() const{
	return context->substr(indexes.first, indexes.second);
}


//Parser Implementation
Parser::Parser(const std::string& ref): context{ref}, current_index{0}{}
std::string Parser::getUnParsed() const {
	return context.substr(current_index);
}

MatchToken Parser::match_number() {
	size_t match_length = 0;
	bool period = false;
	bool has_digit = false;
	auto iter = context.begin() + current_index;
	if(*iter == '-'){
		match_length++;
		iter++;
	}
	for(;iter!=context.end(); iter++){
		if(isdigit(*iter)){
			match_length++;
			has_digit = true;
		}
		else if(*iter == '.' && !period){
			period = true;
			std::cout << "[match]: " << *iter << std::endl;
			match_length++;
			has_digit = false;
		}else break;
	}

	//MatchToken initilization
	MatchToken match{&context};
	if(has_digit){
		match.setIndexes(current_index, current_index+match_length);
		match.setTokenType(DataType::Constant);
		match.setTokenFound(true);
		current_index += match_length;
	}else{
		match.setTokenType(DataType::None);
		match.setTokenFound(false);
	}
	return match;
}
