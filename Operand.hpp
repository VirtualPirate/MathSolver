#ifndef Operand_H
#define Operand_H

enum class DataType
{Constant=0, Variable=1, Term=2, Expression=3, None=-1};

unsigned func_hash(DataType, DataType);

struct Constant;

struct  Operand
{
	void* value;
	DataType type;
	bool is_null;

	Operand();

	Operand(double);
	Operand& operator=(double);
	Operand(const Constant&);
	Operand& operator=(const Constant&);

	// Copy and Move semantics
	Operand(const Operand&);
	Operand(Operand&&);
	Operand& operator=(const Operand&);
	Operand& operator=(Operand&&);

	//Destructor
	~Operand();

	std::string power_print() const;
	Operand substitute() const;

	// Operand to Operand arithmetic operators
	Operand operator+(const Operand&) const;
	Operand operator-(const Operand&) const;
	Operand operator*(const Operand&) const;
	Operand operator/(const Operand&) const;
	Operand raise_pow(const Operand&) const;
	Operand operator+() const;
	Operand operator-() const;
	//Operand to Operand comparison operators
	bool operator==(const Operand&) const;
	bool operator!=(const Operand&) const;

	operator bool() const;
	bool same_type(const Operand&) const;

	friend std::ostream& operator<<(std::ostream&, const Operand&);


};


//Operand to Operand operations
template <class Type_1, class Type_2>
Operand Operand_Operand_add(const Operand& first, const Operand& second){
	return Operand{*(Type_1*)(first.value) + *(Type_2*)(second.value)};}

template <class Type_1, class Type_2>
Operand Operand_Operand_sub(const Operand& first, const Operand& second){
	return Operand{*(Type_1*)(first.value) - *(Type_2*)(second.value)};}

template <class Type_1, class Type_2>
Operand Operand_Operand_mul(const Operand& first, const Operand& second){
	return Operand{*(Type_1*)(first.value) * *(Type_2*)(second.value)};}

template <class Type_1, class Type_2>
Operand Operand_Operand_div(const Operand& first, const Operand& second){
	return Operand{*(Type_1*)(first.value) / *(Type_2*)(second.value)};}

template <class Type_1, class Type_2>
Operand Operand_Operand_pow(const Operand& first, const Operand& second){
	return Operand{(*(Type_1*)(first.value)).raise_pow(*(Type_2*)(second.value))};}

//Operand to Operand comparison
template <class Type_1, class Type_2>
bool Operand_Operand_eq(const Operand& first, const Operand& second){
	return (*(Type_1*)(first.value)) == (*(Type_2*)(second.value));}

template <class Type_1, class Type_2>
bool Operand_Operand_neq(const Operand& first, const Operand& second){
	return (*(Type_1*)(first.value)) != (*(Type_2*)(second.value));}

template <class Type>
Type& Return_Internal_Ref(const Operand& ref){
	return *(Type*)ref.value;
}

#endif