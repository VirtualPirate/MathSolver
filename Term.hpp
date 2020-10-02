#ifndef Term_H
#define Term_H

class Term{
	std::vector<Operand> fields;
	Operand power;
	bool is_simplified;
	bool is_null;

	Term();

	Term(const Term&);
	Term& operator=(const Term&);
	Term(Term&&);
	Term& operator=(Term&&);

	Term(std::string);

	void insert(const Constant&);
	void insert(const Variable&);
	void insert(const Operand&);

	bool is_Constant() const;
	bool is_Variable() const;
	bool var_exist(const char&) const;

	// Term to Constant comparison operators
	bool operator==(const Constant&) const;
	bool operator!=(const Constant&) const;

	// Term to Variable comparison operators
	bool operator==(const Variable&) const;
	bool operator!=(const Variable&) const;

	//Term to Term comparison operators
	bool operator==(const Term&) const;
	bool operator!=(const Term&) const;

	//Term to Constant operations
	Term operator+(const Constant&) const;
	Term operator-(const Constant&) const;
	Term operator*(const Constant&) const;
	Term operator/(const Constant&) const;
	Term raise_pow(const Constant&) const;

	//Term to Variable operations
	Term operator+(const Variable&) const;
	Term operator-(const Variable&) const;
	Term operator*(const Variable&) const;
	Term operator/(const Variable&) const;
	Term raise_pow(const Variable&) const;

	//Term to Term operations
	Term operator+(const Term&) const;
	Term operator-(const Term&) const;
	Term operator*(const Term&) const;
	Term operator/(const Term&) const;
	Term raise_pow(const Term&) const;

	Term operator+() const;
	Term operator-() const;
	operator bool() const;
	friend std::ostream& operator<<(std::ostream&, const Term&);

}

#endif