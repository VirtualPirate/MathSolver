#ifndef Operand_H
#define Operand_H

enum class DataType
{Constant=0, Variable=1, Term=2, Expression=3, None=-1};

unsigned func_hash(DataType, DataType);

class Constant;
class Variable;
class Term;
class Expression;
class Operand
{
	void* value;
	DataType type;
	bool is_null;

public:
	Operand();

	Operand(double);
	Operand& operator=(double);
	Operand(const Constant&);
	Operand& operator=(const Constant&);
	Operand(const Variable&);
	Operand& operator=(const Variable&);
	Operand(const Term&);
	Operand& operator=(const Term&);
	Operand(const Expression&);
	Operand& operator=(const Expression&);

	// Copy and Move semantics
	Operand(const Operand&);
	Operand(Operand&&);
	Operand& operator=(const Operand&);
	Operand& operator=(Operand&&);

	//Destructor
	~Operand();

	//Getters and Setters
	const DataType& getType() const;
	bool isNull() const;

	template<typename Type>
	const Type& get() const{
		return *((Type*)value);
	}

	std::string power_print() const;
	bool is_negative() const;
	bool negative_power() const;
	Operand substitute() const;

	// Operand to Operand arithmetic operators
	Operand operator+(const Operand&) const;
	Operand operator-(const Operand&) const;
	Operand operator*(const Operand&) const;
	Operand operator/(const Operand&) const;
	Operand raise_pow(const Operand&) const;

	// Operand to double arithmetic operators
	Operand operator+(const double&) const;
	Operand operator-(const double&) const;
	Operand operator*(const double&) const;
	Operand operator/(const double&) const;
	Operand raise_pow(const double&) const;

	// Operand to Constant arithmetic operators
	Operand operator+(const Constant&) const;
	Operand operator-(const Constant&) const;
	Operand operator*(const Constant&) const;
	Operand operator/(const Constant&) const;
	Operand raise_pow(const Constant&) const;

	// Operand to Variable arithmetic operators
	Operand operator+(const Variable&) const;
	Operand operator-(const Variable&) const;
	Operand operator*(const Variable&) const;
	Operand operator/(const Variable&) const;
	Operand raise_pow(const Variable&) const;

	//Operand to Term arithmetic operators
	Operand operator+(const Term&) const;
	Operand operator-(const Term&) const;
	Operand operator*(const Term&) const;
	Operand operator/(const Term&) const;
	Operand raise_pow(const Term&) const;

	//Operand to Expression arithmetic operators
	Operand operator+(const Expression&) const;
	Operand operator-(const Expression&) const;
	Operand operator*(const Expression&) const;
	Operand operator/(const Expression&) const;
	Operand raise_pow(const Expression&) const;

	Operand operator+() const;
	Operand operator-() const;
	//Operand to Operand comparison operators
	bool operator==(const Operand&) const;
	bool operator!=(const Operand&) const;

	//Operand to double comparison operators
	bool operator==(const double&) const;
	bool operator!=(const double&) const;

	//Operand to Constant comparison operators
	bool operator==(const Constant&) const;
	bool operator!=(const Constant&) const;

	//Operand to Variable comparison operators
	bool operator==(const Variable&) const;
	bool operator!=(const Variable&) const;

	//Operand to Term comparison operators
	bool operator==(const Term&) const;
	bool operator!=(const Term&) const;

	//Operand to Expression comparison operators
	bool operator==(const Expression&) const;
	bool operator!=(const Expression&) const;

	operator bool() const;
	bool same_type(const Operand&) const;
	bool same_type(const DataType&) const;

	friend std::ostream& operator<<(std::ostream&, const Operand&);


};


//Operand to Operand operations
template <class Type_1, class Type_2>
Operand Operand_Operand_add(const Operand& first, const Operand& second){
	return Operand{first.get<Type_1>() + second.get<Type_2>()};}

template <class Type_1, class Type_2>
Operand Operand_Operand_sub(const Operand& first, const Operand& second){
	return Operand{first.get<Type_1>() - second.get<Type_2>()};}

template <class Type_1, class Type_2>
Operand Operand_Operand_mul(const Operand& first, const Operand& second){
	return Operand{first.get<Type_1>() * second.get<Type_2>()};}

template <class Type_1, class Type_2>
Operand Operand_Operand_div(const Operand& first, const Operand& second){
	return Operand{first.get<Type_1>() / second.get<Type_2>()};}

template <class Type_1, class Type_2>
Operand Operand_Operand_pow(const Operand& first, const Operand& second){
	return Operand{(first.get<Type_1>()).raise_pow(second.get<Type_2>())};}

//Operand to Operand comparison
template <class Type_1, class Type_2>
bool Operand_Operand_eq(const Operand& first, const Operand& second){
	return (first.get<Type_1>()) == (second.get<Type_2>());}

template <class Type_1, class Type_2>
bool Operand_Operand_neq(const Operand& first, const Operand& second){
	return (first.get<Type_1>()) != (second.get<Type_2>());}

template <class Type>
Type& Return_Internal_Ref(const Operand& ref){
	return *(Type*)ref.value;
}

#endif