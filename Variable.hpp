#ifndef Variable_H
#define Variable_H

#include <unordered_map>

class Constant;
struct Operand;

extern std::unordered_map<char, Constant> var_values;

struct Variable{
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

	friend std::ostream& operator<<(std::ostream&, const Variable&);
};

#endif