#ifndef OperandList_H
#define OperandList_H

#include <vector>

class Constant;
class Variable;
class Operand;
class OperandList{
protected:
	std::vector<Operand> fields;
	Operand power;
	bool is_simplified;
	bool is_null;

public:
	friend class iterator;
	class iterator{
		OperandList* ref;
		int index;
		DataType iterative;

		friend class OperandList;

		iterator();
		iterator(const iterator&);
		iterator(OperandList*, int, DataType);
		int operate_add(int);
		int operate_sub(int);
	public:
		iterator& operator=(const iterator&);
		void set_iterative(const DataType&);
		int getIndex() const;
		
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
	OperandList();

	//Copy and Move semantics
	OperandList(const OperandList&);
	OperandList& operator=(const OperandList&);
	OperandList(OperandList&&);
	OperandList& operator=(OperandList&&);

	OperandList(const Constant&);
	OperandList& operator=(const Constant&);
	OperandList(const Variable&);
	OperandList& operator=(const Variable&);
	OperandList(const Operand&);
	OperandList& operator=(const Operand&);

	OperandList(const std::vector<Operand>&);

	OperandList(std::string);


	//Getter Methods
	const std::vector<Operand>& getFields() const;
	const Operand& getPower() const;
	const bool& isSimplified() const;
	const bool& isNull() const;

	//Setter Methods
	void setNull(const bool&);
	void setPower(const Operand&);

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
	/*
	// OperandList to Constant comparison operators
	bool operator==(const Constant&) const;
	bool operator!=(const Constant&) const;

	// OperandList to Variable comparison operators
	bool operator==(const Variable&) const;
	bool operator!=(const Variable&) const;

	//OperandList to OperandList comparison operators
	bool operator==(const OperandList&) const;
	bool operator!=(const OperandList&) const;

	//OperandList to Constant operations
	OperandList operator+(const Constant&) const;
	OperandList operator-(const Constant&) const;
	OperandList operator*(const Constant&) const;
	OperandList operator/(const Constant&) const;
	OperandList raise_pow(const Constant&) const;

	//OperandList to Variable operations
	OperandList operator+(const Variable&) const;
	OperandList operator-(const Variable&) const;
	OperandList operator*(const Variable&) const;
	OperandList operator/(const Variable&) const;
	OperandList raise_pow(const Variable&) const;

	//OperandList to OperandList operations
	OperandList operator+(const OperandList&) const;
	OperandList operator-(const OperandList&) const;
	OperandList operator*(const OperandList&) const;
	OperandList operator/(const OperandList&) const;
	OperandList raise_pow(const OperandList&) const;

	//Pre-increment
	OperandList operator++();
	OperandList operator--();

	//Post-increment
	*/
	operator bool() const;

	// std::string power_print() const;
	// friend std::ostream& operator<<(std::ostream&, const OperandList&);

};

#endif