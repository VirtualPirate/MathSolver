#ifndef Parser_H
#define Parser_H

#include <utility>
#include <string>
#include <variant>
#include <optional>
#include <unordered_map>
#include <vector>

using Token = std::variant<double, char>;

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

	void remove_redundant_operators(); // This function strips out redundant operator characters. Example: "-+" is deduced to "-" only
	void generalize_operators(); // Generalize the operator - and / to + and *
public:
	Parser(const char*);
	Parser(const std::string&);
	std::string getUnParsed() const;

	void create_tokens();
	void debug_info();

	static bool is_operator(const char&);
	static bool is_operator(const Token&);
	static bool is_operand(const Token&);
};

#endif