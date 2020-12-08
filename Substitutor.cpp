#include "Operand.hpp"
#include "Substitutor.hpp"

Substitutor::Substitutor(const Operand& k_, const Operand& s_): key_value{k_}, substitute{s_}{}

bool Substitutor::operator==(const Operand& other) const {
	if(key_value == other)
		return true;
	return false;
}

bool Substitutor::operator!=(const Operand& other) const {
	if(key_value != other)
		return true;
	return false;
}

const Operand& Substitutor::getSubstitute() const {
	return substitute;
}

const Operand& Substitutor::getKey() const {
	return key_value;
}