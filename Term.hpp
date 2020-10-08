#ifndef Term_H
#define Term_H

#include <vector>

class Constant;
class Variable;
class Operand;
class Term{
	std::vector<Operand> fields;
	Operand power;
	bool is_simplified;
	bool is_null;

public:
	friend class iterator;
	class iterator{
		Term* ref;
		int index;
		DataType iterative;

		friend class Term;

		iterator();
		iterator(const iterator&);
		iterator(Term*, int, DataType);
		int operate_add(int);
		int operate_sub(int);
	public:
		iterator& operator=(const iterator&);
		void set_iterative(const DataType&);

		//operations
		iterator operator+(int);
		iterator operator-(int);
		iterator& operator+=(int);
		iterator& operator-=(int);

		iterator& operator++();
		iterator& operator--();
		iterator operator++(int);
		iterator operator--(int);

		Operand& operator*();

		//Comparison operator
		bool operator==(const iterator&) const;
		bool operator!=(const iterator&) const;

	};
	Term();

	//Copy and Move semantics
	Term(const Term&);
	Term& operator=(const Term&);
	Term(Term&&);
	Term& operator=(Term&&);

	Term(const Constant&);
	Term& operator=(const Constant&);
	Term(const Variable&);
	Term& operator=(const Variable&);
	Term(const Operand&);
	Term& operator=(const Operand&);

	Term(const std::vector<Operand>&);

	Term(std::string);


	//Getter Methods
	const std::vector<Operand>& getFields();
	const Operand& getPower();
	const bool& isSimplified();
	const bool& isNull();

	//Setter Methods
	void setNull(const bool&);

	void insert(const Constant&);
	void insert(const Variable&);
	void insert(const Operand&);

	bool is_Constant() const;
	bool is_Variable() const;
	bool var_exist(const char&) const;

	void simplify();

	//Iterator functions
	iterator begin(DataType);
	iterator end(DataType);
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

	//Pre-increment
	Term operator++();
	Term operator--();

	//Post-increment

	operator bool() const;

	std::string power_print() const;
	friend std::ostream& operator<<(std::ostream&, const Term&);

};

#endif