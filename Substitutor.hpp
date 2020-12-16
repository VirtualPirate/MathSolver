#ifndef Substitutor_H
#define Substitutor_H

#include "Operand.hpp"
#include <vector>

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

class Substitutor_List{
	std::vector<Substitutor> sub_;
public:
	Substitutor_List(std::initializer_list<Substitutor>);
	Substitutor_List& operator=(std::initializer_list<Substitutor>);

	Substitutor_List(const std::vector<Substitutor>&);
	Substitutor_List& operator=(const std::vector<Substitutor>&);

	// Substitutor List modifier
	void append(Substitutor);
	void extend(std::initializer_list<Substitutor>);
	void extend(std::vector<Substitutor>);

	void erase(size_t index);
	void erase(const Substitutor&);
	void clear();
};

#endif