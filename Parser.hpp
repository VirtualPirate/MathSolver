#ifndef Parser_H
#define Parser_H

#include <utility>
#include <string>

class MatchToken{
	const std::string* context;
	std::pair<size_t, size_t> indexes;
	DataType token_type;
	bool token_found;

public:
	MatchToken(const std::string* context);
	//Setters
	void setContext(const std::string*);
	void setIndexes(size_t, size_t);
	void setTokenType(DataType);
	void setTokenFound(bool);

	//Getters
	const std::string* getContext() const;
	const std::pair<size_t, size_t>& getIndexes() const;
	DataType getTokenType() const;
	operator bool() const;

	std::string getMatchedString() const;
	
};

class Parser{
	std::string context;
	size_t current_index;

	friend class MatchToken;

public:
	MatchToken match_number();
	MatchToken match_variable();
	MatchToken match_term();
	MatchToken match_expression();

public:
	Parser(const std::string&);
	std::string getUnParsed() const;
	Operand match();
};

// MatchToken match_number(const std::string&);
// MatchToken match_variable(const std::string&);
// MatchToken match_term(const std::string&);
// MatchToken match_expression(const std::string&);

// Operand match_operand(const std::string&);

#endif