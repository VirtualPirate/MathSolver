#ifndef Expression_H
#define Expression_H

class Constant;
class Variable;
class Term;
class Expression{
	std::vector<Operand> fields;
	Operand power;
	bool is_simplified;
	bool is_null;

public:
	Expression(const Expression&);
	Expression& operator=(const Expression&);
	Expression(Expression&&);
	Expression& operator=(Expression&&);

	Expression(const std::vector<Operand>&);

	//Getter Methods
	const std::vector<Operand>& getFields();
	const Operand& getPower();
	const bool& isSimplified();
	const bool& isNull();

	//Setter Methods
	void setNull(const bool&);
	void setPower(const Operand&);

	void insert(const Constant&);
	void insert(const Variable&);
	void insert(const Operand&);
};

#endif