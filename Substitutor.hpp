#ifndef Substitutor_H
#define Substitutor_H

#include "Operand.hpp"

class Operand;


class Substitutor{
	Operand key_value;
	Operand substitute;

public:
	Substitutor(const Operand&, const Operand&);
	bool operator==(const Operand&) const;
	bool operator!=(const Operand&) const;

	const Operand& getSubstitute() const;
	const Operand& getKey() const;
};

/*class Substitutor_List{
	std::vector<Substitutor> sub_;
public:
	Substitutor_List(std::initializer_list<Substitutor>)
}*/

#endif