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

#endif