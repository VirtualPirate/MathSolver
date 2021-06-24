#ifndef Parser_H
#define Parser_H

#include <utility>
#include <string>
#include <variant>
#include <optional>
#include <unordered_map>
#include <vector>

using Token = std::variant<double, char>;
using TokensConstIterator = std::vector<Token>::const_iterator;
using TokensConstIteratorPair = std::pair<TokensConstIterator, TokensConstIterator>;

//This hash struct is used by the lookup_table
struct pair_hash {
	template <class T1, class T2>
	std::size_t operator() (const std::pair<T1, T2>& pair) const {
		return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
	}
};

class Parser{

	static const std::unordered_map<std::pair<char, char>, char, pair_hash> lookup_table_a;

	std::string context;
	size_t current_index;
	std::vector<Token> tokens;

	std::optional<double> match_number();
	std::optional<char> match_char();

	void remove_whitespaces();
	void remove_redundant_operators(); // This function strips out redundant operator characters. Example: "-+" is deduced to "-" only
	void generalize_operators(); // Generalize the operator - and / to + and *

	Operand Parse_Expression(TokensConstIterator begin, TokensConstIterator end);
public:
	Parser(const char*);
	Parser(const std::string&);
	std::string getUnParsed() const;

	void create_tokens();
	void debug_info();

	static bool is_operator(const char&);
	static bool is_operator(const Token&);
	static bool is_operand(const Token&);

	static inline bool is_brace(const Token&, const char&);
	static bool is_leftbrace(const Token&);
	static bool is_rightbrace(const Token&);

	TokensConstIteratorPair grab_group(TokensConstIterator begin, TokensConstIterator end);

	static std::string remove_redundant_operators_2(std::string);
};

#endif