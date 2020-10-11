#ifndef Variable_H
#define Variable_H

#include <unordered_map>

class Constant;
class Operand;
class Term;

extern std::unordered_map<char, Constant> var_values;

class Variable{
	char name;
	Operand power;

public:
	Variable(Variable&&) = default;
	Variable(const Variable&) = default;
	~Variable() = default;
	Variable& operator=(const Variable&);
	Variable& operator=(Variable&&);

	Variable(void);
	Variable(char);
	Variable(char, double);
	Variable(char, const Operand&);
	// Variable(char, Operand&&);

	//Getter and Setter Methods
	const char& getName() const;
	void setName(const char&);

	const Operand& getPower() const;
	void setPower(const Operand&);

	// Variable to Variable comparison operators
	bool operator==(const Variable&) const;
	bool operator!=(const Variable&) const;

	//Variable to Constant operations
	Term operator+(const Constant&) const;
	Term operator-(const Constant&) const;
	Term operator*(const Constant&) const;
	Term operator/(const Constant&) const;
	Term raise_pow(const Constant&) const;

	//Variable to Variable operations
	Term operator+(const Variable&) const;
	Term operator-(const Variable&) const;
	Term operator*(const Variable&) const;
	Term operator/(const Variable&) const;
	Term raise_pow(const Variable&) const;

	//Variable to Term operations
	Term operator+(const Term&) const;
	Term operator-(const Term&) const;
	Term operator*(const Term&) const;
	Term operator/(const Term&) const;
	Term raise_pow(const Term&) const;

	std::string power_print() const;
	bool is_negative() const;
	friend std::ostream& operator<<(std::ostream&, const Variable&);
};

#endif