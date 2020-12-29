#ifndef Parser_H
#define Parser_H

#include <utility>
#include <string>
#include <variant>
#include <optional>

using Token = std::variant<double, char>;

class Parser{
	std::string context;
	size_t current_index;
	std::vector<Token> tokens;

public:
	Parser(std::string);
	std::string getUnParsed() const;
	std::optional<double> match_number();
	std::optional<char> match_char();

	void create_tokens();
	void debug_info();
};

#endif